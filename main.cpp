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
int x_pos = 0, y_pos = 0, enable = 0;
int object_trackbar;

CvScalar Object1_color;
CvScalar Object1_color_h;
CvScalar Object1_color_l;
double Object1_area, Object1_x, Object1_y;

//Image Declarations
IplImage* frame_BGR, *frame_GRY, *frame_THS, *frame_HSV, *frame_THS_temp;

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
	CvCapture *capture = cvCaptureFromCAM(0);
	//0-Internal Camera
	//1-External Camera

	//EXIT CONDITION IF NO CAMERA DETECTED
	frame_BGR = cvQueryFrame(capture);
	if (frame_BGR == 0) {
		printf("No input Detected. \n Program now exiting");
		return 0;
	}

	frame_GRY = cvCreateImage(cvGetSize(frame_BGR), IPL_DEPTH_8U, 1);
	frame_THS = cvCreateImage(cvGetSize(frame_BGR), IPL_DEPTH_8U, 1);
	frame_THS_temp = cvCreateImage(cvGetSize(frame_BGR), IPL_DEPTH_8U, 1);
	frame_HSV = cvCreateImage(cvGetSize(frame_BGR), IPL_DEPTH_8U, 3);

	//Object Images
	IplImage *Object1 = cvCreateImage(cvGetSize(frame_HSV), IPL_DEPTH_8U, 1);
	IplImage *Object2 = cvCreateImage(cvGetSize(frame_HSV), IPL_DEPTH_8U, 1);
	IplImage *Object3 = cvCreateImage(cvGetSize(frame_HSV), IPL_DEPTH_8U, 1);

	//MOUSE FUNCTIONS DECLARATION
	cvSetMouseCallback("INPUT1", MouseMoveINPUT, 0);

	CvMoments* Object1_moment = (CvMoments*) malloc(sizeof(CvMoments));

	//MAIN WHILE LOOP
	while (input != 27) {
		//Acquire Image
		frame_BGR = cvQueryFrame(capture);
		cvSmooth(frame_BGR, frame_BGR, CV_BLUR, 3, 3);
		cvCvtColor(frame_BGR, frame_HSV, CV_BGR2HSV);
		//cvShowImage("OUTPUT1", frame_HSV);

		//Process Image
		if (enable == 1) {

			cvInRangeS(frame_BGR, Object1_color_l, Object1_color_h,
					frame_THS_temp);
			cvDilate(frame_THS_temp, frame_THS, NULL, 4);
			cvShowImage("OUTPUT1", frame_THS);
			cvMoments(frame_THS, Object1_moment, 1);
			Object1_area = cvGetCentralMoment(Object1_moment, 0, 0);
			Object1_x = (cvGetSpatialMoment(Object1_moment, 1, 0))
					/ Object1_area;
			Object1_y = (cvGetSpatialMoment(Object1_moment, 0, 1))
					/ Object1_area;
			cvCircle(frame_BGR, cvPoint(Object1_x, Object1_y), 5,
					CV_RGB(0xff,0xff,0xff));
			printf("%lf %lf \n", Object1_x, Object1_y);
		}

		//Display Functions
		cvShowImage("INPUT1", frame_BGR);

		//Check if ESC Key is pressed
		input = cvWaitKey(1);
	} //SUPER WHILE LOOP END

	//Cleaning Up
	printf("EXITING.....");
	cvDestroyAllWindows();
	cvReleaseImage(&frame_BGR);
	cvReleaseImage(&frame_GRY);
	cvReleaseCapture(&capture);
} //END OF CODE

//Initialization of CONTROL_BOX
void control_box() {
	cvCreateTrackbar("Picture", "CONTROL_BOX", &object_trackbar, 15, NULL);
}

//Call-back Function for INPUT1 window
//When MouseEvent occurs over INPUT1,
//this function is called with an event and positions of x and y.
void MouseMoveINPUT(int event, int x, int y, int, void*) {
	if (event == CV_EVENT_MOUSEMOVE) {
		//uchar B, G, R;
		//GetPixelValues(frame_BGR, &x, &y, &B, &G, &R);
		//printf("x=%d y=%d  B=%d G=%d R=%d\n", x, y, B, G, R);
	}
	if (event == CV_EVENT_RBUTTONDOWN) {
		enable = 1;
		//Object1_color = GetPixelScalar(frame_BGR, &x, &y);
		uchar B, G, R;
		GetPixelValues(frame_BGR, &x, &y, &B, &G, &R);
		Object1_color.val[0] = (double) B;
		Object1_color.val[1] = (double) G;
		Object1_color.val[2] = (double) R;

		GetBoundaryColor(&Object1_color, &Object1_color_h, &Object1_color_l);
		//printf("%lf %lf %lf \n", Object1_color.val[0], Object1_color.val[1],	Object1_color.val[2]);
	}
}

