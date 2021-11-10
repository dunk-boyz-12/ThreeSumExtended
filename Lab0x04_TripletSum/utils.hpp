//
//  utils.hpp
//  Lab0x04_TripletSum
//
//  Created by Nicholas Buras.
//

#ifndef utils_hpp
#define utils_hpp

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <iomanip>

#define MIN_N 20
#define MAX_N 1000000
#define MAX_N3 100000
#define MAX_VAL 100
#define MAX_TRIALS 1
#define MIN_TRIALS 0



void generateTestInput(int*,int,int*,int);
void timeAlgo(void(*)(int*,int),int*,int,int,int*);
double getExpectedDoublingRatio(int,int);
//algos
void bruteForceTripletSum(int*,int);
void fasterTripletSum(int*,int);
void evenFasterTripletSum(int*,int);
//helpers
int binarySearch(int*,int,int,int);
void mergeSort(int*,int*,int,int);
void merge(int*,int*,int,int,int);

#endif /* utils_hpp */
