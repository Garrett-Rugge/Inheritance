
 
#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <stdio.h>
#include <cassert>
#include <cstring>
#include "Image.h"
#include "Rectangle.h"



Frame frame(720, 480);
const double frames_per_second = 30; 
const int duration_in_seconds = 3;


using namespace std;


int main(int argc, char * argv[]) {
	// Construct the ffmpeg command to run.
	const char * cmd = 
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
	Rectangle r(50, 50, 100, 100, 0x00, 0xff, 0x00);
	Rectangle e(0, 0, 50, 50, 0xff, 0x00, 0x00);
#ifdef _WIN32
	FILE * pipe = _popen(cmd, "wb");
#else
	FILE * pipe = popen(cmd, "w");
#endif
	if (pipe == 0) {
		cout << "error: " << strerror(errno) << endl;
		return 1;
	}
	Image image;
	image.load("ducky.bmp", 100, 100, 100, 100);
	Image kappa;
	kappa.load("kappa.bmp", 200, 200, 100, 100);
	// Write video frames into the pipe.
	int num_frames = duration_in_seconds * frames_per_second;
	for (int i = 0; i < num_frames; ++i) {
		r.draw();
		e.draw();
		image.draw();
		kappa.draw();
		frame.write(pipe);
		kappa.update(3, 2);
		image.update(1, 3);
		r.update(1, 1);
		e.update(5, 0);
		frame.clear();
	}
	
	fflush(pipe);
#ifdef _WIN32
	_pclose(pipe);
#else
	pclose(pipe);
#endif
	cout << "num_frames: " << num_frames << endl;
	cout << "Done." << endl;

	return 0;
}
