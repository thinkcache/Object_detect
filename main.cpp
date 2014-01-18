/*
 * Main.cpp
 *
 *  Created on: 19-Sep-2013
 *      Author: anidroid2
 */

//Include Files Declarations
#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include "MyDefs.h"
#include "ImageProcess.h"

using namespace cv;

//Structures Declarations
struct myObject {
	int object_id;
	int obj_enable;
	CvScalar Object_color;
	CvScalar Object_color_h;
	CvScalar Object_color_l;
	double Object1_area, Object1_x, Object1_y;
};

//Function Declarations
void control_box();
void setUpWindows();
void InitFrames();
void AllObjectCentroid();
void AcquireFrames();

//Global Declarations-Variables
int i, j;
int object_trackbar;
struct myObject obj[15];

//Global Declarations-IPLImages
CvCapture *capture;
IplImage* frame_BGR, *frame_GRY, *frame_THS, *frame_HSV, *frame_THS_temp;

//Global Declaration-Moments
CvMoments* Object_moment = (CvMoments*) malloc(sizeof(CvMoments));

////////////////////////////MAIN FUNCTION//////////////////////////////
int main(int argc, char** argv) {

	//Variables Initialization
	char input = 0;

	//Window Initialization
	setUpWindows();

	//Initialize Capture Device
	capture = cvCaptureFromCAM(0);
	//0-Internal Camera
	//1-External Camera

	//EXIT CONDITION IF NO CAMERA DETECTED
	frame_BGR = cvQueryFrame(capture);
	if (frame_BGR == 0) {
		printf("No input Detected. \n Program now exiting");
		return 0;
	}

	//Initialize Frames for specific sizes and types
	InitFrames();

	//MAIN WHILE LOOP
	while (input != 27) {
		//Acquire Image
		frame_BGR = cvQueryFrame(capture);
		void AcquireFrames();

		//Process Image
		AllObjectCentroid();

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
}
/////////////////////////END OF MAIN////////////////////////////////////

//Initialization of CONTROL_BOX

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
		obj[object_trackbar].obj_enable = 1;
		uchar B, G, R;
		GetPixelValues(frame_BGR, &x, &y, &B, &G, &R);
		obj[object_trackbar].Object_color.val[0] = (double) B;
		obj[object_trackbar].Object_color.val[1] = (double) G;
		obj[object_trackbar].Object_color.val[2] = (double) R;
		printf("%lf %lf %lf \n", obj[object_trackbar].Object_color.val[0],
				obj[object_trackbar].Object_color.val[1],
				obj[object_trackbar].Object_color.val[2]);

		GetBoundaryColor(&obj[object_trackbar].Object_color,
				&obj[object_trackbar].Object_color_h,
				&obj[object_trackbar].Object_color_l);

	}
}

void setUpWindows() {
	cvNamedWindow("INPUT1");
	cvNamedWindow("OUTPUT1");
	cvNamedWindow("CONTROL_BOX");
//MOUSE FUNCTIONS DECLARATION
	cvSetMouseCallback("INPUT1", MouseMoveINPUT, 0);

	control_box();
}

void control_box() {
	cvCreateTrackbar("Picture", "CONTROL_BOX", &object_trackbar, 14, NULL);
}

void AcquireFrames() {

	cvSmooth(frame_BGR, frame_BGR, CV_BLUR, 3, 3);
	cvCvtColor(frame_BGR, frame_HSV, CV_BGR2HSV);
}

void InitFrames() {
	frame_GRY = cvCreateImage(cvGetSize(frame_BGR), IPL_DEPTH_8U, 1);
	frame_THS = cvCreateImage(cvGetSize(frame_BGR), IPL_DEPTH_8U, 1);
	frame_THS_temp = cvCreateImage(cvGetSize(frame_BGR), IPL_DEPTH_8U, 1);
	frame_HSV = cvCreateImage(cvGetSize(frame_BGR), IPL_DEPTH_8U, 3);
}

void AllObjectCentroid() {
	for (i = 0; i < 15; i++) {

		if (obj[i].obj_enable == 1) {
			printf("%d \n", i);
			cvInRangeS(frame_BGR, obj[i].Object_color_l, obj[i].Object_color_h,
					frame_THS_temp);
			//cvDilate(frame_THS_temp, frame_THS, NULL, 4);
			cvMoments(frame_THS, Object_moment, 1);
			obj[i].Object1_area = cvGetCentralMoment(Object_moment, 0, 0);
			obj[i].Object1_x = (cvGetSpatialMoment(Object_moment, 1, 0))
					/ obj[i].Object1_area;
			obj[i].Object1_y = (cvGetSpatialMoment(Object_moment, 0, 1))
					/ obj[i].Object1_area;
			if (i == object_trackbar) {
				cvShowImage("CONTROL_BOX", frame_THS_temp);
			}
		}

	}
}
