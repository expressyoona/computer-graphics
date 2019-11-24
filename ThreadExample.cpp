/*
 *  Linux: -pthread
 */

#include <thread>
#include <iostream>
#include <unistd.h>

const int N = 10;
const int TIME_REFRESH_MS = 1000;
clock_t currentTime = clock();

void sleep(int ms) {
    clock_t endTime = clock() + TIME_REFRESH_MS*CLOCKS_PER_SEC/1000;
    if (endTime <= currentTime) {
        std::cout<<"Time out!"<<std::endl;
    }    
}

void count() {

}

void evenLoop() {
    for(int i = 0;i < N;i+=2) {
        std::cout<<i<<" ";
        sleep(1000);
    }
    std::cout<<std::endl;
}

void oddLoop() {
    for(int i = 1;i < N;i+=2) {
        std::cout<<i<<" ";
        sleep(1000);
    }
    std::cout<<std::endl;
}

int main() {
    std::thread first(count);
    std::thread second(oddLoop);

    first.join();
    second.join();
}