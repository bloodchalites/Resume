#include <iostream>

using namespace std;


#include "Shelter.h"

wstring PrintDemonCat( HellObject demon )
{
    switch(demon)
    {
		case HellObject::HellWings : return L"демонические крылья";
		case HellObject::Hooves : return L"копыта";
		case HellObject::Horns : return L"рога";
    }
}

wstring PrintAngelCat( ParadiseObject angel )
{
    switch(angel)
    {
		case ParadiseObject::ParadiseWings : return L"ангельские крылья";
		case ParadiseObject::Halo : return L"нимб";
		case ParadiseObject::Bible : return L"Библия";
    }
}

wstring PrintNormalCat( CatBreed breed )
{
    switch(breed)
    {
		case CatBreed::MainCoon : return L"Мейн-Кун";
		case CatBreed::Russian : return L"Русская голубая кошка";
		case CatBreed::Sfinks : return L"Сфинкс";
		case CatBreed::Savanna : return L"Саванна";
		case CatBreed::Persian : return L"Персидская кошка";
		case CatBreed::Munchkin : return L"Манчкин";
        case CatBreed::Another : return L"Другая порода кошки";
    }
}

wstring PrintCatType( CatType type )
{
    switch(type)
    {
		case CatType::Kitty : return L"котёнок";
		case CatType::Little : return L"миниатюрная кошка";
		case CatType::Average : return L"средняя кошка";
		case CatType::Big : return L"большая кошка";
    }
}

wstring PrintCatMood(CatMood mood )
{
    switch(mood)
    {
	case CatMood::Bad : return L"плохое";
	case CatMood::Nice : return L"отличное";
	case CatMood::Play : return L"игривое";
	case CatMood::Painful : return L"довольно болезненное";
    }
}

wstring PrintCatColor(CatColorEnum color )
{
    switch(color)
    {
		case CatColorEnum::Red : return L"рыжый";
		case CatColorEnum::Black : return L"черный";
		case CatColorEnum::White : return L"белый";
		case CatColorEnum::Blue : return L"голубоватый";
		case CatColorEnum::Chocolate : return L"шоколадный";
		case CatColorEnum::Another : return L"разноцветный";
    }
}
wstring PrintCatOrigin(OriginCats origin)
{
    switch(origin)
    {
		case OriginCats::HellsCats : return L"Адская кошка";
		case OriginCats::NormalCats : return L"Обычная кошка";
        case OriginCats::ParadiseCats : return L"Райская кошка";
    }
}

Cat *Cat::Find(OriginCats origin) //Происхождение кошки
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
   //РАНДОМ ГОЛОДА КОШЕК

Cat::Cat()
{
    Hungry = bool(rand() % 2);
}

    //голод кошек

bool Cat::GetHungry() const
{
    if(Hungry == 0){ cout << "Кажется кошка голодна! \n"; }
    else { cout << "Кажется кошка сыта! \n"; }
}

    //покормить кошку

void Cat::Feed()
{
    if(Hungry == 0)
    {
        cout << "Вы покормили кошку мяском" << endl;
        Hungry = 1;
        GetHungry();
    }
}

    //конструктор класса CatContainer и спользует максимальный размер контейнера

CatContainer::CatContainer(int maxSize)
{
    CatBox = new CatPtr[maxSize];   //дин. массив размера максайз

    for(int i=0; i<maxSize; i++)
    {
        CatBox[i] = NULL;           //изначально в контейнере нет никого
    }

    CatCount = 0;                   //кол-во кошек в коштейнере
    MaxSize = maxSize;              //макс размер равен максимальному размеру контейнера
}

    //Уничтожение кошек, назовем освобождение из коробки((

CatContainer::~CatContainer()
{
    for(int i=0; i< MaxSize; i++)
    {
        if(CatBox[i] != NULL)       //если в контейнере не нуль кошек
        {
            delete CatBox[i];       //то удаляется контейнер
            CatBox[i] = NULL;       // и контейнер снова пуст
        }
    }

    delete [] CatBox;
}

    //Добавление кошки в коробку

void CatContainer::AddCat(CatPtr newCat)
{
    if(CatCount != MaxSize)
    {
        CatBox[CatCount++] = newCat;
        static int n = 1;
        cout << "Посадили в коробку " << n++ << " кошек"<< endl;
    }
    else
    {
        cout << "Коробка переполнена кошками" << endl;
    }
}
SQLContainer::SQLContainer()
{
    int  openResult = sqlite3_open("Table.db", &Database);

    if(openResult != SQLITE_OK) //если не смогли открыть базу данных
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
    //закрытие БД
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
        cout << "Ошибка выполнения запроса!" << endl;
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
        wcout << "Ошибка подготовки запроса!" << endl;
        const char *errmsg2 = sqlite3_errmsg(Database);
        cout << errmsg2 << endl;
    }
    //выполнение запроса
    int execResult3 = sqlite3_step(pStatement);
    int n;
    if(execResult3 == SQLITE_ROW)
    {
        n = sqlite3_column_int(pStatement, 0 /* номер столбца*/);
    }

    sqlite3_finalize(pStatement); //очистка памяти
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
        wcout << "Ошибка подготовки запроса!" << endl;
        const char *errmsg2 = sqlite3_errmsg(Database);
        cout << errmsg2 << endl;
    }
    //Выполнение запроса
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




