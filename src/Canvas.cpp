#include <Canvas.hpp>

Canvas::Canvas(int w, int h)
: w(w)
, h(h)
{
	this->pixels.resize(w*h*4, 255);
}

void Canvas::set_pixel(int x, int y, const Color &c)
{
	if (x >= 0 && x < this->w && y >= 0 && y < this->h)
	{
		int i = this->get_index(x, y) * 4;
		this->pixels[ i ] = c.r*255;
		this->pixels[i+1] = c.g*255;
		this->pixels[i+2] = c.b*255;
		this->pixels[i+3] = c.a*255;
	}
}
