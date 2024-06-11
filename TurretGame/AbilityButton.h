#pragma once
#include "Button.h"
#include "types.h"

class AbilityButton : public Button
{
public:
	AbilityButton(int posX, int posY, TurretAbility ability);

	virtual void Draw() override;
	virtual void Update(int mouseX, int mouseY) override;
	void SetBarProgress(float barProgress);
	void SetCooldownProgress(float barProgress);
	
	TurretAbility GetAbility();
	int GetCurrentCharges() const;

	static const int width;
	static const int height;

private:
	virtual bool MouseCollide(int mouseX, int mouseY);

	TurretAbility ability;
	float barProgress = 0.0f; //how much bar is filled
	float cooldownProgress = 0.0f; //how much the bar is shaded
	Texture2D* texture;

};

