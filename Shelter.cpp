#include <iostream>

using namespace std;


#include "Shelter.h"

wstring PrintDemonCat( HellObject demon )
{
    switch(demon)
    {
		case HellObject::HellWings : return L"������������ ������";
		case HellObject::Hooves : return L"������";
		case HellObject::Horns : return L"����";
    }
}

wstring PrintAngelCat( ParadiseObject angel )
{
    switch(angel)
    {
		case ParadiseObject::ParadiseWings : return L"���������� ������";
		case ParadiseObject::Halo : return L"����";
		case ParadiseObject::Bible : return L"������";
    }
}

wstring PrintNormalCat( CatBreed breed )
{
    switch(breed)
    {
		case CatBreed::MainCoon : return L"����-���";
		case CatBreed::Russian : return L"������� ������� �����";
		case CatBreed::Sfinks : return L"������";
		case CatBreed::Savanna : return L"�������";
		case CatBreed::Persian : return L"���������� �����";
		case CatBreed::Munchkin : return L"�������";
        case CatBreed::Another : return L"������ ������ �����";
    }
}

wstring PrintCatType( CatType type )
{
    switch(type)
    {
		case CatType::Kitty : return L"������";
		case CatType::Little : return L"����������� �����";
		case CatType::Average : return L"������� �����";
		case CatType::Big : return L"������� �����";
    }
}

wstring PrintCatMood(CatMood mood )
{
    switch(mood)
    {
	case CatMood::Bad : return L"������";
	case CatMood::Nice : return L"��������";
	case CatMood::Play : return L"�������";
	case CatMood::Painful : return L"�������� �����������";
    }
}

wstring PrintCatColor(CatColorEnum color )
{
    switch(color)
    {
		case CatColorEnum::Red : return L"�����";
		case CatColorEnum::Black : return L"������";
		case CatColorEnum::White : return L"�����";
		case CatColorEnum::Blue : return L"�����������";
		case CatColorEnum::Chocolate : return L"����������";
		case CatColorEnum::Another : return L"������������";
    }
}
wstring PrintCatOrigin(OriginCats origin)
{
    switch(origin)
    {
		case OriginCats::HellsCats : return L"������ �����";
		case OriginCats::NormalCats : return L"������� �����";
        case OriginCats::ParadiseCats : return L"������� �����";
    }
}

Cat *Cat::Find(OriginCats origin) //������������� �����
{
    switch(origin)
    {
        case OriginCats::NormalCats: return new NormalCats;
        case OriginCats::HellsCats: return new HellsCats;
        case OriginCats::ParadiseCats: return new ParadiseCats;
        default: return nullptr;
    }
}

OriginCats RandomCatOrigin()
{
    return OriginCats(rand() % 3);
}
   //������ ������ �����

Cat::Cat()
{
    Hungry = bool(rand() % 2);
}

    //����� �����

bool Cat::GetHungry() const
{
    if(Hungry == 0){ cout << "������� ����� �������! \n"; }
    else { cout << "������� ����� ����! \n"; }
}

    //��������� �����

void Cat::Feed()
{
    if(Hungry == 0)
    {
        cout << "�� ��������� ����� ������" << endl;
        Hungry = 1;
        GetHungry();
    }
}

    //����������� ������ CatContainer � ��������� ������������ ������ ����������

CatContainer::CatContainer(int maxSize)
{
    CatBox = new CatPtr[maxSize];   //���. ������ ������� �������

    for(int i=0; i<maxSize; i++)
    {
        CatBox[i] = NULL;           //���������� � ���������� ��� ������
    }

    CatCount = 0;                   //���-�� ����� � ����������
    MaxSize = maxSize;              //���� ������ ����� ������������� ������� ����������
}

    //����������� �����, ������� ������������ �� �������((

CatContainer::~CatContainer()
{
    for(int i=0; i< MaxSize; i++)
    {
        if(CatBox[i] != NULL)       //���� � ���������� �� ���� �����
        {
            delete CatBox[i];       //�� ��������� ���������
            CatBox[i] = NULL;       // � ��������� ����� ����
        }
    }

    delete [] CatBox;
}

    //���������� ����� � �������

