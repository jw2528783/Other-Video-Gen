#pragma once
#include <cstdint>
#define W 720
#define H 480	
extern unsigned char frame[H][W][3];
typedef unsigned char byte;

class Rectangle{
	public:
		Rectangle(int height,int width,int x,int y,byte red,byte 			green,byte blue){
			h = height;
			w = width;
			this->x = x;
			this->y = y;
			r = red;
			g = green;
			b = blue;
		};
		void drawrect(Rectangle r1);
		void clamp(int x,int y);
		byte r,g,b;
		int h,w;
		int x,y;
};

void Rectangle::drawrect(Rectangle r1){
	int r1x0=r1.x;
	int r1x1=r1.x+4*r1.w;
	int r1y0=r1.y;
	int r1y1=r1.y+4*r1.h;
	clamp(r1x0,r1y0);
	clamp(r1x1,r1y1);
	for(int y=r1y0;y<r1y1;++y){
		for(int x=r1x0;x<r1x1;++x){
			//multiplied x value to create choppy/blurry effect
			frame[y][5*x][0]=r1.r;
			frame[y][x][1]=r1.g;
			frame[y][x][2]=r1.b;
		}
	}
};

void Rectangle::clamp(int x,int y) {
	if(x<0)x=0; else if (x>=W)x=W-1;
	if(y<0)y=0; else if (y>=H)y=H-1;
};

