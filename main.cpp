#include <iostream>
#include <thread>
#include <vector>
#include <windows.h>
#include <chrono>
#include <fstream>
#include "read.cpp"

using std::cout;
using std::endl;
using std::thread;
using std::string;
using std::vector;
using namespace std::chrono;

int COUNT_LOVE = 0;
int COUNT_HATE = 0;
int arraCOUNT_LOVE[100];
int arraCOUNT_HATE[100];

void countWordsCaller(char *text, int iInitial, int iFinal, int threadNumber);
int countWords(char *text, char *word, int iInitial, int iFinal);
void testThreads(int k, std::chrono::duration<double>* temp);

int main(){

    FILE* arqWord;
    FILE* arqBlock;
    arqWord = fopen("data//times.txt", "wt");
    arqBlock = fopen("data//block.txt", "wt");
    int repeats = 20;

    for (int i=1; i<21; i++){
        double tempWord = 0;
        double tempBlock = 0;
        cout << "\nTestando com " << i << " threads" << endl;
        for (int r = 0; r<repeats; r++)
        {
            cout << "Repeticao " << r << endl;
            std::chrono::duration<double> t[2];
            testThreads(i, t);
            // Tempo de contagem das palavras
            tempWord += t[0].count();
            // Tempo de preparação do texto
            tempBlock += t[1].count();
            COUNT_LOVE = 0;
            COUNT_HATE = 0;
            for (int j=0; j<i; j++){
                arraCOUNT_LOVE[j] = 0;
                arraCOUNT_HATE[j] = 0;
            }
        }
        fprintf(arqWord, "%s", "\n");
        fprintf(arqWord, "%f", tempWord/repeats);
        fprintf(arqBlock, "%s", "\n");
        fprintf(arqBlock, "%f", tempBlock/repeats);
    }
    fclose(arqWord);
    fclose(arqBlock);
}

void countWordsCaller(char *text, int iInitial, int iFinal, int threadNumber){
    char w1[] = "love";
    char w2[] = "Love";
    char w3[] = "hate";
    char w4[] = "Hate";
    int rLove = countWords(text, w1, iInitial, iFinal);
    rLove += countWords(text, w2, iInitial, iFinal);
    int rHate = countWords(text, w3, iInitial, iFinal);
    rHate += countWords(text, w4, iInitial, iFinal);
    arraCOUNT_LOVE[threadNumber] += rLove;
    arraCOUNT_HATE[threadNumber] += rHate;
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

void testThreads(int k, std::chrono::duration<double>* temp)
{
    int iNumBlocks = k;

    auto beginBlock = high_resolution_clock::now();
    Text* text = new Text("data/multiplied.txt", 1);
    int* iBlockSize = text -> blocktext(iNumBlocks);
    auto endBlock = high_resolution_clock::now();
    
    cout << "Tempo de Preparacao: " << duration_cast<microseconds>(endBlock - beginBlock).count() << " microssegundos" << endl;
    
    vector<thread> threads;

    int iInitial = 0;
    int iFinal = 0;
    auto beginCount = high_resolution_clock::now();

    for (int i = 0; i < iNumBlocks; i++) {
        iFinal = iBlockSize[i];
        threads.push_back(std::thread(countWordsCaller, text -> cText, iInitial, iFinal, i));
        iInitial = iFinal;
    }

    for (auto& th : threads) th.join();

    for (int i = 0; i < iNumBlocks; i++) {
        COUNT_LOVE += arraCOUNT_LOVE[i];
        COUNT_HATE += arraCOUNT_HATE[i];
    }

    auto endCount = high_resolution_clock::now();

    cout << "Tempo de Contagem: " << duration_cast<microseconds>(endCount - beginCount).count() << " microssegundos" << endl;

    cout << "Tempo Total: " << duration_cast<microseconds>(endCount - beginCount + endBlock - beginBlock).count() << " microssegundos" << endl;

    cout << "\t Thread " << 0 << " n char: " << iBlockSize[0] << endl;
    for (int i = 1; i < iNumBlocks; i++) {
        cout << "\t Thread " << i << ", n char: " << iBlockSize[i] -  iBlockSize[i - 1] << endl;
    }

    cout << "Love: " << COUNT_LOVE << endl;
    cout << "Hate: " << COUNT_HATE << endl;
    if (COUNT_LOVE > COUNT_HATE)
    {
        cout << "Love wins!" << endl;
    }
    else
    {
        cout << "Hate wins!" << endl;
    }
    // Tempo de contagem das palavras
    temp[0] = duration_cast<microseconds>(endCount - beginCount);
    // Tempo de preparação do texto
    temp[1] = duration_cast<microseconds>(endBlock - beginBlock);
    return;
}
