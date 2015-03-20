// ImageToFlag.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include "core.hpp"
#include "highgui.hpp"
#include "imgproc.hpp"
#include "opencv.hpp"
#include <iostream>
# define MY_PI           3.14159265358979323846

using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
	int wave_frequency = 3;//Default wave frequency
	double amplitude = 0.03;//Defined after load of picture to be 3%
	if (argc < 2)
	{
		cout << " Usage: ImageToFlag ImageToLoadAndDisplay" << endl;
		waitKey(0);                              // Wait for a keystroke in the window
		return -1;
	}
	if (argc > 2){
		wave_frequency = atoi(argv[2]);
	}
	
	Mat src, warp_dst;
	src = imread(argv[1], IMREAD_COLOR);   // Read the file
	amplitude = amplitude * src.rows;//% of picture height.

	if ((!src.data)||src.empty())                              // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		waitKey(0);                              // Wait for a keystroke in the window
		return -2;
	}
	

	/// Set the dst image the same type as src but in size + amplitude for height.
	Size size(src.cols, src.rows + 2*amplitude);
	//Create destination Matrix
	warp_dst = Mat::zeros(size, src.type());
	//Set Background to white.
	warp_dst.setTo(Scalar(255, 255, 255));
	

	//Distort done here
	for (int y = 0; y < src.rows; y++){
		for (int x = 0; x < src.cols; x++){
			int new_y = (int)( y + amplitude + (int)(amplitude * sin(wave_frequency * MY_PI * x / src.cols)));
			warp_dst.at<Vec3b>(new_y, x) = src.at<Vec3b>(y, x);
		}
	}
	//Done distort here

	namedWindow("Before", WINDOW_AUTOSIZE);  // Create a window for display.
	namedWindow("After", WINDOW_AUTOSIZE);   // Create a window for display.
	imshow("Before", src);                   // Show Before Image
	imshow("After", warp_dst);               // Show After  Image

	waitKey(0);                              // Wait for a keystroke in the window
	return 0;
}

