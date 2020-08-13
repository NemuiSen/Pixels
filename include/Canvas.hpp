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

	Color(float R, float G, float B, float A = 255)
	: r(R)
	, g(G)
	, b(B)
	, a(A)
	{}

	Color(const uint32_t &c) { this->set_int(c); }

	void set_int(const uint32_t &c)
	{
		r = static_cast<float>((c & 0xff000000) >> 24) / 255.0;
		g = static_cast<float>((c & 0x00ff0000) >> 16) / 255.0;
		b = static_cast<float>((c & 0x0000ff00) >>  8) / 255.0;
		a = static_cast<float>((c & 0x000000ff) >>  0) / 255.0;
	}

	uint32_t get_int()
	{
		return (static_cast<uint8_t>(r*255.0) << 24)|
			   (static_cast<uint8_t>(g*255.0) << 16)|
			   (static_cast<uint8_t>(b*255.0) <<  8)|
			   (static_cast<uint8_t>(a*255.0) <<  0);
	}

	//formula
	//https://ciechanow.ski/alpha-compositing/#combining-colors
	static Color blend_color(const Color &dst, const Color &src)
	{
		Color out;
		out.a = src.a + dst.a * (1 - src.a);

		if (out.a > 0)
		{
			out.r = (src.r * src.a + dst.r * dst.a * (1 - src.a)) / out.a;
			out.g = (src.g * src.a + dst.g * dst.a * (1 - src.a)) / out.a;
			out.b = (src.b * src.a + dst.b * dst.a * (1 - src.a)) / out.a;
			return out;
		}

		out.r = 0;
		out.g = 0;
		out.b = 0;
		return out;
	}

	float r;
	float g;
	float b;
	float a;
};

struct Canvas
{
	Canvas(int w, int h);
	void set_pixel(int x, int y, const Color &c);
	Color get_pixel(int x, int y);
	inline const uint8_t* get_texture() { return this->pixels.data(); }
private:
	inline int get_index(int x, int y) { return x + w * y; }
	std::vector<uint8_t> pixels;
	int w;
	int h;
};
