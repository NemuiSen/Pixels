#pragma once
#include <stdint.h>
#include <vector>

struct Color
{
	Color()
	: r(0)
	, g(0)
	, b(0)
	, a(0)
	{}

	Color(float R, float G, float B, float A = 0)
	: r(R)
	, g(G)
	, b(B)
	, a(A)
	{}

	void set_int(const uint32_t &c)
	{
		r = (c >> 24) / 255;
		g = (c >> 16) / 255;
		b = (c >>  8) / 255;
		a = (c >>  0) / 255;
	}

	uint32_t get_int()
	{
		return ((uint8_t)r*255 << 24)|
			   ((uint8_t)g*255 << 16)|
			   ((uint8_t)b*255 <<  8)|
			   ((uint8_t)a*255 <<  0);
	}

	static Color blend_color(const Color &dst, const Color &src)
	{
		Color out;
		out.a = src.a + dst.a * (1 - src.a);

		out.r = (src.r * src.a + dst.r * dst.a * (1 - src.a)) / out.a;
		out.g = (src.g * src.a + dst.g * dst.a * (1 - src.a)) / out.a;
		out.b = (src.b * src.a + dst.b * dst.a * (1 - src.a)) / out.a;

		return out;
	}

	float r, g, b, a;
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
