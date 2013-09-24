/*
 * Main.cpp
 *
 *  Created on: 19-Sep-2013
 *      Author: anidroid2
 */

//Include Files Declarations
#include <cv.h>
#include <highgui.h>
#include "MyDefs.h"
#include "ImageProcess.h"

using namespace cv;

//Function Declarations
void control_box();

//Global Declarations
IplImage *frame_BGR;
int x_pos = 0, y_pos = 0;

//MAIN FUNCTION
int main(int argc, char** argv) {

	//Variables Initialization
	char input = 0;

	//Window Initialization
	cvNamedWindow("INPUT1");
	cvNamedWindow("OUTPUT1");
	cvNamedWindow("CONTROL_BOX");
	control_box();

	//Image Pointers declarations
	CvCapture *capture = cvCaptureFromCAM(1);
	frame_BGR = cvQueryFrame(capture);
	IplImage *frame_GRY = cvCreateImage(cvGetSize(frame_BGR), IPL_DEPTH_8U, 1);
	IplImage *frame_THRES = cvCreateImage(cvGetSize(frame_BGR), IPL_DEPTH_8U,
			1);
	IplImage *frame_HSV = cvCreateImage(cvGetSize(frame_BGR), IPL_DEPTH_8U, 3);

	//EXIT CONDITION IF NO CAMERA DETECTED
	if (frame_BGR == 0) {
		printf("No input Detected. \n Program now exiting");
		return 0;
	}

	//MOUSE FUNCTIONS DECLARATION
	cvSetMouseCallback("INPUT1", MouseMoveINPUT, 0);

	//MAIN WHILE LOOP
	while (input != 27) {
		//Acquire Image
		IplImage *frame_BGR = cvQueryFrame(capture);
		cvSmooth(frame_BGR,frame_BGR,CV_BLUR,3,3);
		cvCvtColor(frame_BGR, frame_HSV, CV_BGR2HSV);
		//cvShowImage("OUTPUT1", frame_HSV);
		//Process Image
		if (x_pos != 0 && y_pos != 0) {

			cvInRangeS(frame_HSV,
					GetPixelScalarThres(frame_HSV, &x_pos, &y_pos, LOWER),
					GetPixelScalarThres(frame_HSV, &x_pos, &y_pos, UPPER),
					frame_THRES);
			cvShowImage("OUTPUT1", frame_THRES);
		}

		//Display Functions
		cvShowImage("INPUT1", frame_BGR);

		//Check if ESC Key is pressed
		input = cvWaitKey(1);
	} //MAIN WHILE LOOP END

	//Cleaning Up
	printf("EXITING.....");
	//cvDestroyAllWindows();
	cvReleaseImage(&frame_BGR);
	cvReleaseImage(&frame_GRY);
	cvReleaseCapture(&capture);
} //END OF CODE

//Initialization of CONTROL_BOX
void control_box() {
}

//Call-back Function for INPUT window
void MouseMoveINPUT(int event, int x, int y, int, void*) {
	if (event == CV_EVENT_MOUSEMOVE) {
		int B, G, R;
		GetPixelValues(frame_BGR, &x, &y, &B, &G, &R);
		//printf("x=%d y=%d  B=%d G=%d R=%d\n", x, y, B, G, R);
	}
	if (event == CV_EVENT_RBUTTONDOWN) {
		x_pos = x;
		y_pos = y;
		printf("x_pos=%d y_pos=%d\n", x, y);

	}
}