void CatContainer::AddCat(CatPtr newCat)
{
    if(CatCount != MaxSize)
    {
        CatBox[CatCount++] = newCat;
        static int n = 1;
        cout << "�������� � ������� " << n++ << " �����"<< endl;
    }
    else
    {
        cout << "������� ����������� �������" << endl;
    }
}
SQLContainer::SQLContainer()
{
    int  openResult = sqlite3_open("Table.db", &Database);

    if(openResult != SQLITE_OK) //���� �� ������ ������� ���� ������
    {
        wcout << L"Error opening database!" << endl;
    }

    id = 1;
}

SQLContainer::~SQLContainer()
{
	string request = "DELETE FROM cats";
    char *errmsg;
	int execResult = sqlite3_exec(Database, request.c_str(), NULL, 0, &errmsg);

    if(execResult != SQLITE_OK)
    {
        cout << "Request execution error!" << endl;
        cout << errmsg << endl;
    }

    int close_result = sqlite3_close(Database);
    //�������� ��
    if(close_result == SQLITE_OK)
    {
        cout << "The file (Database) is closed" << endl;
	}

}

void SQLContainer::AddCat(CatPtr cat)
{
    int origin = (int)cat->GetOrigin();
    int color = (int)cat->GetColor();
    int mood = (int)cat->GetMood();
    int type = (int)cat->GetType();
    int specific;

    string request = "INSERT INTO cats (Id, Origin, Color, Mood, Type) VALUES (" + to_string(id) + ", "
                                                                                 + to_string(origin) + ", "
                                                                                 + to_string(color) + ", "
                                                                                 + to_string(mood) + ", "
                                                                                 + to_string(type) + ") ";

    id++;


    cout << request << endl;

    char *errmsg;

    int execResult = sqlite3_exec(Database, request.c_str(), NULL, 0, &errmsg);

    if(execResult != SQLITE_OK)
    {
        cout << "������ ���������� �������!" << endl;
        cout << errmsg << endl;
    }

}
int SQLContainer::GetCount() const
{
    string request = "SELECT count(*) FROM cats";

    sqlite3_stmt *pStatement;

    int execResult2 = sqlite3_prepare_v2(Database,
                                         request.c_str(),
                                         -1,
                                         &pStatement, NULL);

    if(execResult2 != SQLITE_OK)
    {
        wcout << "������ ���������� �������!" << endl;
        const char *errmsg2 = sqlite3_errmsg(Database);
        cout << errmsg2 << endl;
    }
    //���������� �������
    int execResult3 = sqlite3_step(pStatement);
    int n;
    if(execResult3 == SQLITE_ROW)
    {
        n = sqlite3_column_int(pStatement, 0 /* ����� �������*/);
    }

    sqlite3_finalize(pStatement); //������� ������
    return n;
}

CatPtr SQLContainer::GetByIndex(int i) const
{
    string request = "SELECT * FROM cats WHERE Id=" + to_string(i);

    sqlite3_stmt *pStatement;

    int execResult2 = sqlite3_prepare_v2(Database,
                                         request.c_str(),
                                         -1,
                                         &pStatement, NULL);

    if(execResult2 != SQLITE_OK)
    {
        wcout << "������ ���������� �������!" << endl;
        const char *errmsg2 = sqlite3_errmsg(Database);
        cout << errmsg2 << endl;
    }
    //���������� �������
    int execResult3 = sqlite3_step(pStatement);

    int origin;
    int Color;
    int Mood;
    int Type;

    if(execResult3 == SQLITE_ROW)
    {
        origin = sqlite3_column_int(pStatement, 1);
        Color = sqlite3_column_int(pStatement, 2);
        Mood = sqlite3_column_int(pStatement, 3);
        Type = sqlite3_column_int(pStatement, 4);
    }

    switch((OriginCats)origin)
    {
        case OriginCats::NormalCats: return new NormalCats(origin, Color, Mood, Type);
        case OriginCats::HellsCats: return new HellsCats(origin, Color, Mood, Type);
        case OriginCats::ParadiseCats: return new ParadiseCats(origin, Color, Mood, Type);
        default: return nullptr;
    }

}




