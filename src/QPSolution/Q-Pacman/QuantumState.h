#pragma once

#include "InternalState.h"

#include "LoggedObject.h"

#include <vector>
#include <complex>

/*
* WARNING, matrix multiplication order MATTERS !
* 
* For now : No multiple input so not a problem (hopefully)
* Still, always multiply matrices in declaration order !
*/

//Libs exist ot handle complex registers but where's the fun then ?
class QuantumState : public ProtoEng::LoggedObject
{
public:
	//Static Flags for matrix combination
	static const uint16_t H_FLAG = 0x0001;
	static const uint16_t RT_FLAG = 0x0002;
	static const uint16_t LT_FLAG = 0x0004;
	static const uint16_t INV_FLAG = 0x0008;
	static const uint16_t SWAP_FLAG = 0x0010;

	//Static Matrices
	static const float H_factor;
	static const std::vector<std::vector<std::complex<float>>> HADAMAR;
	static const std::vector<std::vector<std::complex<float>>> R_TURN;
	static const std::vector<std::vector<std::complex<float>>> L_TURN;
	static const std::vector<std::vector<std::complex<float>>> INV;
	static const std::vector<std::vector<std::complex<float>>> SWAP;

	static const std::vector<std::vector<std::complex<float>>> Ident;


	//Utility
	static std::vector<std::vector<std::complex<float>>>
		matrixCombine(uint16_t matrixFlag);

	static std::vector<std::vector<std::complex<float>>>
		matrixMultiply(
			std::vector<std::vector<std::complex<float>>> m1,
			std::vector<std::vector<std::complex<float>>> m2
		);


	//Local
	QuantumState();
	QuantumState(uint16_t id);
	QuantumState(std::list<uint16_t> ids);
	QuantumState(const std::vector<std::complex<float>>& reg);
	~QuantumState();

	//Matrix Function
	void apply_transform(uint16_t matrixFlag);
	void hadamar_dir(); //Apply Hadamar on the 2 directional bits
	void rturn_dir();   //Apply Right-Tun on the 2 directional bits
	void lturn_dir();   //Apply Left-Turn on the 2 directional bits
	void inv_dir();     //Apply Inverse on the 2 directional bits
	void swap_dir();    //Apply Pauli-Y on the 2 directional bits


	//Power up Tranform
	void goSuper(sf::Vector2i pos);

	//Move
	void move();

	//Accessor

	//Array-like accessor
	std::complex<float> operator[](InternalState is);
	const std::complex<float> operator[](InternalState is) const;
	std::complex<float> operator[](uint16_t id);
	const std::complex<float> operator[](uint16_t id) const;
private:
	//Overrides
	virtual std::string custom_log_header() const override;

	void swapCache(); //DO NOT USE if you're not 100% sure of what you're doing !

	std::vector<std::complex<float>>* reg;
	std::vector<std::complex<float>>* cache;
};


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
