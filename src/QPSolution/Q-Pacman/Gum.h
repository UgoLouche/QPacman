#pragma once

#include "ImmobileEntity.h"

class Gum : public ImmobileEntity
{
public:
	Gum();
	Gum(QPacman* parent, QPWorld* wld);
	~Gum();

	void init();

private:
	// Inherited via ClassicEntity
	virtual void act_custom() override;
	virtual void collision_custom(float coeff, bool isSuper) override;
	virtual std::string custom_log_header() const override;
};