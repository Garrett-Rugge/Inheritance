#include "Rectangle.h"
#include "Frame.h"



Rectangle::Rectangle(){
	x = 0;
	y = 0;
	w = 0;
	h = 0;
	r = 0x00;
	g = 0x00;
	b = 0x00;
}
Rectangle::Rectangle(int x, int y, int w, int h, byte r, byte g, byte b){
	j = x;
	k = y;
	wid = w;
	height = h;
	red = r;
	green = g;
	blue = b;
}
// Main drawing code.
// Expand this function to add content to the video.

// Constrain point to frame.

void Rectangle::draw(){
	x = j;
	y = k;
	w = wid;
	h = height;
	r = red;
	g = green;
	b = blue;
	int x0 = x;
	int x1 = x + w;
	int y0 = y;
	int y1 = y + h;
	for (int y = y0; y < y1; ++y) {
		for (int x = x0; x < x1; ++x) {
			frame.setPixel(x, y, r, g, b);
		}
	}
}

void Rectangle::update(int l, int p){
	j+=l;
	k+=p;
}
