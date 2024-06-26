#pragma once
#include "Button.h"
#include "types.h"

class UpgradeButton : public Button
{
public:
	UpgradeButton(int posX, int posY, Upgrade upgrade);

	virtual void Draw() override;
	virtual void Update(int mouseX, int mouseY) override;

	Upgrade GetUpgrade() const;
	int GetPrice() const;

	void SetPrice(int price);

private:
	virtual bool MouseCollide(int mouseX, int mouseY);
	Texture2D* texture;

	Upgrade upgrade;
	int price;
};