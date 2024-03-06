#include <iostream>
#include <fstream>
using namespace std;

char* read(int iRepeat) {

    // rodar arquivo python com argumento iRepeat
    string command = "python3 multiply_text.py " + to_string(iRepeat);
    system(command.c_str());

    streampos size;
    char* memblock;

    ifstream file ("data/multiplied.txt", ios::in|ios::binary|ios::ate);
    if (file.is_open())
    {
        size = file.tellg();
        memblock = new char [size];
        file.seekg (0, ios::beg);
        file.read (memblock, size);
        file.close();
    }
    else cout << "Unable to open file";
    return memblock;
}

char** blocktext(int iRepeat, int iBlocks){
    char* cText = read(iRepeat);

    int iLines = 0;
    int iChars = 0;
    while (cText[iChars] != '\0'){
        if (cText[iChars] == '\n'){
            iLines++;
        }
        iChars++;
    }

    // Pegar o número de caracteres por bloco
    int iBlockSize[iBlocks];
    int iLinesAtBlock = 0;
    int iBlock = 0;
    int iCharsAtBlock = 0;
    while (cText[iChars] != '\0'){
        if (cText[iChars] == '\n'){
            iLines++;
        }
        iCharsAtBlock++;
        if (iLinesAtBlock == iLines/iBlocks){
            cout << iBlock << " " << iCharsAtBlock << endl;
            iBlockSize[iBlock] = iCharsAtBlock;
            iBlock++;
            iLinesAtBlock = 0;
            iCharsAtBlock = 0;
        }
    }

    char** blocks = new char*[iBlocks];
    for (int i = 0; i < iBlocks; i++){
        blocks[i] = new char[iBlockSize[i]];
        for (int j = 0; j < iBlockSize[i]; j++){
            blocks[i][j] = cText[i*iBlockSize[i] + j];
        }
        cout << "foi" << endl;
    }
    cout << "de novo" << endl;
    return blocks;
}

int main(){
    char* cText = blocktext(2, 3)[0];
    cout << cText;
    return 0;
}