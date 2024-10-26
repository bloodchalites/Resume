#include <iostream>
#include <windows.h>

using namespace std;

/*��� ���� �������� ��� ������ ������� ��� �� ��������,
 ������ ������� ������ ��� ������������ � ������������ ������ � ������
 */
#pragma pack(push, 1)

const BYTE mySignature[] = {0x52, 0x61, 0x72, 0x21, 0x1A, 0x07, 0x00}; //������������ ������ � ������� ��������� ��-�� ��������� (7 ����)

typedef struct
{
    // ��� ���� ����� � File_Head
    WORD header_crc; //2 ����� ����
    BYTE header_type; //1 ����
    WORD header_flags;
    WORD header_size;

}VolumeHeaderFormat; /* *PVolumeHeaderFormat; ��������� ����� 1-� ��������� � 2.1 Volume Header Format,
                            ��������� ������ ��� ����*/
typedef struct
{
    // ��� ���� ����� � File_Head
    DWORD PackSize; //4 �����
    DWORD UnpSize;
    BYTE HostOS;
    DWORD FileCRC;
    DWORD FileTime;
    BYTE UnpVer;
    BYTE Method;
    WORD NameSize;
    DWORD FileAttr;

}FILE_HEAD; // *PFILE_HEAD; ��������� ����� 2-� ���������

//���. ������� ��� #pragma pack(push, 1), ���������� ������������ �� ���������

#pragma pack(pop)

int Oglav(const BYTE *dataBuffer, unsigned int bufferSize)
{
    int numberOfFiles = 0;

    // ��������� ��������� �����, ��� �� ��������� ������
    if(memcmp(dataBuffer, mySignature, sizeof(mySignature)) != 0)
    {
        // ������
        return -1;
    }

    // ��������� �� ������ ����� �� ����� ��������� (7 ����)
    unsigned int fileOffset = sizeof(mySignature);

    // ���� �� ������
    while(fileOffset < bufferSize)
    {
    //��������� ��������� ���� VolumeHeaderFormat �� ������� dataBuffer, ������� �������� ������� ����� ������

        VolumeHeaderFormat *currentVolumeHeader = (VolumeHeaderFormat*)&dataBuffer[fileOffset];

        wcout<< "��� ������: " << hex << uppercase << currentVolumeHeader->header_type << endl;

        // ��������� ��� ������. ��� ������ ���������� ������� ������� ���������� ������������ ������ ��� ���� ����������...
        if(currentVolumeHeader->header_type == 0x73)// 115
        {
            // MAIN_HEAD, ����������
            fileOffset += currentVolumeHeader->header_size;
        }
        else if(currentVolumeHeader->header_type == 0x74)
		{
            // FILE_HEAD, ������� ��� �����

			const FILE_HEAD *fileHeader = (FILE_HEAD*)&dataBuffer[fileOffset + sizeof(VolumeHeaderFormat)];

			// ��� ����� ������� ����� ����� ��������� FILE_HEAD
			string fileName((char*)&dataBuffer[fileOffset + sizeof(VolumeHeaderFormat) + sizeof(FILE_HEAD)],
                    fileHeader->NameSize);

			// ����� ��� �����
			cout << fileName << endl;
			numberOfFiles++;

            // ������ ������� �� ��������� � ����������� ������
            fileOffset += currentVolumeHeader->header_size;
            fileOffset += fileHeader->PackSize;
        }
        else if(currentVolumeHeader->header_type == 0x7B)

        {
            // ������� ���������� ������
            break;
        }
		else
		{
			// ������ ���� ���������� �� �������������� � ���������� ���������� ���������
			break;
		}
    }

    return numberOfFiles;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    // �������� ����� "Example.rar"
    HANDLE fileHandle = CreateFile("Example.rar",
                                   GENERIC_READ,
                                   0,
                                   NULL,
                                   OPEN_EXISTING,
                                   FILE_ATTRIBUTE_NORMAL,
                                   NULL);

    //�������� ��������

    if (fileHandle == INVALID_HANDLE_VALUE)
    {
        DWORD errorCode = GetLastError();
        wcout<< "������ �������� �����: " << errorCode <<endl;
        return 1;
    }

    // ���������� ��� ������
    DWORD fileSize = GetFileSize(fileHandle, NULL);
    if (fileSize == INVALID_FILE_SIZE)
    {
        wcout<< "������ ����������� ������� �����!"  <<endl;
        CloseHandle(fileHandle);
        return 1;
    }

    //vector<BYTE> dataBuffer(fileSize);
    BYTE *dataBuffer = new BYTE[fileSize]; //���. ������
    DWORD bytesRead;
    bool readOk = ReadFile(fileHandle, dataBuffer, fileSize, &bytesRead, NULL);

    if(readOk)
    {
        // ���� ������� ������
        wcout << "���� 'Example.rar' ������!" << endl;
        int numberOfFiles = Oglav(dataBuffer, fileSize);
        wcout << "����� ������ � ������: " << numberOfFiles << endl;
    }

    //��������

    bool closed = CloseHandle(fileHandle);
    if(closed)
    {
        cout << "���� ������� ������!" << endl;
    }
    delete [] dataBuffer;
    return 0;
}
