/*
 * ImageProcess.h
 *
 *  Created on: 22-Sep-2013
 *      Author: anidroid2
 */

#ifndef IMAGEPROCESS_H_
#define IMAGEPROCESS_H_


void GetPixelValues(IplImage*, int*, int*, int*, int*, int*);
void MouseMoveINPUT(int event, int x, int y, int, void*);
CvScalar GetPixelScalar(IplImage*, int*, int*);
CvScalar GetPixelScalarThres(IplImage*, int*, int*, char);




#endif /* IMAGEPROCESS_H_ */
