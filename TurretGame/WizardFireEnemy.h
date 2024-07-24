#pragma once

#include "Enemy.h"

class WizardFireEnemy : public Enemy
{
public:
	WizardFireEnemy();

	virtual void Update(unsigned int frame) override;
	virtual void Draw() override;

	unsigned int GetLocalFramecount() const;

private:
	int stopPointY;
	bool hoverMode;

	unsigned int localFramecount;

};