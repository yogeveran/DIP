// ImageToFlag.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include "core.hpp"
#include "highgui.hpp"
#include "imgproc.hpp"
#include "opencv.hpp"
#include <math.h>
#include <iostream>
# define MY_PI           3.14159265358979323846

using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
	int wave_frequency = 3;//Default wave frequency
	double amplitude = 0.03;//Defined after load of picture to be 3%
	if (argc != 4)
	{
		cout << " Usage: ImageToFlag ImageToLoadAndDisplay" << endl;
		waitKey(0);                              // Wait for a keystroke in the window
		return -1;
	}
	wave_frequency = atoi(argv[2]);
	char* interpolation = argv[3];
	
	Mat src, warp_dst, warp_dst_inter;
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
	warp_dst_inter = Mat::zeros(size, src.type());
	//Set Background to white.
	warp_dst.setTo(Scalar(255, 255, 255));
	warp_dst_inter.setTo(Scalar(255, 255, 255));
	

	//Distort done here using forward scanning with no interpolation.
	for (int y = 0; y < src.rows; y++){
		for (int x = 0; x < src.cols; x++){
			int new_y = (int)(y + amplitude * (1 + sin(wave_frequency * MY_PI * x / src.cols)));
			warp_dst.at<Vec3b>(new_y, x) = src.at<Vec3b>(y, x);
		}
	}
	cout << "done forward  \n";

	//Distort done here using backward scanning with interpolation.
	for (int new_y = 0; new_y < warp_dst_inter.rows; new_y++){
		for (int x = 0; x < warp_dst_inter.cols; x++){
			double y = new_y - amplitude * ( 1 + sin(wave_frequency * MY_PI * x / src.cols));
			int src_y;
			switch (interpolation[0]){
			case 'n':
				src_y = ((int)round(y)) % src.rows;
				break;
			case 'b'://Bi-Linear ------ Need To Do
			case 'c'://Cubic	 ------ Need To Do
			default:
				src_y = ((int)round(y)) % src.rows;
				break;
				
			}
			
			if (src_y >= 0)
				warp_dst_inter.at<Vec3b>(new_y, x) = src.at<Vec3b>(src_y, x);
		}
	}
	cout << "done backward  \n";

	namedWindow("Before", WINDOW_AUTOSIZE);  // Create a window for display.
	namedWindow("After", WINDOW_AUTOSIZE);   // Create a window for display.
	namedWindow("After Inter", WINDOW_AUTOSIZE);   // Create a window for display.
	imshow("Before", src);                   // Show Before Image
	imshow("After", warp_dst);               // Show After  Image
	imshow("After Inter", warp_dst_inter);   // Create a window for display.

	waitKey(0);                              // Wait for a keystroke in the window
	return 0;
}

