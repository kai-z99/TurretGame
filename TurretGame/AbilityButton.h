#pragma once
#include "Button.h"
#include "types.h"

class AbilityButton : public Button
{
public:
	AbilityButton(int posX, int posY, TurretAbility ability);

	virtual void Draw() override;
	virtual void Update(int mouseX, int mouseY) override;
	void SetProgress(float barProgress);
	void SetTotalCharges(int charges);
	void SetCurrentCharges(int charges);
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
	int totalCharges;
	int currentCharges;
	Texture2D* texture;

};

