#pragma once
#include "Button.h"
#include "types.h"

class AbilityButton : public Button
{
public:
	AbilityButton(int posX, int posY, TurretAbility ability);

	virtual void Draw() override;
	virtual void Update(int mouseX, int mouseY) override;
	void SetProgress(float progress);
	void SetTotalCharges(int charges);
	void SetCurrentCharges(int charges);

	TurretAbility GetAbility();
	int GetCurrentCharges() const;

	static const int width;
	static const int height;

private:
	virtual bool MouseCollide(int mouseX, int mouseY);

	TurretAbility ability;
	float progress = 0.0f; //how much bar is filled
	int totalCharges;
	int currentCharges;
	Texture2D texture;

};

