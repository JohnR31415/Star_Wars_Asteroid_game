#pragma once
#pragma warning(disable:4505)
#ifndef COLOR
#define COLOR
#include "..\Math\Random.h"
#include "Core.h"
using Core::RGB;

class Color
{
public:
	int r, g, b;
};


static RGB varColor(RGB color, int var)
{
	int r, g, b;
	Random rand;
	r = GetRValue(color);
	g = GetGValue(color);
	b = GetBValue(color);

	r = r + int(rand.randomInRange((float)-var, (float)var));
	if(r < 0) 
		r = 0;
	if(r > 255)
		r = 255;

	g = g + int(rand.randomInRange((float)-var, (float)var));
	if(g < 0) 
		g = 0;
	if(g > 255)
		g = 255;

	b = b + int(rand.randomInRange((float)-var, (float)var));
	if(b < 0) 
		b = 0;
	if(b > 255)
		b = 255;

	return RGB(r, g, b);
}
static RGB brightness(RGB color, float brightValue)
{
	return RGB(
		int(GetRValue(color) * brightValue),
		int(GetGValue(color) * brightValue),
		int(GetBValue(color) * brightValue));
}

#endif