#pragma once
#include "VisualEffect.h"


class CoinSplashEffect : public VisualEffect
{
public:
	CoinSplashEffect(Vector2 pos, int amount);
	virtual void UpdateAndDraw() override;

private:
	int coinAmount;
};