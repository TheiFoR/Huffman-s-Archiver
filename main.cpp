#include <iostream>
#include "FileWorker.h"
#include "HuffmansAlgorithm.h"
#include <vector>
#include <string>

#define tmr0 startTimer=clock();
#define tmr1(v) endTimer=clock();secondsTimer=(double)(endTimer-startTimer)/CLOCKS_PER_SEC;cout<<v<<" The time: "<<secondsTimer<<" seconds\n";startTimer=clock();
#define tmr2(v) endTimer=clock();secondsTimer=(double)(endTimer-startTimer)/CLOCKS_PER_SEC;cout<<v<<" The time: "<<secondsTimer<<" seconds\n";
#define tmri clock_t endTimer;clock_t startTimer;double secondsTimer;

using namespace std;

int main(int argc, char* name[])
{
    FileWorker file;
    HuffmansAlgorithm huffman;
    vector<string> fileNames;
    int mode = 0;

    if (argc == 5)
    {
        fileNames.emplace_back(name[1]);
        fileNames.emplace_back(name[2]);
        fileNames.emplace_back(name[3]);
        if (*name[4] == '0') {
            mode = 0;
        }
        else {
            mode = 1;
        }
    }
    else
    {
        fileNames = file.getNameFromConsole();
    }
    tmri;

    tmr0;
    if (!mode) {
        huffman.codingAlgorithm(fileNames[0], fileNames[1]);
        tmr1("CODING TIMER");
    }
    else {
        huffman.decodingAlgorithm(fileNames[1], fileNames[2]);
        tmr2("DECODING TIMER");
    }
}