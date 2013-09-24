/*
 * ImageProcess.cpp
 *
 *  Created on: 22-Sep-2013
 *      Author: anidroid2
 */

#include <cv.h>
#include <highgui.h>
#include "MyDefs.h"

void GetPixelValues(IplImage* image, int* x, int* y, int* B, int* G, int* R) {
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

