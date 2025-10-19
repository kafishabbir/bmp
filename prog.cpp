#include "bmp.h"


int main()
{
	drw::Bmp image(400, 400);
	image.save("white.bmp");
	image.draw_pixel(0, 0, drw::blue);
	image.save("00blue.bmp");
	image.draw_rectangle(300, 200, 0, 100, drw::green);
	image.save("green-rectangle.bmp");
	image(300, 300) = drw::yellow;
	image.save("points.bmp");
	return 0;
}
