#include "renderable.h"

Renderable::Renderable(float xin, float yin)
{
    x = xin;
    y = yin;
    r = 0.;
    tex = 0.;
}

Renderable::~Renderable()
{
    //dtor
}

void Renderable::setTex(int img)
{
    tex = img;
}

int Renderable::getTex()
{
    return tex;
}

float Renderable::getX()
{
	return x;
}

void Renderable::setX(float newX)
{
	x = newX;
}

float Renderable::getY()
{
	return y;
}

void Renderable::setY(float newY)
{
	y = newY;
}

float Renderable::getR()
{
	return r;
}

void Renderable::setR(float newR)
{
	r = newR;
}
