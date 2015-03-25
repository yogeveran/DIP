// ImageToFlag.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "core.hpp"
#include "highgui.hpp"
#include "imgproc.hpp"
#include "opencv.hpp"
#include <math.h>
#include <iostream>
#define MY_PI 3.14159265358979323846
#define MAT_SIZE 4
using namespace cv;
using namespace std;
Mat leftUp, leftDown, rightUp, rightDown;
Mat src, dst, dst_inter, srcWithMirror;

bool in_Range(double value, int from, int to){
	return (from <= floor(value)) && (ceil(value) < to);
}
float uFunc(float d){
	if (d < 1 && d >= 0){
		return (3 / 2)*pow(d, 3) - (5 / 2)*pow(d, 2) + 1;
	}
	else if (d < 2 && d >= 1){
		return (-3 / 2)*pow(d, 3) + (5 / 2)*pow(d, 2) - 4 * d + 2;
	}
	else
		return 0;
}
void calcLeftUp(){
	Mat leftUpX = Mat::zeros(MAT_SIZE, MAT_SIZE, CV_32F);
	Mat leftUpY = Mat::zeros(MAT_SIZE, MAT_SIZE, CV_32F);
	leftUpX.at<float>(0, 0) = 7 / 4; leftUpY.at<float>(0, 0) = 7 / 4;
	leftUpX.at<float>(0, 1) = 3 / 4; leftUpY.at<float>(0, 1) = 7 / 4;
	leftUpX.at<float>(0, 2) = 1 / 4; leftUpY.at<float>(0, 2) = 7 / 4;
	leftUpX.at<float>(0, 3) = 5 / 4; leftUpY.at<float>(0, 3) = 7 / 4;
	leftUpX.at<float>(1, 0) = 7 / 4; leftUpY.at<float>(1, 0) = 7 / 4;
	leftUpX.at<float>(1, 1) = 3 / 4; leftUpY.at<float>(1, 1) = 3 / 4;
	leftUpX.at<float>(1, 2) = 1 / 4; leftUpY.at<float>(1, 2) = 3 / 4;
	leftUpX.at<float>(1, 3) = 5 / 4; leftUpY.at<float>(1, 3) = 3 / 4;
	leftUpX.at<float>(2, 0) = 7 / 4; leftUpY.at<float>(2, 0) = 1 / 4;
	leftUpX.at<float>(2, 1) = 3 / 4; leftUpY.at<float>(2, 1) = 1 / 4;
	leftUpX.at<float>(2, 2) = 1 / 4; leftUpY.at<float>(2, 2) = 1 / 4;
	leftUpX.at<float>(2, 3) = 5 / 4; leftUpY.at<float>(2, 3) = 1 / 4;
	leftUpX.at<float>(3, 0) = 7 / 4; leftUpY.at<float>(3, 0) = 5 / 4;
	leftUpX.at<float>(3, 1) = 3 / 4; leftUpY.at<float>(3, 1) = 5 / 4;
	leftUpX.at<float>(3, 2) = 1 / 4; leftUpY.at<float>(4, 2) = 5 / 4;
	leftUpX.at<float>(3, 3) = 5 / 4; leftUpY.at<float>(5, 3) = 5 / 4;
	float sumForNormal = 0;
	for (int i = 0; i < MAT_SIZE; i++){
		for (int j = 0; j < MAT_SIZE; j++){
			float uFuncAns = uFunc(leftUpX.at<float>(i, j)) * uFunc(leftUpY.at<float>(i, j));
			leftUp.at<float>(i, j) = uFuncAns;
			sumForNormal += uFuncAns;
		}
	}
	for (int i = 0; i < MAT_SIZE; i++){
		for (int j = 0; j < MAT_SIZE; j++){
			leftUp.at<float>(i, j) = leftUp.at<float>(i, j) / sumForNormal;
		}
	}
}
void calcLeftDown(){
	Mat leftDownX = Mat::zeros(MAT_SIZE, MAT_SIZE, CV_32F);
	Mat leftDownY = Mat::zeros(MAT_SIZE, MAT_SIZE, CV_32F);
	leftDownX.at<float>(0, 0) = 7 / 4; leftDownY.at<float>(0, 0) = 5 / 4;
	leftDownX.at<float>(0, 1) = 3 / 4; leftDownY.at<float>(0, 1) = 5 / 4;
	leftDownX.at<float>(0, 2) = 1 / 4; leftDownY.at<float>(0, 2) = 5 / 4;
	leftDownX.at<float>(0, 3) = 5 / 4; leftDownY.at<float>(0, 3) = 5 / 4;
	leftDownX.at<float>(1, 0) = 7 / 4; leftDownY.at<float>(1, 0) = 1 / 4;
	leftDownX.at<float>(1, 1) = 3 / 4; leftDownY.at<float>(1, 1) = 1 / 4;
	leftDownX.at<float>(1, 2) = 1 / 4; leftDownY.at<float>(1, 2) = 1 / 4;
	leftDownX.at<float>(1, 3) = 5 / 4; leftDownY.at<float>(1, 3) = 1 / 4;
	leftDownX.at<float>(2, 0) = 7 / 4; leftDownY.at<float>(2, 0) = 3 / 4;
	leftDownX.at<float>(2, 1) = 3 / 4; leftDownY.at<float>(2, 1) = 3 / 4;
	leftDownX.at<float>(2, 2) = 1 / 4; leftDownY.at<float>(2, 2) = 3 / 4;
	leftDownX.at<float>(2, 3) = 5 / 4; leftDownY.at<float>(2, 3) = 3 / 4;
	leftDownX.at<float>(3, 0) = 7 / 4; leftDownY.at<float>(3, 0) = 7 / 4;
	leftDownX.at<float>(3, 1) = 3 / 4; leftDownY.at<float>(3, 1) = 7 / 4;
	leftDownX.at<float>(3, 2) = 1 / 4; leftDownY.at<float>(4, 2) = 7 / 4;
	leftDownX.at<float>(3, 3) = 5 / 4; leftDownY.at<float>(5, 3) = 7 / 4;
	float sumForNormal = 0;
	for (int i = 0; i < MAT_SIZE; i++){
		for (int j = 0; j < MAT_SIZE; j++){
			float uFuncAns = uFunc(leftDownX.at<float>(i, j)) * uFunc(leftDownY.at<float>(i, j));
			leftDown.at<float>(i, j) = uFuncAns;
			sumForNormal += uFuncAns;
		}
	}
	for (int i = 0; i < MAT_SIZE; i++){
		for (int j = 0; j < MAT_SIZE; j++){
			leftDown.at<float>(i, j) = leftDown.at<float>(i, j) / sumForNormal;
		}
	}
}
void calcRightUp(){
	Mat rightUpX = Mat::zeros(MAT_SIZE, MAT_SIZE, CV_32F);
	Mat rightUpY = Mat::zeros(MAT_SIZE, MAT_SIZE, CV_32F);
	rightUpX.at<float>(0, 0) = 5 / 4; rightUpY.at<float>(0, 0) = 7 / 4;
	rightUpX.at<float>(0, 1) = 1 / 4; rightUpY.at<float>(0, 1) = 7 / 4;
	rightUpX.at<float>(0, 2) = 3 / 4; rightUpY.at<float>(0, 2) = 7 / 4;
	rightUpX.at<float>(0, 3) = 7 / 4; rightUpY.at<float>(0, 3) = 7 / 4;
	rightUpX.at<float>(1, 0) = 5 / 4; rightUpY.at<float>(1, 0) = 3 / 4;
	rightUpX.at<float>(1, 1) = 1 / 4; rightUpY.at<float>(1, 1) = 3 / 4;
	rightUpX.at<float>(1, 2) = 3 / 4; rightUpY.at<float>(1, 2) = 3 / 4;
	rightUpX.at<float>(1, 3) = 7 / 4; rightUpY.at<float>(1, 3) = 3 / 4;
	rightUpX.at<float>(2, 0) = 5 / 4; rightUpY.at<float>(2, 0) = 1 / 4;
	rightUpX.at<float>(2, 1) = 1 / 4; rightUpY.at<float>(2, 1) = 1 / 4;
	rightUpX.at<float>(2, 2) = 3 / 4; rightUpY.at<float>(2, 2) = 1 / 4;
	rightUpX.at<float>(2, 3) = 7 / 4; rightUpY.at<float>(2, 3) = 1 / 4;
	rightUpX.at<float>(3, 0) = 5 / 4; rightUpY.at<float>(3, 0) = 5 / 4;
	rightUpX.at<float>(3, 1) = 1 / 4; rightUpY.at<float>(3, 1) = 5 / 4;
	rightUpX.at<float>(3, 2) = 3 / 4; rightUpY.at<float>(4, 2) = 5 / 4;
	rightUpX.at<float>(3, 3) = 7 / 4; rightUpY.at<float>(5, 3) = 5 / 4;
	float sumForNormal = 0;
	for (int i = 0; i < MAT_SIZE; i++){
		for (int j = 0; j < MAT_SIZE; j++){
			float uFuncAns = uFunc(rightUpX.at<float>(i, j)) * uFunc(rightUpY.at<float>(i, j));
			rightUp.at<float>(i, j) = uFuncAns;
			sumForNormal += uFuncAns;
		}
	}
	for (int i = 0; i < MAT_SIZE; i++){
		for (int j = 0; j < MAT_SIZE; j++){
			rightUp.at<float>(i, j) = rightUp.at<float>(i, j) / sumForNormal;
		}
	}
}
void calcRightDown(){
	Mat rightDownX = Mat::zeros(MAT_SIZE, MAT_SIZE, CV_32F);
	Mat rightDownY = Mat::zeros(MAT_SIZE, MAT_SIZE, CV_32F);
	rightDownX.at<float>(0, 0) = 5 / 4; rightDownY.at<float>(0, 0) = 5 / 4;
	rightDownX.at<float>(0, 1) = 1 / 4; rightDownY.at<float>(0, 1) = 5 / 4;
	rightDownX.at<float>(0, 2) = 3 / 4; rightDownY.at<float>(0, 2) = 5 / 4;
	rightDownX.at<float>(0, 3) = 7 / 4; rightDownY.at<float>(0, 3) = 5 / 4;
	rightDownX.at<float>(1, 0) = 5 / 4; rightDownY.at<float>(1, 0) = 1 / 4;
	rightDownX.at<float>(1, 1) = 1 / 4; rightDownY.at<float>(1, 1) = 1 / 4;
	rightDownX.at<float>(1, 2) = 3 / 4; rightDownY.at<float>(1, 2) = 1 / 4;
	rightDownX.at<float>(1, 3) = 7 / 4; rightDownY.at<float>(1, 3) = 1 / 4;
	rightDownX.at<float>(2, 0) = 5 / 4; rightDownY.at<float>(2, 0) = 3 / 4;
	rightDownX.at<float>(2, 1) = 1 / 4; rightDownY.at<float>(2, 1) = 3 / 4;
	rightDownX.at<float>(2, 2) = 3 / 4; rightDownY.at<float>(2, 2) = 3 / 4;
	rightDownX.at<float>(2, 3) = 7 / 4; rightDownY.at<float>(2, 3) = 3 / 4;
	rightDownX.at<float>(3, 0) = 5 / 4; rightDownY.at<float>(3, 0) = 7 / 4;
	rightDownX.at<float>(3, 1) = 1 / 4; rightDownY.at<float>(3, 1) = 7 / 4;
	rightDownX.at<float>(3, 2) = 3 / 4; rightDownY.at<float>(4, 2) = 7 / 4;
	rightDownX.at<float>(3, 3) = 7 / 4; rightDownY.at<float>(5, 3) = 7 / 4;
	float sumForNormal = 0;
	for (int i = 0; i < MAT_SIZE; i++){
		for (int j = 0; j < MAT_SIZE; j++){
			float uFuncAns = uFunc(rightDownX.at<float>(i, j)) * uFunc(rightDownY.at<float>(i, j));
			rightDown.at<float>(i, j) = uFuncAns;
			sumForNormal += uFuncAns;
		}
	}
	for (int i = 0; i < MAT_SIZE; i++){
		for (int j = 0; j < MAT_SIZE; j++){
			rightDown.at<float>(i, j) = rightDown.at<float>(i, j) / sumForNormal;
		}
	}
}
void calcMatrices(){
	leftUp = Mat::zeros(MAT_SIZE, MAT_SIZE, CV_32S);
	leftDown = Mat::zeros(MAT_SIZE, MAT_SIZE, CV_32S);
	rightUp = Mat::zeros(MAT_SIZE, MAT_SIZE, CV_32S);
	rightDown = Mat::zeros(MAT_SIZE, MAT_SIZE, CV_32S);
	calcLeftUp();
	calcLeftDown();
	calcRightUp();
	calcRightDown();
}
void addMirror(){
	int colsNumMirror = srcWithMirror.cols - 1;
	int colsNum = src.cols - 1;
	int rowNumMirror = srcWithMirror.rows - 1;
	int rowsNum = src.rows - 1;
	for (int i = 2; i < src.cols - 2; i++){//Up and Bottom
		srcWithMirror.at<float>(0, i) = src.at<float>(1, i);
		srcWithMirror.at<float>(1, i) = src.at<float>(0, i);
		srcWithMirror.at<float>(rowNumMirror, i) = src.at<float>(rowsNum - 1, i);
		srcWithMirror.at<float>(rowNumMirror - 1, i) = src.at<float>(rowsNum, i);
	}
	for (int i = 2; i < src.rows - 2; i++){//Right and Left
		srcWithMirror.at<float>(i, 0) = src.at<float>(i, 1);
		srcWithMirror.at<float>(i, 1) = src.at<float>(i, 0);
		srcWithMirror.at<float>(i, colsNumMirror) = src.at<float>(i, colsNum - 1);
		srcWithMirror.at<float>(i, colsNumMirror - 1) = src.at<float>(i, colsNum);
	}
	//Corners:
	srcWithMirror.at<float>(0, 0) = src.at<float>(1, 1);
	srcWithMirror.at<float>(0, 1) = src.at<float>(0, 1);
	srcWithMirror.at<float>(1, 0) = src.at<float>(1, 0);
	srcWithMirror.at<float>(1, 1) = src.at<float>(0, 0);

	srcWithMirror.at<float>(rowNumMirror, colsNumMirror) = src.at<float>(rowsNum - 1, colsNum - 1);
	srcWithMirror.at<float>(rowNumMirror - 1, colsNumMirror) = src.at<float>(rowsNum - 1, colsNum);
	srcWithMirror.at<float>(rowNumMirror, colsNumMirror - 1) = src.at<float>(rowsNum, colsNum - 1);
	srcWithMirror.at<float>(rowNumMirror - 1, colsNumMirror - 1) = src.at<float>(rowsNum, colsNum);

	srcWithMirror.at<float>(0, colsNumMirror) = src.at<float>(1, colsNum - 1);
	srcWithMirror.at<float>(0, colsNumMirror - 1) = src.at<float>(0, colsNum - 1);
	srcWithMirror.at<float>(1, colsNumMirror) = src.at<float>(1, colsNum);
	srcWithMirror.at<float>(1, colsNumMirror - 1) = src.at<float>(0, colsNum);

	srcWithMirror.at<float>(rowNumMirror, 0) = src.at<float>(rowsNum - 1, 1);
	srcWithMirror.at<float>(rowNumMirror, 1) = src.at<float>(rowsNum, 1);
	srcWithMirror.at<float>(rowNumMirror - 1, 0) = src.at<float>(rowsNum - 1, 0);
	srcWithMirror.at<float>(rowNumMirror - 1, 1) = src.at<float>(rowsNum, 0);
}


