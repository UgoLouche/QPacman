#pragma once

#include "ClassicEntity.h"

#include "SFML\Graphics.hpp"

#include <string>

class QPacman;
class QPWorld;

class TestEntity : public ClassicEntity
{
public:
	TestEntity();
	TestEntity(QPacman* parent, QPWorld* wld);
	~TestEntity();

	void init();

private:
	//Overrides
	virtual void act_custom() override;
	virtual void collision_custom(float coeff, bool isSuper) override;
	virtual std::string custom_log_header() const override;

	int stepCount;
};