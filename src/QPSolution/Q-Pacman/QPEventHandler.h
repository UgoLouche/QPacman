#pragma once

#include "QPInput.h"

#include "EventHandler.h"

#include "SFML\Graphics.hpp"

#include <cstdint>


class QPacman;
class QuantumEntity;

class QPEventHandler : public ProtoEng::EventHandler
{
public:
	QPEventHandler();
	~QPEventHandler();

	void linkParent(QPacman* parent);

private:
	//Overrides
	virtual void handleEvent(const sf::Event& ev) override;
	virtual std::string custom_log_header() const override;

	void keyEvent(const sf::Event& ev) const;
	uint16_t getKey(const sf::Event& ev) const;

	QPacman* parent;
};