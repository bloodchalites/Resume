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
		wcout << L"�������������: " << PrintCatOrigin(cat->GetOrigin())
			 << L". ���� �����: " << PrintCatColor(cat->GetColor())
			 << L". ���������� �����: " << PrintCatMood(cat->GetMood())
			 << L". ������������: " << PrintCatType(cat->GetType()) << endl;
    }
}

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "Russian");
    wcout << L"�������� ����� ��� �����!\n" << endl;

    SQLContainer db;
    NormalCats cat1222;

    db.AddCat(&cat1222);
    for( int i = 0; i<2 ; i++)
    {
        db.AddCat(Cat::Find(RandomCatOrigin()));
    }

    CatPtr cat = db.GetByIndex(3);

	wcout << L"�������������: " << PrintCatOrigin(cat->GetOrigin()) << ", " <<
	L" ���� �����: " << PrintCatColor(cat->GetColor()) << ", " <<
	L" ���������� �����: " << PrintCatMood(cat->GetMood()) << ", " <<
	L" ������������: " << PrintCatType(cat->GetType()) << endl;

    cout << endl;


    NormalCats cat1;
    HellsCats cat2;
    ParadiseCats cat3;
    CatContainer container1(5);
    container1.AddCat(&cat1);           //
    container1.AddCat(&cat2);           // �������� ������������ ����� � �������
    container1.AddCat(&cat3);           //
    container1.AddCat(new NormalCats);  //�������� ����� �����


    cout << "\n";
	wcout << L"������� ��� ����� �1\n\n";
        //���-�� ����� � �������
	wcout << L"� ������� " << container1.GetCount() << L" ����� �����\n" << endl;
        //����� ������� Iterator1
    Iterator1(container1.GetIterator());

    cout << "\n";
	wcout << L"����-������� ��� ����� �2\n\n";
    MegaCatContainer container2;
    int randomCount = rand()%90;
    for( int i = 0; i < randomCount ; i++)
    {
        container2.AddCat(Cat::Find(RandomCatOrigin()));
    }
    wcout << L"� ����-������� " << container2.GetCount() << L" ����� ����� " << endl;

        //������� ���� ����� �� ����-�������
    //Iterator1(container2.GetIterator());

        // ��������� �1 ������� ������ ����� � ������� �����������
    //Iterator<CatPtr> *it = new CatMoodDecorator(container2.GetIterator(), CatMood::Nice);
        //��������� �2 ������� ������ ������� �����
    //Iterator<CatPtr> *it = new CatTypeDecorator(container2.GetIterator(), CatType::Big);
        // ��������� �3 ������� ������ ����� �����
    //Iterator<CatPtr> *it = new CatColorDecorator(container2.GetIterator(), CatColorEnum::Red);
        //��� ���������� �1 � �2 ������� ������� ����� � �������� �����������
    Iterator<CatPtr> *it = new CatMoodDecorator(new CatTypeDecorator(container2.GetIterator(), CatType::Big ), CatMood::Nice);
    Iterator1(it);

    return 0;
}
