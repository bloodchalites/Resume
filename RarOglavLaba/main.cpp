#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

void Oglavlenie(vector<unsigned char> dataBuffer)
{

    size_t currentPos = 22;
    int currentHeadSize = 0; //размер текущего заголовка
    int currentPackSize = 0; //размер в байтах, после заголовка
    int currentNameSize = 0; //длина имени
    string currFileName = "";//текущее имя
    while(currentPos <= dataBuffer.size())
    {
        if(dataBuffer[currentPos] == 0x74)
        {
            currentHeadSize = (dataBuffer[currentPos+4] << 8) + dataBuffer[currentPos+3];

            currentPackSize = (dataBuffer[currentPos+8] << 24) +
                              (dataBuffer[currentPos+7] << 16) +
                              (dataBuffer[currentPos+6] << 8) +
                              dataBuffer[currentPos+5];
            currentNameSize = (dataBuffer[currentPos+25] << 8) + dataBuffer[currentPos+24];
            for(size_t i = currentPos+30; i != currentPos+30+currentNameSize; i++)
            {
                currFileName.push_back(dataBuffer[i]);
            }
            cout << currFileName << endl;
            cout << "\n";

        }

        currentPos = currentPos + currentHeadSize + currentPackSize;
        currFileName = "";
    }



}


int main()
{


    HANDLE fileHandle = CreateFile("Example.rar", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if(fileHandle == INVALID_HANDLE_VALUE)
    {
        cout << "Opening error!"<< endl;
    }


    DWORD fileSize = GetFileSize(fileHandle, NULL);

    vector<unsigned char> dataBuffer(fileSize);


    DWORD bytesRead;
    bool readOk = ReadFile(
            fileHandle,
            &dataBuffer[0],
            fileSize,
            &bytesRead,
            NULL
            );

    Oglavlenie(dataBuffer);

    dataBuffer.clear();

    bool closed = CloseHandle(fileHandle);
    if(closed)
    {
        cout << "\n\nFile closed" << endl;
    }

}
