#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <stdio.h>
#include <cassert>
#include <cstring>
#include <cstdint>
#include "rectangle.cpp"

const double fps=30; 
const int duration=3;
#define W 720
#define H 480	
unsigned char frame[H][W][3];
using namespace std;

void clear(){memset(frame, 0, sizeof(frame));}

bool outside(int *x,int *y){
	return *x<0 or *x>=W or *y<0 or *y>= H;
};



void drawframe(double t,Rectangle r1,Rectangle r2,Rectangle r3){
	clear();
	const double pps = 80;
	Rectangle newR1=r1;
	newR1.x=r1.x+t *pps;
	newR1.y=r1.y+t *pps;
	Rectangle newR2=r2;
	newR2.x=r2.x+t *pps;
	newR2.y=r2.y+t *pps;
	Rectangle newR3=r3;
	newR3.x=r3.x+t *pps;
	newR3.y=r3.y+t *pps;
	r1.drawrect(newR1);
	r2.drawrect(newR2);
	r3.drawrect(newR3);
};

int main(int argc, char * argv[]){	
	Rectangle r1(20,25,51,152,0xff,0x00,0x00);
	Rectangle r2(10,12,25,75,0xff,0x00,0x00);
	Rectangle r3(10,12,0,0,0x00,0xff,0x00);
	// Construct the ffmpeg command to run.
	const char *cmd = 
		"ffmpeg              "
		"-y                  "
		"-hide_banner        "
		"-f rawvideo         " // input to be raw video data
		"-pixel_format rgb24 "
		"-video_size 720x480 "
		"-r 60               " // frames per second
		"-i -                " // read data from the standard input stream
		"-pix_fmt yuv420p    " // to render with Quicktime
		"-vcodec mpeg4       "
		"-an                 " // no audio
		"-q:v 5              " // quality level; 1 <= q <= 32
		"output.mp4          ";

	// Run the ffmpeg command and get pipe to write into its standard input stream.
	FILE *pipe=popen(cmd,"w");
	if (pipe == 0) {
		cout<<"error: "<<strerror(errno)<<endl;
		return 1;
	}
	// Write video frames into the pipe.
	int numframes=duration*fps;
	for(int i=0;i<numframes;++i){
		double time=i/fps;
		drawframe(time,r1,r2,r3);
		fwrite(frame,3,W*H,pipe);
	}
	fflush(pipe);
	pclose(pipe);
	cout<<"\n\n\nnum_frames: "<<numframes<<endl;
	cout<<"Done.\n"<<endl;
	return 0;
}
