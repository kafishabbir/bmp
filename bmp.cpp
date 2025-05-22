#include "bmp.h"

drw::Color::Color(int red, int green, int blue):
	red(red),
	green(green),
	blue(blue)
{}

std::string drw::Color::binary() const
{
	return
	{
		blue,
		green,
		red
	};
}

bool drw::Color::operator== (drw::Color other) const
{
	return red == other.red && blue == other.blue && green == other.green;
}


drw::Bmp::Hex::Hex(int value, int size):
	value(value),
	size(size)
{}

std::string drw::Bmp::Hex::binary() const
{
	std::string s(this->size, '\0');

	for(int i = 0; i < size; ++ i)
	{
		s[i] = (this->value >> (8 * i));
	}

	return s;
}

std::string drw::Bmp::hex_vector_to_binary(const std::vector<Hex>& hex_vec)
{
	std::string s;
	for(const Hex hex: hex_vec)
	{
		s += hex.binary();
	}

	return s;
}


int drw::Bmp::width_with_padding() const
{
	int multiple = 4;
	return ((this->width + multiple - 1) / multiple) * multiple;
}


drw::Bmp::Bmp(int width, int height, Color bg_color):
	width(width),
	height(height),
	data(
		std::vector<std::vector<Color>>(
			height,
			std::vector<Color>(width_with_padding(), bg_color)
		)
	)
{}



std::string drw::Bmp::binary_head() const
{
	const int SIZE_BMP_HEADER = 14;
	const int SIZE_DIB_HEADER = 40;
	const int SIZE_HEADER = SIZE_BMP_HEADER + SIZE_DIB_HEADER;
	const int size_file = SIZE_HEADER + size_data();

	// https://en.wikipedia.org/wiki/BMP_file_format
	// Bmp header
	const Hex bmp_header_bm_code_1('B', 1);
	const Hex bmp_header_bm_code_2('M', 1);
	const Hex bmp_header_size_file(size_file, 4);
	const Hex bmp_header_application_id(0, 4);
	const Hex bmp_header_data_offset(SIZE_HEADER, 4); // where to find data

	// Dib header
	const Hex dib_header_size_dib_header(SIZE_DIB_HEADER, 4);
	const Hex dib_header_width(this->width, 4);
	const Hex dib_header_height(this->height, 4);
	const Hex dib_header_planes(1, 2);
	const Hex dib_header_bits_per_pixel(24, 2);
	const Hex dib_header_compression(0, 4);
	const Hex dib_header_size_data(size_data(), 4);
	const Hex dib_header_resolution_x(1000, 4); // pixels per meter
	const Hex dib_header_resolution_y(1000, 4);
	const Hex dib_header_palette(0, 4);
	const Hex dib_header_important_colors(0, 4);

	return hex_vector_to_binary(
		{
			bmp_header_bm_code_1,
			bmp_header_bm_code_2,
			bmp_header_size_file,
			bmp_header_application_id,
			bmp_header_data_offset,

			dib_header_size_dib_header,
			dib_header_width,
			dib_header_height,
			dib_header_planes,
			dib_header_bits_per_pixel,
			dib_header_compression,
			dib_header_size_data,
			dib_header_resolution_x,
			dib_header_resolution_y,
			dib_header_palette,
			dib_header_important_colors,
		}
	);
}

int drw::Bmp::size_data() const
{
	return width_with_padding() * height * 3;
}

std::string drw::Bmp::binary_data() const
{
	std::string s;
	s.reserve(size_data());
	for(const auto& row: data)
	{
		for(const auto& cell: row)
		{
			s += cell.binary();
		}
	}
	return s;
}

std::string drw::Bmp::binary() const
{
	return binary_head() + binary_data();
}

void drw::Bmp::save(const std::string& filename) const
{
	std::ofstream fout(filename, std::ios::binary);
	const std::string& file = binary();
	fout.write(file.data(), file.size());
}

void drw::Bmp::draw_pixel(int x, int y, Color color)
{
	data[y][x] = color;
}

void drw::Bmp::draw_rectangle(int x1, int y1, int x2, int y2, Color color)
{
	int xmin = std::min(x1, x2);
	int xmax = std::max(x1, x2);

	int ymin = std::min(y1, y2);
	int ymax = std::max(y1, y2);

	for(int x = xmin; x <= xmax; ++ x)
	{
		for(int y = ymin; y <= ymax; ++ y)
		{
			data[y][x] = color;
		}
	}
}


drw::Color& drw::Bmp::operator()(int x, int y)
{
	return data[y][x];
}


