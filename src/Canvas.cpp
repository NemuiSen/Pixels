#include <Canvas.hpp>

Canvas::Canvas(int w, int h)
: w(w)
, h(h)
{
	this->pixels.resize(w*h*4, 255);
}

void Canvas::set_pixel(int x, int y, const Vec4<uint8_t> &c)
{
	if (x >= 0 && x < this->w && y >= 0 && y < this->h)
	{
		int i = this->get_index(x, y) * 4;
		this->pixels[ i ] = c.r;
		this->pixels[i+1] = c.g;
		this->pixels[i+2] = c.b;
		this->pixels[i+3] = c.a;
	}
}
