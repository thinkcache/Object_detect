/*
 * ImageProcess.cpp
 *
 *  Created on: 22-Sep-2013
 *      Author: anidroid2
 */

#include <cv.h>
#include <highgui.h>
#include "MyDefs.h"

struct myObject {
	int object_id;
	CvScalar Object_color;
	CvScalar Object_color_h;
	CvScalar Object_color_l;

	double Object1_area, Object1_x, Object1_y;
};

void GetPixelValues(IplImage* image, int* x, int* y, uchar* B, uchar* G,
		uchar* R) {
	int xx = *x, yy = *y;
	uchar* ptr = (uchar*) ((image->imageData) + (yy * (image->widthStep)));
	*B = ptr[(3 * xx) + 0];
	*G = ptr[(3 * xx) + 1];
	*R = ptr[(3 * xx) + 2];
}

CvScalar GetPixelScalar(IplImage* image, int* x, int* y) {
	int xx = *x, yy = *y;
	uchar* ptr = (uchar*) ((image->imageData) + (yy * (image->widthStep)));
	CvScalar s;
	s.val[0] = ptr[(3 * xx) + 0];
	s.val[1] = ptr[(3 * xx) + 1];
	s.val[2] = ptr[(3 * xx) + 2];
	return s;
}

CvScalar GetPixelScalarThres(IplImage* image, int* x, int* y, char param = 0) {
	int xx = *x, yy = *y;
	uchar* ptr = (uchar*) ((image->imageData) + (yy * (image->widthStep)));
	CvScalar s;
	s.val[0] = ptr[(3 * xx) + 0];
	s.val[1] = ptr[(3 * xx) + 1];
	s.val[2] = ptr[(3 * xx) + 2];
	if (param == UPPER) {
		if (s.val[0] < 250)			//Hue
			s.val[0] = s.val[0] + H_diff;
		if (s.val[1] < 245)			//Sat
			s.val[1] = s.val[1] + S_diff;
		if (s.val[2] < 245)			//Val
			s.val[2] = s.val[2] + V_diff;

	} else if (param == LOWER) {
		if (s.val[0] > 5)			//Hue
			s.val[0] = s.val[0] - H_diff;
		if (s.val[1] < 10)			//Sat
			s.val[1] = s.val[1] - S_diff;
		if (s.val[2] < 10)			//Val
			s.val[2] = s.val[2] - V_diff;

	} else {
	}

	return s;
}

void GetBoundaryColor(CvScalar* input, CvScalar* high, CvScalar* low) {

	//FOR HIGH SCALAR
	if (input->val[0] < (255 - H_diff))			//Hue
		high->val[0] = input->val[0] + H_diff;
	else
		high->val[0] = 255;
	if (input->val[1] < (255 - S_diff))			//Sat
		high->val[1] = input->val[1] + S_diff;
	else
		high->val[1] = 255;
	if (input->val[2] < (255 - V_diff))			//Val
		high->val[2] = input->val[2] + V_diff;
	else
		high->val[2] = 255;

	//FOR LOW SCALAR
	if (input->val[0] > (H_diff))			//Hue
		low->val[0] = input->val[0] - H_diff;
	else
		low->val[0] = 0;
	if (input->val[1] > (S_diff))			//Sat
		low->val[1] = input->val[1] - S_diff;
	else
		low->val[1] = 0;
	if (input->val[2] > (V_diff))			//Val
		low->val[2] = input->val[2] - V_diff;
	else
		low->val[2] = 0;

}
