#include "Object.h"
#include "Frame.h"
#pragma once

extern Frame frame;

typedef unsigned char byte;

class Rectangle : public Object{
	public:
		Rectangle();
		Rectangle(int x, int y, int w, int h, byte r, byte g, byte b);
		void draw_rect();	
		virtual void draw();
		virtual void update(int l, int p);
	private:
		int x, y, w, h, j, k, wid, height;
		byte r, g, b, red, green, blue;
		byte * pixels;
};
