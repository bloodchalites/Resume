#include <iostream>
#include <cstdlib>
#include <ctime>
#include <list>


using namespace std;


#include "Shelter.h"


void Iterator1(Iterator<CatPtr> *it)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        CatPtr cat = it->GetCurrent();
		wcout << L"Происхождение: " << PrintCatOrigin(cat->GetOrigin())
			 << L". Цвет кошки: " << PrintCatColor(cat->GetColor())
			 << L". Настроение кошки: " << PrintCatMood(cat->GetMood())
			 << L". Телосложение: " << PrintCatType(cat->GetType()) << endl;
    }
}

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "Russian");
    wcout << L"Странный приют для кошек!\n" << endl;

    SQLContainer db;
    NormalCats cat1222;

    db.AddCat(&cat1222);
    for( int i = 0; i<2 ; i++)
    {
        db.AddCat(Cat::Find(RandomCatOrigin()));
    }

    CatPtr cat = db.GetByIndex(3);

	wcout << L"Происхождение: " << PrintCatOrigin(cat->GetOrigin()) << ", " <<
	L" Цвет кошки: " << PrintCatColor(cat->GetColor()) << ", " <<
	L" Настроение кошки: " << PrintCatMood(cat->GetMood()) << ", " <<
	L" Телосложение: " << PrintCatType(cat->GetType()) << endl;

    cout << endl;


    NormalCats cat1;
    HellsCats cat2;
    ParadiseCats cat3;
    CatContainer container1(5);
    container1.AddCat(&cat1);           //
    container1.AddCat(&cat2);           // ДОБАВИТЬ СУЩЕСТВУЮЩИХ КОШЕК В КОРОБКУ
    container1.AddCat(&cat3);           //
    container1.AddCat(new NormalCats);  //Добавить новую кошку


    cout << "\n";
	wcout << L"Коробка для кошек №1\n\n";
        //кол-во кошек в коробке
	wcout << L"В коробке " << container1.GetCount() << L" кошек всего\n" << endl;
        //вызов функции Iterator1
    Iterator1(container1.GetIterator());

    cout << "\n";
	wcout << L"Мега-Коробка для кошек №2\n\n";
    MegaCatContainer container2;
    int randomCount = rand()%90;
    for( int i = 0; i < randomCount ; i++)
    {
        container2.AddCat(Cat::Find(RandomCatOrigin()));
    }
    wcout << L"В мега-коробке " << container2.GetCount() << L" кошек всего " << endl;

        //выводит всех кошек их мега-коробки
    //Iterator1(container2.GetIterator());

        // декоратор №1 выводит только кошек с отличны настроением
    //Iterator<CatPtr> *it = new CatMoodDecorator(container2.GetIterator(), CatMood::Nice);
        //декоратор №2 выводит только больших кошек
    //Iterator<CatPtr> *it = new CatTypeDecorator(container2.GetIterator(), CatType::Big);
        // декоратор №3 выводит только рыжих кошек
    //Iterator<CatPtr> *it = new CatColorDecorator(container2.GetIterator(), CatColorEnum::Red);
        //Два декоратора №1 и №2 выводит большую кошку с отличным настроением
    Iterator<CatPtr> *it = new CatMoodDecorator(new CatTypeDecorator(container2.GetIterator(), CatType::Big ), CatMood::Nice);
    Iterator1(it);

    return 0;
}
