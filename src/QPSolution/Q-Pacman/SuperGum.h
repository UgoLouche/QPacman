#pragma once

#include "ImmobileEntity.h"

class SuperGum : public ImmobileEntity
{
public:
	SuperGum();
	SuperGum(QPacman* parent, QPWorld* wld);
	~SuperGum();

	void init();

private:
	// Inherited via ClassicEntity
	virtual void act_custom() override;
	virtual void collision_custom(float coeff, bool isSuper) override;
	virtual std::string custom_log_header() const override;
};