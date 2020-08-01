//
//  main.cpp
//  PerfTracker
//
//  Created by Vinay Gupta on 01/08/20.
//  Copyright © 2020 Vinay Gupta. All rights reserved.
//

#include <iostream>
#include "SimpleTimer.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

void recursePrint(string out, int open, int end, int n){
    if((open+end)>=n){
        if(open==end)
            printf("%s \n", out.c_str());
        return;
    }
    if(open>end)
        recursePrint(out+"}", open, end+1 , n);
    
    recursePrint(out+"{", open+1, end, n);

}

int mainBrackets(){
    int n=4;
    
    string out = "{";
    int open = 1;
    int end = 0;
    
    recursePrint(out, open, end, n);
    return 0;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    SimpleTimer *timer1 = new SimpleTimer();
    timer1->startTimer();
    mainBrackets();
    timer1->stopTimer();
    
    // Using time point and system_clock
    time_point<system_clock> start, end;

    start = system_clock::now();
    mainBrackets();
    end = system_clock::now();
    
    duration<double> duration = end - start;
    
    cout<<"Timer using frequency: "<<timer1->getElapsedTime(SimpleTimer::unit::MICRO) <<" microseconds"<<endl;
    cout<< "Timer using chrono: "<<duration_cast<microseconds>(duration).count() <<" microseconds"<<endl;
    return 0;
}
