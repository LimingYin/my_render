#include "render.h"
#include <cmath>
#include <memory>
#include <algorithm>


render::render(int w, int h):width(w), height(h)
{
	backBuffer = new unsigned int[w*h];
	memset(backBuffer, b_col, width*height * 4);
}


render::~render()
{
}

void render::setbackColor(int c)
{
	b_col = c;
}

void render::setRenderColor(int c)
{
	r_col = c;
}

void render::clean()
{
	memset(backBuffer, b_col, width*height * 4);
}

void render::drawLine(Point2i start, Point2i end)
{
	// point
	if (start.x == end.x && end.y == end.y)
	{
		backBuffer[start.x + start.y*width] = r_col;
	}
	else if (start.x == end.x) // slope = inf
	{
		int inc = start.y < end.y ? 1 : -1;
		for (int x = start.x, y = start.y; y != end.y; y += inc)
		{
			backBuffer[x + y * width] = r_col;
		}
		backBuffer[end.x + end.y*width] = r_col;
	}
	else if (start.y == end.y) // slope = 0
	{
		int inc = start.x < end.x ? 1 : -1;
		for (int x = start.x, y = start.y; x != end.x; x += inc)
		{
			backBuffer[x + y * width] = r_col;
		}
		backBuffer[end.x + end.y*width] = r_col;
	}
	else
	{
		// Bresenham
		int dx = end.x - start.x;
		int dy = end.y - start.y;
		int inc_x = dx > 0 ? 1 : -1;
		int inc_y = dy > 0 ? 1 : -1;
		dx = abs(dx);
		dy = abs(dy);
		int dx2 = dx << 1;
		int dy2 = dy << 1;

		if (dx > dy) // slope < 1
		{
			int e = -dx;
			for (int x = start.x, y = start.y; x != end.x; x += inc_x)
			{
				backBuffer[x + y * width] = r_col;
				e += dy2;
				if (e > 0)
				{
					y += inc_y;
					e -= dx2;
				}
			}
		}
		else // slope > 1
		{
			int e = -dy;
			for (int x = start.x, y = start.y; y != end.y; y += inc_y)
			{
				backBuffer[x + y * width] = r_col;
				e += dx2;
				if (e > 0)
				{
					x += inc_x;
					e -= dy2;
				}
			}
		}
	}
}

void render::drawTriangle(Point2i a, Color color_a, Point2i b, Color color_b, Point2i c, Color color_c)
{
	Vector2i ab(b - a);
	Vector2i ac(c - a);

	float area = ab.x*ac.y - ac.x*ab.y;

	if (abs(area) < 0.0001)
	{
		return;
	}

	int xmin = std::min(std::min(a.x, b.x), c.x);
	int xmax = std::max(std::max(a.x, b.x), c.x);
	int ymin = std::min(std::min(a.y, b.y), c.y);
	int ymax = std::max(std::max(a.y, b.y), c.y);

	for(int x = xmin; x <= xmax; ++x)
		for (int y = ymin; y <= ymax; ++y)
		{
			Vector2i ap(x - a.x, y - a.y);
			int areaB = ap.x*ac.y - ac.x*ap.y;
			int areaC = ab.x*ap.y - ap.x*ab.y;
			float beta = areaB / area;
			float gamma = areaC / area;
			float alpha = 1 - beta - gamma;

			if (alpha >= 0 && beta >= 0 && gamma >= 0)
			{
				Color colInt = color_a * alpha + color_b * beta + color_c * gamma;
				backBuffer[y*width + x] = colInt.color;
			}
		}
	
}


