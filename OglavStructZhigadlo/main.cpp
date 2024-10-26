#include <iostream>
#include <windows.h>

using namespace std;

/*при моей проверке без данной строчки код не работает,
 данная строчка служит для выравнивания и расположения байтов в памяти
 */
#pragma pack(push, 1)

const BYTE mySignature[] = {0x52, 0x61, 0x72, 0x21, 0x1A, 0x07, 0x00}; //неизменяемый массив в котором находятся эл-ты сигнатуры (7 байт)

typedef struct
{
    // все наши байты в File_Head
    WORD header_crc; //2 байтв байт
    BYTE header_type; //1 байт
    WORD header_flags;
    WORD header_size;

}VolumeHeaderFormat; /* *PVolumeHeaderFormat; псевдоним нашей 1-й структуры с 2.1 Volume Header Format,
                            указатель убрала для себя*/
typedef struct
{
    // все наши байты в File_Head
    DWORD PackSize; //4 байта
    DWORD UnpSize;
    BYTE HostOS;
    DWORD FileCRC;
    DWORD FileTime;
    BYTE UnpVer;
    BYTE Method;
    WORD NameSize;
    DWORD FileAttr;

}FILE_HEAD; // *PFILE_HEAD; псевдоним нашей 2-й структуры

//доп. строчка для #pragma pack(push, 1), возвращает выравнивание по умолчанию

#pragma pack(pop)

int Oglav(const BYTE *dataBuffer, unsigned int bufferSize)
{
    int numberOfFiles = 0;

    // Проверить сигнатуру файла, как на последней лекции
    if(memcmp(dataBuffer, mySignature, sizeof(mySignature)) != 0)
    {
        // Ошибка
        return -1;
    }

    // Отступить от начала файла на длину сигнатуры (7 байт)
    unsigned int fileOffset = sizeof(mySignature);

    // Цикл по архиву
    while(fileOffset < bufferSize)
    {
    //Определяю указатель типа VolumeHeaderFormat на элемент dataBuffer, который является началом новой записи

        VolumeHeaderFormat *currentVolumeHeader = (VolumeHeaderFormat*)&dataBuffer[fileOffset];

        wcout<< "Тип записи: " << hex << uppercase << currentVolumeHeader->header_type << endl;

        // Проверяем тип записи. Для вывода оглавления простых архивов достаточно декодировать только два типа заголовков...
        if(currentVolumeHeader->header_type == 0x73)// 115
        {
            // MAIN_HEAD, пропускаем
            fileOffset += currentVolumeHeader->header_size;
        }
        else if(currentVolumeHeader->header_type == 0x74)
		{
            // FILE_HEAD, выводим имя файла

			const FILE_HEAD *fileHeader = (FILE_HEAD*)&dataBuffer[fileOffset + sizeof(VolumeHeaderFormat)];

			// Имя файла следует сразу после заголовка FILE_HEAD
			string fileName((char*)&dataBuffer[fileOffset + sizeof(VolumeHeaderFormat) + sizeof(FILE_HEAD)],
                    fileHeader->NameSize);

			// Вывод имя файла
			cout << fileName << endl;
			numberOfFiles++;

            // Запись состоит из заголовка и упакованных данных
            fileOffset += currentVolumeHeader->header_size;
            fileOffset += fileHeader->PackSize;
        }
        else if(currentVolumeHeader->header_type == 0x7B)

        {
            // Штатное завершение архива
            break;
        }
		else
		{
			// Другие виды заголовков не обрабатываются и инициируют завершения обработки
			break;
		}
    }

    return numberOfFiles;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    // Открытие файла "Example.rar"
    HANDLE fileHandle = CreateFile("Example.rar",
                                   GENERIC_READ,
                                   0,
                                   NULL,
                                   OPEN_EXISTING,
                                   FILE_ATTRIBUTE_NORMAL,
                                   NULL);

    //проверка открытия

    if (fileHandle == INVALID_HANDLE_VALUE)
    {
        DWORD errorCode = GetLastError();
        wcout<< "Ошибка открытия файла: " << errorCode <<endl;
        return 1;
    }

    // Определить его размер
    DWORD fileSize = GetFileSize(fileHandle, NULL);
    if (fileSize == INVALID_FILE_SIZE)
    {
        wcout<< "Ошибка определения размера файла!"  <<endl;
        CloseHandle(fileHandle);
        return 1;
    }

    //vector<BYTE> dataBuffer(fileSize);
    BYTE *dataBuffer = new BYTE[fileSize]; //дин. массив
    DWORD bytesRead;
    bool readOk = ReadFile(fileHandle, dataBuffer, fileSize, &bytesRead, NULL);

    if(readOk)
    {
        // Файл успешно считан
        wcout << "Файл 'Example.rar' считан!" << endl;
        int numberOfFiles = Oglav(dataBuffer, fileSize);
        wcout << "Всего файлов в архиве: " << numberOfFiles << endl;
    }

    //Закрытие

    bool closed = CloseHandle(fileHandle);
    if(closed)
    {
        cout << "Файл успешно закрыт!" << endl;
    }
    delete [] dataBuffer;
    return 0;
}
