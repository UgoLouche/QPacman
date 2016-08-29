#include "QuantumState.h"

#include "InternalState.h"

#include "const.h"

//Static Initialization
//Hadamar (see maths at the end)
//These are derived from 1Qbit gate, for instance P_x_2 = P_x (X) P_x
//With (X) the tensor product
const float QuantumState::H_factor = 1 / sqrtf(4.0f);
const std::vector<std::vector<std::complex<float>>> QuantumState::HADAMAR = {
	{H_factor,  H_factor,  H_factor,  H_factor},
	{H_factor, -H_factor,  H_factor, -H_factor},
	{H_factor,  H_factor, -H_factor, -H_factor},
	{H_factor, -H_factor, -H_factor,  H_factor}
};

const std::vector<std::vector<std::complex<float>>> QuantumState::R_TURN = {
	{ 0, 0, 1, 0 },
	{ 1, 0, 0, 0 },
	{ 0, 0, 0, 1 },
	{ 0, 1, 0, 0 },
};

const std::vector<std::vector<std::complex<float>>> QuantumState::L_TURN = {
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 1 },
	{ 1, 0, 0, 0 },
	{ 0, 0, 1, 0 },
};

const std::vector<std::vector<std::complex<float>>> QuantumState::INV = {
	{0, 0, 0, 1},
	{0, 0, 1, 0},
	{0, 1, 0, 0},
	{1, 0, 0, 0},
};

const std::vector<std::vector<std::complex<float>>> QuantumState::SWAP = {
	{1, 0, 0, 0},
	{0, 0, 1, 0},
	{0, 1, 0, 0},
	{0, 0, 0, 1},
};

const std::vector<std::vector<std::complex<float>>> QuantumState::Ident = {
	{ 1, 0, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 1, 0 },
	{ 0, 0, 0, 1 },
};


std::vector<std::vector<std::complex<float>>> QuantumState::matrixCombine(uint16_t matrixFlag)
{
	std::vector<std::vector<std::complex<float>>> ret = Ident;

	if ( (matrixFlag & H_FLAG) > 0 )    ret = matrixMultiply(ret, HADAMAR);
	if ( (matrixFlag & RT_FLAG) > 0 )   ret = matrixMultiply(ret, R_TURN);
	if ( (matrixFlag & LT_FLAG) > 0 )   ret = matrixMultiply(ret, L_TURN);
	if ( (matrixFlag & INV_FLAG) > 0 )  ret = matrixMultiply(ret, INV);
	if ( (matrixFlag & SWAP_FLAG) > 0 ) ret = matrixMultiply(ret, SWAP);

	return ret;
}

//Naive implementation but size is constant ... and this shouldn't be called a lot
std::vector<std::vector<std::complex<float>>> 
QuantumState::matrixMultiply(
	std::vector<std::vector<std::complex<float>>> m1, 
	std::vector<std::vector<std::complex<float>>> m2
)
{
	std::vector<std::vector<std::complex<float>>> ret(
		4, 
		std::vector<std::complex<float>>(
			4, 
			std::complex<float> (0.0f, 0.0f)
		)
	);

	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			for (size_t k = 0; k < 4; k++)
			{
				ret[i][j] += m1[i][k] * m2[k][j];
			}
		}
	}

	return ret;
}

QuantumState::QuantumState()
{
	reg = new std::vector<std::complex<float>>(
		Q_REGISTER_SIZE, 
		std::complex<float>(0.0f, 0.0f)
	);

	cache = new std::vector<std::complex<float>>(
		Q_REGISTER_SIZE, 
		std::complex<float>(0.0f, 0.0f)
	);
}

QuantumState::QuantumState(uint16_t id)
	: QuantumState()
{
	(*reg)[id] = std::complex<float>(1.0f, 0.0f);
}

QuantumState::QuantumState(std::list<uint16_t> ids)
	: QuantumState()
{
	for (std::list<uint16_t>::iterator it = ids.begin(); it != ids.end(); ++it)
		(*reg)[*it] = std::complex<float>(1.0f / ids.size(), 0.0f);
}

QuantumState::QuantumState(const std::vector<std::complex<float>>& reg)
{
	this->reg = new std::vector<std::complex<float>>(reg);
	cache = new std::vector<std::complex<float>>(reg);
}

QuantumState::~QuantumState()
{
	delete(reg);
	delete(cache);
}

