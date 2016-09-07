#include "QuantumEntity.h"

#include "QPSpriteFactory.h"
#include "QPInput.h"

#include "const.h"



QuantumEntity::QuantumEntity()
{
}

QuantumEntity::QuantumEntity(QPacman* parent, QPWorld* wld)
	: Entity(parent, wld), state(402)
{
	/*setRandomBounds(0, 4);

	//That's a bit ugly I admit...
	state[
		InternalState(
			sf::Vector2i((BOARD_WIDTH / 2) - 4 + nextRndInt(), (BOARD_HEIGHT / 2) - 4 + nextRndInt()),
			Directions::NORTH + nextRndInt(),
			false
		).getIs()
	] = std::complex<float>(1.0f, .0f);*/
}

QuantumEntity::~QuantumEntity()
{
}

void QuantumEntity::init()
{
	setSprite(getFactory().getPlayerSprite());
}

void QuantumEntity::goSuper(sf::Vector2i pos)
{
	state.goSuper(pos);
}

float QuantumEntity::getProba(
	uint16_t flag, 
	sf::Vector2i pos, 
	Directions dir, 
	bool isSuper
) const
{
	return getProba( flag, InternalState(pos, dir, isSuper).getIs() );
}

float QuantumEntity::getProba(uint16_t flag, uint16_t base) const
{
	if (flag == InternalState::FULL) return std::norm(state[base]); //Shortcut, see if it improves perf

	float ret = 0;
	std::list<uint16_t> matchingPatterns = InternalState::patternMatch(base, flag);

	std::list<uint16_t>::iterator it;

	for (it = matchingPatterns.begin(); it != matchingPatterns.end(); ++it)
		ret += std::norm(state[*it]);

	return ret;
}

void QuantumEntity::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	sf::Vector2f posf;
	sf::Vector2i posi;
	InternalState tmp;
	float c_norm;

	for (uint16_t index = 0x0000; index <= (uint16_t)(~(InternalState::EXTRA)); ++index)
	{
		c_norm = std::norm(state[index]);
		if (c_norm > 0)
		{
			tmp = InternalState::int2is(index);
			posf = tmp.getDrawPosition(getActionTimeRatio());

			drawSprite(
				target,
				states,
				posf,
				tmp.getDirectionAngle(),
				(int)( (0.5 + c_norm) / 1.5 * 255), //Minimal threshold for alpha.
				tmp.getSuper()
			);

		}
	}
}

void QuantumEntity::notifyGraphicUpdate_custom(sf::Time deltaTime)
{
	updateSprite(deltaTime);
}

//See Input Mapping in QPInput.h
void QuantumEntity::act_custom()
{
	QPInput inputs = getInputs();
	uint16_t matrixFlag = 0x0000;

	if (inputs.isKey1Pressed()) matrixFlag |= QuantumState::SWAP_FLAG;
	if (inputs.isKey2Pressed()) matrixFlag |= QuantumState::INV_FLAG;
	if (inputs.isKey3Pressed()) matrixFlag |= 0x0000; //No Input Mapped yet
	if (inputs.isKey4Pressed()) matrixFlag |= QuantumState::LT_FLAG;
	if (inputs.isKey5Pressed()) matrixFlag |= QuantumState::H_FLAG;
	if (inputs.isKey6Pressed()) matrixFlag |= QuantumState::RT_FLAG;
	if (inputs.isKey7Pressed()) matrixFlag |= 0x0000; //No Input Mapped yet
	if (inputs.isKey8Pressed()) matrixFlag |= 0x0000; //No Input Mapped yet
	if (inputs.isKey9Pressed()) matrixFlag |= 0x0000; //No Input Mapped yet

	state.apply_transform(matrixFlag);

	state.move();
}
