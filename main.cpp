#include <iostream>
#include <thread>
#include <vector>
#include <windows.h>
#include <chrono>
#include "read.cpp"

using std::cout;
using std::endl;
using std::thread;
using std::string;
using std::vector;
using namespace std::chrono;

int COUNT_LOVE = 0;
int COUNT_HATE = 0;

void countWordsCaller(char *text, int iInitial, int iFinal);
int countWords(char *text, char *word, int iInitial, int iFinal);

int main(){
    int iNumBlocks = 20;
    Text* text = new Text("data/multiplied.txt", 1);
    int* iBlockSize = text -> blocktext(iNumBlocks);

    vector<thread> threads;

    int iInitial = 0;
    int iFinal = 0;
    auto begin = high_resolution_clock::now();
    for (int i = 0; i < iNumBlocks; i++) {
        iFinal = iBlockSize[i];
        threads.push_back(std::thread(countWordsCaller, text -> cText, iInitial, iFinal));
        iInitial = iFinal;
    }

    cout << "about to join" << endl;
    for (auto& th : threads) th.join();

    auto end = high_resolution_clock::now();
    cout << duration_cast<microseconds>(end - begin).count() << endl;

    cout << "Love: " << COUNT_LOVE << endl;
    cout << "Hate: " << COUNT_HATE << endl;
    cout << "end" << endl;

    return 0;
}

void countWordsCaller(char *text, int iInitial, int iFinal){
    char w1[] = "love";
    char w2[] = "Love";
    char w3[] = "hate";
    char w4[] = "Hate";
    int rLove = countWords(text, w1, iInitial, iFinal);
    rLove += countWords(text, w2, iInitial, iFinal);
    int rHate = countWords(text, w3, iInitial, iFinal);
    rHate += countWords(text, w4, iInitial, iFinal);
    COUNT_LOVE += rLove;
    COUNT_HATE += rHate;
}

int countWords(char *text, char *word, int iInitial, int iFinal){
    int tSize = iFinal - iInitial;
    int wSize = 0;

    while( word[wSize] != '\0')
    {
        wSize++;
    }

    int tCounter = 0;
    int wTimes = 0;
    while(tCounter+wSize<tSize+1)
    {
        bool founder = true;
        int wCounter = 0;
        while(wCounter<wSize)
        {
            if(text[tCounter+wCounter + iInitial]!=word[wCounter]){
                founder = false;
            }
            wCounter++;
        }

        if(founder == true){
            wTimes++;
        }
        tCounter++;
    }

    return wTimes;
}
