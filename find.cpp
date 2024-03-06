#include<iostream>
#include<string>
#include<cstring>

using namespace std;

int countWords(char *text);
int countWords(char *text, char *word);

int countWords(char *text){
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