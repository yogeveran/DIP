// ImageToFlag.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "core.hpp"
#include "highgui.hpp"
#include "imgproc.hpp"
#include "opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
	if (argc != 2)
	{
		cout << " Usage: display_image ImageToLoadAndDisplay" << endl;
		return -1;
	}
	
	Mat src, warp_dst;
	src = imread(argv[1], IMREAD_COLOR);   // Read the file

	if (!src.data)                              // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	/// Set the dst image the same type and size as src
	warp_dst = Mat::zeros(src.rows, src.cols, src.type());
	warp_dst.setTo(Scalar(255, 255, 255));


	//Distort done here
	Mat t(2, 3, CV_64F, Scalar(0.0));

	t.at<double>(0, 0) = 1;
	t.at<double>(1, 1) = 1;
	t.at<double>(0, 1) = -tan(0.17);
	//    t.at<double>(2,2) = 1;


	Mat dest;
	Size size(src.cols, src.rows);
	warpAffine(src, dest, t, size, INTER_LINEAR, BORDER_CONSTANT);
	//end distort here

	namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
	namedWindow("Display window2", WINDOW_AUTOSIZE);// Create a window for display.
	imshow("Display window", src);                   // Show our image inside it.
	imshow("Display window2", dest);                   // Show our image inside it.

	waitKey(0);                                          // Wait for a keystroke in the window
	return 0;
}

