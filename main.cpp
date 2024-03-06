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

void countWords(int block) {
    COUNT_LOVE += block;
    cout << "oioi" << endl;
    return;
}

int main(){
    int block[20];

    for (int i = 0; i < 20; i++) block[i] = i;

    vector<thread> threads;

    auto begin = high_resolution_clock::now();
    for (int i = 0; i < 20; i++) {
        threads.push_back(thread(countWords, block[i]));
    }

    cout << "about to join" << endl;
    for (auto& th : threads) th.join();

    auto end = high_resolution_clock::now();
    cout << duration_cast<microseconds>(end - begin).count() << endl;

    cout << COUNT_LOVE << endl;
    cout << "end" << endl;

    return 0;
}