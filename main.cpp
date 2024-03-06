#include <iostream>
#include <thread>
#include <vector>
#include <windows.h>
#include <chrono>

using std::cout;
using std::endl;
using std::thread;
using std::string;
using std::vector;
using namespace std::chrono;

int COUNT_LOVE = 0;
int COUNT_HATE = 0;

void countWords(char *text);
int countWords(char *text, char *word);

int main(){
    int block[20];
    char bloco[] = "Arroz love, I hate yooooou. Love";

    for (int i = 0; i < 20; i++) block[i] = i;

    vector<thread> threads;

    auto begin = high_resolution_clock::now();
    for (int i = 0; i < 20; i++) {
        threads.push_back(thread(countWords, bloco));
    }

    cout << "about to join" << endl;
    for (auto& th : threads) th.join();

    auto end = high_resolution_clock::now();
    cout << duration_cast<microseconds>(end - begin).count() << endl;

    cout << COUNT_LOVE << endl;
    cout << "end" << endl;

    return 0;
}

void countWords(char *text){
    char w1[] = "love";
    char w2[] = "Love";
    char w3[] = "hate";
    char w4[] = "Hate";
    int rLove = countWords(text, w1);
    rLove += countWords(text, w2);
    int rHate = countWords(text, w3);
    rHate += countWords(text, w4);
    COUNT_LOVE += rLove;
    COUNT_HATE += rHate;
}

int countWords(char *text, char *word){
    int tSize = 0;
    int wSize = 0;
    while( text[tSize] != '\0')
    {
        tSize++;
    }
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
            if(text[tCounter+wCounter]!=word[wCounter]){
                founder = false;
            }
            wCounter++;
        }

        if(founder == true){
            wTimes++;
        }
        tCounter++;
    }
    cout << wTimes << endl;

    return wTimes;
}