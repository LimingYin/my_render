#pragma once
class Color
{
public:
	Color();
	~Color();

	Color(unsigned int rr, unsigned int gg, unsigned int bb, unsigned int tt = 255);

	Color operator*(const float alpha) const;
	Color operator+(const Color rhs) const;

	static Color red;
	static Color white;
	static Color green;
	static Color blue;
	static Color black;

	unsigned int t;
	unsigned int r;
	unsigned int g;
	unsigned int b;

	unsigned int color;
};

