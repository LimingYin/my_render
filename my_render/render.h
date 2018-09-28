#pragma once

#include "geometry.h"
#include "Color.h"

class render
{
public:
	render(int w = 0, int h = 0);
	~render();

	void setbackColor(int c);
	void setRenderColor(int c);

	void clean();

	void drawLine(Point2i start, Point2i end);
	void drawTriangle(Point2i a, Color color_a, Point2i b, Color color_b, Point2i c, Color color_c);

	int width, height;
	unsigned int *backBuffer;
	int r_col = (0x01 << 24) | (0x58 << 16) | (0x58 << 8) | (0x58 << 0);
	int b_col = (0x01 << 24) | (0x58 << 16) | (0x58 << 8) | (0x58 << 0);
};

