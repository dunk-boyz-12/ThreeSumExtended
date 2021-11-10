//
//  utils.cpp
//  Lab0x04_TripletSum
//
//  Created by Nicholas Buras.
//

#include "utils.hpp"

void generateTestInput(int* list, int listSize, int* tList, int nForcedTriplets){
    //srand(time(0));
    //fill list
    for (int i = 0; i < listSize; i++) {
        if(i%3==0 || i%5==0) {
            list[i] = -(rand() % MAX_VAL );
        }
        else {
            list[i] = rand() % MAX_VAL;
        }
    }
    //force triplets
    int n1;
    int n2;
    int target;
    int index = 0;
    int tIndex = 0;
    for (int i = 0; i < nForcedTriplets; i++) {
        n1 = list[index];
        n2 = list[index+2];
        target = n1+n2;
        list[index+4] = -(target);
        //store indexes
        tList[tIndex] = index;
        tList[tIndex+1] = index + 2;
        tList[tIndex+2] = index + 4;
        //inc tList index
        tIndex += 3;
        //inc list index
        index += 6;
    }
    /*for (int i = 0; i < listSize; i++) {
        std::cout << list[i] << std::endl;
    }
    std::cout << "Indexes" << std::endl;
    for (int i = 0; i < nForcedTriplets*3; i++) {
        std::cout << tList[i] << std::endl;
    }*/
    
}

double getExpectedDoublingRatio(int runtimeType, int N) {
    double expectedDoublingRatio, n1, n2;
    switch (runtimeType) {
        case 0:
            //(n3) cubic
            expectedDoublingRatio = pow((2*N), 3) / pow(N, 3);
            break;
        case 1:
            //n2*log(n)
            expectedDoublingRatio = pow((2*N), 2) * log((2*N)) /  (pow(N, 2) * log(N));
            break;
        case 2:
            //quadratic (n2)
            expectedDoublingRatio = pow((2*N), 2) / pow(N, 2);
            break;
        default:
            expectedDoublingRatio = -1;
            break;
    }
    return expectedDoublingRatio;
}

void timeAlgo(void (*algoToTest)(int*,int), int* list, int N, int algoExpRuntime, int* tripList) {
    //timer vars
    clock_t sTime, eTime, currTrialTime, overhead;
    double expRT;
    //clock start
    sTime = clock();
    //trial loop
    for (int trial = MIN_TRIALS; trial < MAX_TRIALS; trial++) {
        generateTestInput(list, N, tripList, floor(N/6));
        algoToTest(list,N);
    }
    //clock end
    eTime = clock();
    currTrialTime = (eTime - sTime) / MAX_TRIALS;

    //clock start
    sTime = clock();
    //trial loop
    for (int trial = MIN_TRIALS; trial < MAX_TRIALS; trial++) {
        //calculate overhead of the for loop
        generateTestInput(list, N, tripList, floor(N/6));
    }
    //clock end
    eTime = clock();
    overhead = (eTime - sTime) / MAX_TRIALS;
    //find time for size N
    currTrialTime -= overhead;
    //convert to seconds && get expected doubling ratio
    double t = static_cast<double>(currTrialTime)/CLOCKS_PER_SEC;
    expRT = getExpectedDoublingRatio(algoExpRuntime, N);
    //print table row
    std::cout.width(6);
    std::cout << N << "  |  ";
    std::cout.precision(4);
    std::cout.width(10);
    std::cout << t << "  |  ";
    std::cout.width(23);
    std::cout.precision(4);
    std::cout << expRT << "  |  ";
    
    std::cout << std::endl;
    
}

/* ############################ Algos ############################ */

void bruteForceTripletSum(int* list, int N) {
    int tripletCount = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            for (int k = j + 1; k < N; k++) {
                if((list[i] + list[j] + list[k]) == 0) {
                    tripletCount++;
                    //printf("Triplet (%d, %d, %d) Indexes (%d %d %d)\n", list[i], list[j], list[k], i, j, k);
                }
            }
        }
    }
    //std::cout << "T Count = " << tripletCount << std::endl;
}

void fasterTripletSum(int* list, int N)  {
    
    int* tempList = new int[N];
    mergeSort(list, tempList, 0, N-1);
        /*for (int i = 0; i < N; i++) {
            std::cout << list[i] << std::endl;
        }*/
    delete[] tempList;
    
    int tripletCount = 0;
    int target;
    int targetIndex;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            target = -(list[i] + list[j]);
            targetIndex = binarySearch(list, 0, N-1, target);
            if (targetIndex > -1) {
                tripletCount++;
                //printf("Triplet (%d, %d, %d) Indexes (%d %d %d)\n", list[i], list[j], list[targetIndex], i, j, targetIndex);
            }
        }
    }
    //std::cout << "T Count = " << tripletCount << std::endl;
}

int binarySearch(int* list, int l, int r, int target) {
    int m = floor((l+r)/2);
    if(list[m] == target) {
        return m;
    } else if(l == r){
        return -1;
    } else if(target < list[m]) {
        return binarySearch(list, 0, m-1, target);
    } else { //target > list[m]
        return binarySearch(list, m+1, r, target);
    }
}

void mergeSort(int* inList, int* tempList, int left, int right) {
    if(left >= right){
        return;
    }
    int middle = floor((right+left)/2);
    mergeSort(inList, tempList,left, middle);
    mergeSort(inList, tempList,middle+1, right);
    merge(inList,tempList,left,middle,right);
}
void merge(int* inList,int* tempList, int left, int middle, int right) {
    int leftIndex = left;
    int rightIndex = middle+1;

    //copy into temp list
    for (int ctr = left; ctr <= right; ctr++) {
        tempList[ctr] = inList[ctr];
    }
    
    //merge back to actual list
    for (int ctr = left; ctr <= right; ctr++) {
        //no more in left side list
        if(leftIndex > middle){
            inList[ctr] = tempList[rightIndex];
            rightIndex++;
        } else if(rightIndex > right) {
            //no more in right side list
            inList[ctr] = tempList[leftIndex];
            leftIndex++;
        } else if(tempList[leftIndex] <= tempList[rightIndex]) {
            inList[ctr] = tempList[leftIndex];
            leftIndex++;
        } else {
            inList[ctr] = tempList[rightIndex];
            rightIndex++;
        }
    }
}

void evenFasterTripletSum(int* list, int N) {
    //avoids duplicates
    
    int* tempList = new int[N];
    mergeSort(list, tempList, 0, N-1);
        /*for (int i = 0; i < N; i++) {
            std::cout << list[i] << std::endl;
        }*/
    delete[] tempList;
    
    int tripletCount = 0;
    int n2_Index, n3_Index;
    for (int n1_Index = 0; n1_Index < N - 2; n1_Index++) {
        //setup nums to check
        n2_Index = n1_Index+1;
        n3_Index = N-1;
        while (n2_Index < n3_Index) {
            if(list[n1_Index] + list[n2_Index] + list[n3_Index] == 0){ //hooray, triplet
                tripletCount++;
                //printf("Triplet (%d, %d, %d) Indexes (%d %d %d)\n", list[n1_Index], list[n2_Index], list[n3_Index], n1_Index, n2_Index, n3_Index);
                //still walk 3rd num <- to keep checking
                n3_Index--;
            } else if(list[n1_Index] + list[n2_Index] + list[n3_Index] > 0) { //walk 3rd num <-
                n3_Index--;
            } else { // n1 + n2 + n3 < 0 , walk 2nd num ->
                n2_Index++;
            }
        }
    }
    //std::cout << "T Count = " << tripletCount << std::endl;
}
