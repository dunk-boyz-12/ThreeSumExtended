//
//  main.cpp
//  Lab0x04_TripletSum
//
//  Created by Nicholas Buras.
//

#include <iostream>
//files
#include "utils.hpp"


int main(int argc, const char * argv[]) {
    
    //setup
    int* list;
    int* tripList;
    srand(time(0));
    
    /* ############################ Brute Force Test ############################ */
    //print table header
    /*std::cout.width(30);
    std::cout << "Brute Force Test" << std::endl;
    std::cout.width(9);
    std::cout << "N  |";
    std::cout.width(15);
    std::cout << "  Runtime  |";
    std::cout.width(10);
    std::cout << "  Expected Doubling Ratio  |";
    std::cout << std::endl;

    for (int currN = MIN_N; currN < MAX_N3; currN *= 2) {
        //setup
        list = new int[currN];
        tripList = new int[floor((currN/6))*3]; //1 triplet per 6 elements, N >= 6 to work, set to start at 10
        
        //call time algo which runs trial loops to find time for that N & prints the table row
        timeAlgo(bruteForceTripletSum, list, currN, 0, tripList);
        
        //clean up
        delete[] list;
        delete[] tripList;
    }
    
    //table break
    std::cout << std::endl << std::endl << std::endl << std::endl;
    
    /* ############################ Faster - n2*log(N) - Test ############################ */
    //print table header
    /*std::cout.width(30);
    std::cout << "Faster - n2*logn - Test" << std::endl;
    std::cout.width(9);
    std::cout << "N  |";
    std::cout.width(15);
    std::cout << "  Runtime  |";
    std::cout.width(10);
    std::cout << "  Expected Doubling Ratio  |";
    std::cout << std::endl;

    for (int currN = MIN_N; currN < MAX_N; currN *= 2) {
        //setup
        list = new int[currN];
        tripList = new int[floor((currN/6))*3]; //1 triplet per 6 elements, N >= 6 to work, set to start at 10

        //call time algo which runs trial loops to find time for that N & prints the table row
        timeAlgo(fasterTripletSum, list, currN, 1, tripList);
        
        //clean up
        delete[] list;
        delete[] tripList;
    }
    
    //table break
    std::cout << std::endl << std::endl << std::endl << std::endl;
    
    /* ############################ Fastest - n2 - Test ############################ */
    //print table header
    std::cout.width(30);
    std::cout << "Fastest - n2 - Test" << std::endl;
    std::cout.width(9);
    std::cout << "N  |";
    std::cout.width(15);
    std::cout << "  Runtime  |";
    std::cout.width(10);
    std::cout << "  Expected Doubling Ratio  |";
    std::cout << std::endl;

    for (int currN = MIN_N; currN < MAX_N; currN *= 2) {
        //setup
        list = new int[currN];
        tripList = new int[floor((currN/6))*3]; //1 triplet per 6 elements, N >= 6 to work, set to start at 10

        //call time algo which runs trial loops to find time for that N & prints the table row
        timeAlgo(evenFasterTripletSum, list, currN, 2, tripList);
        
        //clean up
        delete[] list;
        delete[] tripList;
    }
    

}
