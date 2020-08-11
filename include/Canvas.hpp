#pragma once
#include <stdint.h>
#include <vector>

struct Color
{
	uint8_t r, g, b, a;
};

struct Canvas
{
	Canvas(int w, int h);
	void set_pixel(int x, int y, const Color &c);
	inline const uint8_t* get_texture() { return this->pixels.data(); }
private:
	inline int get_index(int x, int y) { return x + w * y; }
	std::vector<uint8_t> pixels;
	int w;
	int h;
};
