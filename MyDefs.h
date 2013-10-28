/*
 * MyDefs.h
 *
 *  Created on: 22-Sep-2013
 *      Author: anidroid2
 */


//Define Macros
#define UPPER 1
#define LOWER 2


#define H_diff 10
#define S_diff 20
#define V_diff 20

// Record the execution time of some code, in milliseconds.
//Courtesy:Shervin Emami and aishack.in
#define DECLARE_TIMING(s)  int64 timeStart_##s; double timeDiff_##s; double timeTally_##s = 0; int countTally_##s = 0
#define START_TIMING(s)    timeStart_##s = cvGetTickCount()
#define STOP_TIMING(s) 	   timeDiff_##s = (double)(cvGetTickCount() - timeStart_##s); timeTally_##s += timeDiff_##s; countTally_##s++
#define GET_TIMING(s) 	   (double)(timeDiff_##s / (cvGetTickFrequency()*1000.0))
#define GET_AVERAGE_TIMING(s)   (double)(countTally_##s ? timeTally_##s/ ((double)countTally_##s * cvGetTickFrequency()*1000.0) : 0)
#define CLEAR_AVERAGE_TIMING(s) timeTally_##s = 0; countTally_##s = 0