void QuantumState::apply_transform(uint16_t matrixFlag)
{
	std::complex<float> tmp;
	std::vector<std::vector<std::complex<float>>> mat =
		matrixCombine(matrixFlag);

	//No need for iterator, Impl likely won't change and I need an int counter anyway
	uint16_t index; 

	//loop and other variables
	uint16_t row_index; //take value between 0 and 3
	uint16_t index_loop; //Variable used to access v[1] through v[4] (see maths)

	//You can safely ignore the unused bits
	for (index = 0x0000; index <= (uint16_t)(~(InternalState::EXTRA)); ++index)
	{
		tmp = 0;

		//First compute the row index for the Matrix (i in maths below)
		row_index = (index & InternalState::DIRECTION) >> 10;

		for (int col_index = 0; col_index < 4; col_index++)
		{
			//Take index, kill directiions and replace by col_index's direction (j in math)
			index_loop = (index & ~(InternalState::DIRECTION)) | (col_index << 10);

			//Compute sum
			tmp += mat[row_index][col_index] * (*reg)[index_loop];
		}

		(*cache)[index] = tmp;
	}

	swapCache();
}

void QuantumState::hadamar_dir()
{
	apply_transform(H_FLAG);
}

void QuantumState::rturn_dir()
{
	apply_transform(RT_FLAG);
}

void QuantumState::lturn_dir()
{
	apply_transform(LT_FLAG);
}

void QuantumState::inv_dir()
{
	apply_transform(INV_FLAG);
}

void QuantumState::swap_dir()
{
	apply_transform(SWAP_FLAG);
}

void QuantumState::goSuper(sf::Vector2i pos)
{
	//For a given pos ther's only 4 state to swap (one for each direction)
	//with 4 others (same IS with different super bit
	uint16_t index_base; //Base index
	uint16_t index_loop; //used in loop with direction specified
	uint16_t index_super; //index loop with/without super bit
	InternalState index_is = InternalState(0x0000); //Ad-hoc for creating index_base
	index_is.setPosition(pos);

	std::complex<float> tmp;
	index_base = index_is.getIs();
	for (uint16_t dir_bits = 0x0000; dir_bits <= 0x0003; ++dir_bits)
	{
		index_loop = index_base | (dir_bits << 10);
		//Check the super bit, and compute index for the twin state
		if ( (index_loop & InternalState::SUPER) > 0) index_super = 
			index_loop & ~InternalState::SUPER;
		else index_super = index_loop | InternalState::SUPER;

		tmp = (*reg)[index_super];
		(*reg)[index_super] = (*reg)[index_loop];
		(*reg)[index_loop] = tmp;
	}
}

/*Pre-Computing Transition Tables should be faster, 
investigate if performance is an issue
*/
void QuantumState::move()
{
	uint16_t index;
	InternalState index_is;
	sf::Vector2i pos;

	//Iterate through all valid indexes
	for (index = 0x0000; index <= (uint16_t)(~(InternalState::EXTRA)); ++index)
	{
		index_is = InternalState(index); //Wrap index
		pos = index_is.getPosition();

		//Check that position is within the board, or at most 1 cell past the edges
		if (pos.x >= 0 && pos.x <= BOARD_WIDTH-1 && pos.y >= 0 && pos.y <= BOARD_HEIGHT-1)
		{
			//Then Compute Next Position
			pos += index_is.getDirectionOffset();

			//Out-of-board point handling, This is where I should handle ghosts
			if (pos.x < 0)                     pos.x += BOARD_WIDTH;
			else if (pos.y < 0)                pos.y += BOARD_HEIGHT;
			else if (pos.x > BOARD_WIDTH - 1)  pos.x -= BOARD_WIDTH;
			else if (pos.y > BOARD_HEIGHT - 1) pos.y -= BOARD_HEIGHT;
			index_is.setPosition(pos);

			(*cache)[index_is.getIs()] = (*reg)[index];
		}
	}

	swapCache();
}

std::complex<float> QuantumState::operator[](InternalState is)
{
	return (*reg)[InternalState::is2int(is)];
}

const std::complex<float> QuantumState::operator[](InternalState is) const
{
	return (*reg)[InternalState::is2int(is)];
}

std::complex<float> QuantumState::operator[](uint16_t id)
{
	return (*reg)[id];
}

const std::complex<float> QuantumState::operator[](uint16_t id) const
{
	return (*reg)[id];
}

std::string QuantumState::custom_log_header() const
{
	return "::QuantumState::";
}

void QuantumState::swapCache()
{
	std::vector<std::complex<float>>* swap_tmp = reg;
	reg = cache;
	cache = swap_tmp;
}


/* Quick Math
Hadamar Matrix on 2 Qbit: H =  ( 1/sqrt(4) ) * ...
1  1  1  1
1 -1  1 -1
1  1 -1 -1
1 -1 -1  1

Let V a 2 Qbit vector : V = |00> v1 + |01> v2 + |10> v3 + |11> v4
Let V' = H * V with V = |00> v'1 + |01> v'2 + |10> v'3 + |11> v'4

Then :
v'1 = H[1,1] v1 + H[1,2] v2 + H[1,3] v'3 + H[1,4] v'4

Or more generally : v'[i] = SUM[j = 1:4] H[i,j] v[j]
*/
