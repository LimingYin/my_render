#include "Color.h"



Color::Color() : t(255), r(0), g(0), b(0)
{
	color = t << 24 || r << 16 || g << 8 || b;
}


Color::~Color()
{
}

Color::Color(unsigned int rr, unsigned int gg, unsigned int bb, unsigned int tt)
	: r(rr), g(gg), b(bb), t(tt)
{
	color = t << 24 | r << 16 | g << 8 | b;
}

Color Color::operator*(const float alpha) const
{
	return Color(r*alpha, g*alpha, b*alpha, t*alpha);
}

Color Color::operator+(const Color rhs) const
{
	return Color(r+rhs.r, g+rhs.g, b+rhs.b, t+rhs.t);
}


Color Color::red(255, 0, 0);
Color Color::white(255, 255, 255);
Color Color::green(0, 255, 0);
Color Color::blue(0, 0, 255);
Color Color::black(0, 0, 0);