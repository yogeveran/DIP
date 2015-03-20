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
	if (argc != 2)
	{
		cout << " Usage: ImageToFlag ImageToLoadAndDisplay" << endl;
		return -1;
	}
	
	Mat src, warp_dst;
	src = imread(argv[1], IMREAD_COLOR);   // Read the file

	if (!src.data)                              // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -2;
	}
	

	/// Set the dst image the same type and size as src
	Size size(src.cols, 3*src.rows);
	warp_dst = Mat::zeros(size, src.type());
	warp_dst.setTo(Scalar(255, 255, 255));
	

	//Distort done here
	for (int y = 0; y < src.rows; y++){
		for (int x = 0; x < src.cols; x++){
			int new_y = y * (1 + sin(3 * MY_PI * x / src.cols)) / 2;
			if ((new_y<warp_dst.rows) && (x<warp_dst.cols))
				warp_dst.at<uchar>(new_y, x) = src.at<uchar>(y, x);
		}
	}
	

	//Done distort here

	namedWindow("Before", WINDOW_AUTOSIZE);  // Create a window for display.
	namedWindow("After", WINDOW_AUTOSIZE);   // Create a window for display.
	imshow("Before", src);                   // Show Before Image
	imshow("After", warp_dst);               // Show After  Image

	waitKey(0);                                          // Wait for a keystroke in the window
	return 0;
}

