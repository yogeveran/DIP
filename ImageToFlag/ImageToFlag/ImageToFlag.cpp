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
	int amplitude = 20; //Default Height of sinus wave.
	if (argc < 2)
	{
		cout << " Usage: ImageToFlag ImageToLoadAndDisplay" << endl;
		return -1;
	}
	if (argc > 2){
		wave_frequency = atoi(argv[2]);
	}
	
	Mat src, warp_dst;
	src = imread(argv[1], IMREAD_COLOR);   // Read the file


	if ((!src.data)||src.empty())                              // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -2;
	}
	

	/// Set the dst image the same type as src but in size + amplitude for height.
	Size size(src.cols, src.rows + 2*amplitude);
	//Create destination Matrix
	warp_dst = Mat::zeros(size, src.type());
	//Set Background to white.
	warp_dst.setTo(Scalar(255, 255, 255));
	

	//Distort done here
	cout << "rows: " << src.rows << " cols: " << src.cols << "\n";
	

	for (int y = 0; y < src.rows; y++){
		for (int x = 0; x < src.cols; x++){
			int new_y = (warp_dst.rows + y + amplitude + (int)(amplitude * sin(wave_frequency * MY_PI * x / src.cols))) % warp_dst.rows;
			warp_dst.at<Vec3b>(new_y, x) = src.at<Vec3b>(y, x);
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