int main(int argc, char** argv)
{
	int wave_frequency = 3;//Default wave frequency
	double amplitude = 0.03;//Defined after load of picture to be 3%
	if (argc != 4)
	{
		cout << "Usage: ImageToFlag <image> <wave_frequency> <interpolation_type: n,b,c>" << endl;
		waitKey(0);                              // Wait for a keystroke in the window
		return -1;
	}
	wave_frequency = atoi(argv[2]);
	char* interpolation = argv[3];
	src = imread(argv[1], IMREAD_COLOR);   // Read the file
	amplitude = amplitude * src.rows;//% of picture height.

	if ((!src.data) || src.empty())                              // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		waitKey(0);                              // Wait for a keystroke in the window
		return -2;
	}


	/// Set the dst image the same type as src but in size + amplitude for height.
	Size size(src.cols, (int)ceil(src.rows + 2 * amplitude));
	//Create destination Matrix
	Size sizeMirror(src.cols + 2, src.rows + 2);
	srcWithMirror = Mat::zeros(sizeMirror, src.type());
	dst = Mat::zeros(size, src.type());
	dst_inter = Mat::zeros(size, src.type());
	//Set Background to white.
	dst.setTo(Scalar(255, 255, 255));
	dst_inter.setTo(Scalar(255, 255, 255));
	//addMirror();

	namedWindow("Src Image", WINDOW_AUTOSIZE);   // Create a window for display.
	imshow("Src Image", src);
	namedWindow("Mirrored Image", WINDOW_AUTOSIZE);   // Create a window for display.
	imshow("Mirrored Image", srcWithMirror);
	waitKey(0);
	//Distort done here using forward scanning with no interpolation.
	for (int y = 0; y < src.rows; y++){
		for (int x = 0; x < src.cols; x++){
			int new_y = (int)(y + amplitude * (1 + sin(wave_frequency * MY_PI * x / src.cols)));
			dst.at<Vec3b>(new_y, x) = src.at<Vec3b>(y, x);
		}
	}
	cout << "done sin func\n";

	//Distort done here using backward scanning with interpolation.

	for (int dst_y = 0; dst_y < dst_inter.rows; dst_y++){
		for (int x = 0; x < dst_inter.cols; x++){
			double y = dst_y - amplitude * (1 + sin(wave_frequency * MY_PI * x / src.cols));
			int src_y;
			double src_y1, src_y2;
			switch (interpolation[0]){
			case 'n':
				src_y = ((int)round(y));
				if ((src_y >= 0) && (src_y<src.rows))
					dst_inter.at<Vec3b>(dst_y, x) = src.at<Vec3b>(src_y, x);
				break;
			case 'b'://Bi-Linear
				src_y1 = floor(y);
				src_y2 = ceil(y);
				if (in_Range(src_y1, 0, src.rows)){
					if (in_Range(src_y2, 0, src.rows)){//Both in range
						dst_inter.at<Vec3b>(dst_y, x) = src.at<Vec3b>((int)src_y1, x)*(src_y2 - y) + src.at<Vec3b>((int)src_y2, x)*(y - src_y1);
					}
					else{
						// 1 in range
						dst_inter.at<Vec3b>(dst_y, x) = src.at<Vec3b>((int)src_y1, x);
					}
				}
				else if (in_Range(src_y2, 0, src.rows)){
					// 2 in range
					dst_inter.at<Vec3b>(dst_y, x) = src.at<Vec3b>((int)src_y2, x);
				}//else None in range
				break;
			case 'c':{
				//Cubic	 ------ Need To Do
				float distFromSrcY = abs(y - src_y);
				if (distFromSrcY > 0.5){//Use topRight

				}
				else{//user bottomRight

				}
				waitKey(2);
				break;
			}
			default:
				src_y = ((int)round(y));
				if (in_Range(src_y, 0, src.rows))
					dst_inter.at<Vec3b>(dst_y, x) = src.at<Vec3b>(src_y, x);
				break;

			}


		}
	}
	cout << "\ndone backward \n";

	namedWindow("Before", WINDOW_AUTOSIZE);  // Create a window for display.
	namedWindow("No Interpolation", WINDOW_AUTOSIZE);   // Create a window for display.
	namedWindow("With Interpolation", WINDOW_AUTOSIZE);   // Create a window for display.
	imshow("Before", src);                   // Show Before Image
	imshow("No Interpolation", dst);               // Show After  Image
	imshow("With Interpolation", dst_inter);   // Create a window for display.

	waitKey(0);                              // Wait for a keystroke in the window
	return 0;
}
