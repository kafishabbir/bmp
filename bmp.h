#ifndef DRW_BMP_H
#define DRW_BMP_H

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

namespace drw
{
	class Color
	{
		char red;
		char green;
		char blue;

	public:
		Color() = default;
		Color(int red, int green, int blue);

		std::string binary() const;
		bool operator==(Color other) const;
	};

	const Color black(0, 0, 0);
	const Color grey_dark(64, 64, 64);
	const Color grey(150, 150, 150);
	const Color grey_light(200, 200, 200);
	const Color white(255, 255, 255);
	const Color brown(128, 0, 0);
	const Color red(255, 0, 0);
	const Color orange(255, 165, 0);
	const Color yellow(255, 255, 0);
	const Color green(0, 255, 0);
	const Color green_dark(0, 128, 0);
	const Color blue(0, 0, 255);
	const Color cyan(0, 255, 255);
	const Color magenta(255, 0, 255);
	const Color purple(128, 0, 128);

	class Bmp
	{
		const int width;
		const int height;
		std::vector<std::vector<Color>> data;
		class Hex
		{
			const int value;
			const int size;

			public:

			Hex(int value, int size);
			std::string binary() const;
		};

		static std::string hex_vector_to_binary(const std::vector<Hex>& hex_vec);

		int size_data() const;
		int width_with_padding() const;
		std::string binary_head() const;
		std::string binary_data() const;
		std::string binary() const;

	public:
		Bmp() = delete;
		Bmp(int width, int height, Color bg_color=white);

		void save(const std::string& filename) const;
		void draw_pixel(int x, int y, Color color=black);
		void draw_rectangle(int x1, int y1, int x2, int y2, Color color=black);
		Color& operator()(int x, int y);
	};
}

#endif
