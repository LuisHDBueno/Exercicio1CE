#include <iostream>
#include <fstream>
using namespace std;

class Text{
    public:
        // Atributos
        // Texto Completo
        char* cText;
        // Número de Caracteres por bloco
        int* iBlockSize;

        Text(string path, int iRepeat = 1){
            // Ler o arquivo
            if (iRepeat > 1){
                multiply(iRepeat);
            }
            cText = read(path);
        }

        void multiply(int iRepeat){
            // rodar arquivo python com argumento iRepeat
            string command = "python3 multiply_text.py " + to_string(iRepeat);
            system(command.c_str());
        }

        char* read(string path) {
            streampos size;
            char* memblock;

            ifstream file (path, ios::in|ios::binary|ios::ate);
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

        int* blocktext(int iBlocks){
            int iLines = 0;
            int iChars = 0;
            while (cText[iChars] != '\0'){
                if (cText[iChars] == '\n'){
                    iLines++;
                }
                iChars++;
            }

            // Pegar o número de caracteres por bloco
            iBlockSize = new int[iBlocks];
            int iBlockLines = 0;
            int iBlockChars = 0;
            int iBlock = 0;
            while (cText[iBlockChars] != '\0'){
                if (cText[iBlockChars] == '\n'){
                    iBlockLines++;
                }
                iBlockChars++;
                if (iBlockLines == iLines / iBlocks){
                    iBlockSize[iBlock] = iBlockChars;
                    iBlock++;
                    iBlockLines = 0;
                }
            }
            
            iBlockSize[iBlocks - 1] = iChars - iBlockSize[iBlocks - 2];
            return iBlockSize;
        }
};

/* Exemplo de uso
int main(){
    Text* text = new Text("data/multiplied.txt");
    int* iBlockSize = text -> blocktext(5);
    cout << iBlockSize[0] << endl;
    for (int i = 0; i < iBlockSize[0]; i++){
        cout << text -> cText[i];
    }
    return 0;
}
*/