#pragma once
#include <stdint.h>
#include <vector>

template<typename T>
struct Vec4
{
	T r, g, b, a;
};

template<typename T>
struct Vec3
{
	T r, g, b;
	static Vec3 blend_color(Vec3 dst, const Vec4<T> &src)
	{
		if (src.a > 0)
		{
			float alpha = 1/255*src.a;
			dst.r = uint8_t(alpha * float(src.r * dst.r) + dst.r);
			dst.g = uint8_t(alpha * float(src.g * dst.g) + dst.g);
			dst.b = uint8_t(alpha * float(src.b * dst.b) + dst.b);
			dst.a = 1;
			return dst;
		}

		dst.r = 0;
		dst.g = 0;
		dst.b = 0;
		dst.a = 0;
		return dst;
	}
};

struct Canvas
{
	Canvas(int w, int h);
	void set_pixel(int x, int y, const Vec4<uint8_t> &c);
	inline const uint8_t* get_texture() { return this->pixels.data(); }
private:
	inline int get_index(int x, int y) { return x + w * y; }
	std::vector<uint8_t> pixels;
	int w;
	int h;
};
