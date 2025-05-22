#include "bmp.h"


int main()
{
	drw::Bmp image(4, 4);
	image.save("white.bmp");
	image.draw_pixel(0, 0, drw::blue);
	image.save("00blue.bmp");
	image.draw_rectangle(3, 2, 0, 1, drw::green);
	image.save("green-rectangle.bmp");
	image(3, 3) = drw::yellow;
	image.save("points.bmp");
	return 0;
}
