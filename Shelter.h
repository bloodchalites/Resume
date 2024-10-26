#ifndef SHELTER_H
#define SHELTER_H
#include <vector>
#include <iostream>
#include <windows.h>
#include "Iterator.h"
#include "sqlite3.h"
using namespace std;

//������ 10 ����� ����������� ������ ��� SQLite!\\
            // ������� 3 ���������� ��� ������ ��������� ����� �����
                            //� ������� "������� ����������" �� ���� ����������

enum class CatBreed                 //������������ ����� �����
{
    MainCoon,
    Russian,
    Sfinks,
    Savanna,
    Persian,
    Munchkin,
    Another = -1
};
enum class CatColorEnum : int       //������������ ������ �����
{
    Black = 0,
    White = 1,
    Red = 2,
    Blue = 3,
    Chocolate = 4,
    Another = -1
};
enum class CatType                  //������������ ������������ �����
{
    Kitty,
    Little,
    Average,
    Big
};
enum class CatMood                  //������������ ���������� �����
{
    Bad,
    Nice,
    Play,           //�������
    Painful         //�����������
};
enum class ParadiseObject
{
    ParadiseWings,
    Halo,
    Bible
};
enum class HellObject
{
    HellWings,
    Hooves,
    Horns
};
enum class OriginCats //������������� �����
{
    NormalCats,
    HellsCats,
    ParadiseCats
};

wstring PrintDemonCat( HellObject demon );
wstring PrintAngelCat( ParadiseObject angel );
wstring PrintNormalCat( CatBreed breed );
wstring PrintCatType( CatType type );
wstring PrintCatMood(CatMood mood );
wstring PrintCatColor(CatColorEnum color );
wstring PrintCatOrigin(OriginCats origin);

OriginCats RandomCatOrigin();

class Cat
{
protected:
    OriginCats origin;
    CatColorEnum color;
    CatMood mood;
    CatType type;
    bool Hungry;
    Cat();
public:
	virtual ~Cat() {}
    OriginCats GetOrigin() const {return origin; }
    CatColorEnum GetColor() const {return color; }
	CatMood GetMood() const { return mood; }
    CatType GetType() const {return type; }
    virtual void View() const = 0;          //������� �����
    virtual void Pat() const = 0;           //��������� �����
    bool GetHungry() const;
    void Feed();                            // ��������� �����

    static Cat *Find(OriginCats origin);       //�����(�������) ����� ������������ ������
};

    //����������� ����� ������� �����
class NormalCats : public Cat
{
private:
    CatBreed Breed;
public:
    CatBreed GetBreed() const {return Breed; }
    NormalCats() : Cat() { origin = OriginCats::NormalCats;
                           type = CatType(rand() % 4);
                           Breed = CatBreed(rand() % 7 - 1);
                           color = CatColorEnum(rand() % 5 - 1);
                           mood = CatMood(rand() % 4);}
    NormalCats(int Origin, int Color, int Mood, int Type)
    {
        origin = (OriginCats)Origin;
        color = (CatColorEnum)Color;
        mood = (CatMood)Mood;
        type = (CatType)Type;
    }
	void View() const { wcout << L"�� �������� ��� ��� ������� ����� � �� ������: "
						<< PrintNormalCat(Breed) << L"\n� �����, �� ��������� ��� ��� "
						<< PrintCatType(type) <<  L" � ��� ����� �������� " << PrintCatMood(mood) << endl; }
    void Pat() const { wcout << L"�� ������� ����� �� �� " << PrintCatColor(color) << L" �������" << endl; }



};

    // ����������� ����� ������ �����
class HellsCats : public Cat
{

private:
    HellObject demon;
public:
    HellsCats() : Cat() { origin = OriginCats::HellsCats;
                          type = CatType(rand() % 4);
                          demon = HellObject(rand() % 3);
                          color = CatColorEnum::Red;
                          mood = CatMood::Bad;}
    HellsCats(int Origin, int Color, int Mood, int Type)
    {
        origin = (OriginCats)Origin;
        color = (CatColorEnum)Color;
        mood = (CatMood)Mood;
        type = (CatType)Type;
    }
	void View() const { wcout << L"�� �������� ��� ��� ����� ������������ � � ��� ���� �������� ����������: "
						<< PrintDemonCat(demon) << L"\n� �����, �� ��������� ��� ��� "
						<< PrintCatType(type) << L" � ��� ����� �������� " << PrintCatMood(mood) << endl;}
    void Pat() const { wcout << L"�� ������� ������ ����� �� �� " << PrintCatColor(color) << L" �������, ��� ��� ��������!" << endl; }
};

    // ����������� ����� ������� �����
class ParadiseCats : public Cat
{
private:
    ParadiseObject angel;
public:
    ParadiseCats() : Cat() { origin = OriginCats::ParadiseCats;
                             type = CatType(rand() % 4);
                             angel = ParadiseObject(rand() % 3);
                             color = CatColorEnum::White;
                             mood = CatMood(rand() % 4);}
    ParadiseCats(int Origin, int Color, int Mood, int Type)
    {
        origin = (OriginCats)Origin;
        color = (CatColorEnum)Color;
        mood = (CatMood)Mood;
        type = (CatType)Type;
    }
	void View() const { wcout << L"�� �������� ��� ��� ����� ������� � � ��� ���� �������� ����������: "
						<< PrintAngelCat(angel) << L"\n� �����, �� ��������� ��� ��� "
						<< PrintCatType(type) << L" � ��� ����� �������� " << PrintCatMood(mood) << endl; }
	void Pat() const { wcout << L"�� ������� ����� �� �� " << PrintCatColor(color) << L" �������, �� ������� ��������..." << endl; }

};

typedef Cat * CatPtr;

    //�������� �����-���������
class BaseContainer                 // ������� ����� ��� ����������
{
protected:
    BaseContainer() {};
public:
    virtual void AddCat(CatPtr newCat) = 0;             // ����������� ����� ��� ���������� ����� � ���������
    virtual int GetCount() const = 0;                   // ����������� ����� ��� ��������� ���������� ����� � ����������
    virtual CatPtr GetByIndex(int index) const = 0;     // ����������� ����� ��� ��������� ����� �� �������
};

    //�������� �1
class CatContainerIterator : public Iterator<CatPtr>
{
private:
    const CatPtr *CatBox;   // ��������� �� ��������� �� ����� (������������ ������ ���������� �� �����)
    int Pos;                // ������� ������� � ����������
    int Quant;              // ����� ���������� ����� � ����������

public:
    // �����������, ����������� ��������� �� ������ ���������� �� ����� � ����� ���������� �����
    CatContainerIterator(const CatPtr *catBox, int count)
    {
        CatBox = catBox;
        Quant = count;
        Pos = 0;
    }
            // ����� ������������� �������� �� ������ ���������� �����
    void First() { Pos = 0; }
            // ����� ���������� �������� � ���������� �������� ���������� �����
    void Next() { Pos++; }
            // ����� ���������, ������ �� �������� ����� ���������� �����
    bool IsDone() const { return Pos >= Quant; }
            // ����� ���������� ��������� �� ������� ������ �����, �� ������� ��������� ��������
    CatPtr GetCurrent() const { return CatBox[Pos]; }
};

    //�1 �����-���������
class CatContainer :  BaseContainer             //��������� � �������
{
private:
    CatPtr *CatBox;                             //��������� �� ��������� �� ����� (���.������ ���������� �� �����)
    int CatCount;                               //���������� �����
    int MaxSize;                                //���� ������ ����������
public:
    virtual ~CatContainer();
    CatContainer(int maxSize);
    void AddCat(CatPtr newCat);                 //�������� ����� � �����
    int GetCount() const { return CatCount; }    //�������� ����� �����
    CatPtr GetByIndex(int i) const { return CatBox[i]; }           //������������� �����
    Iterator<CatPtr> *GetIterator()
    {
        return new CatContainerIterator(CatBox, CatCount);
    }
};

    //�������� ��� 2-�� ���������� (������)
class CatContainerIterator2 : public Iterator<CatPtr>
{
protected:
    // ��������� �� ����������� ������ ���������� �� ������� �����
    const std::vector<CatPtr> *CatBox;
    std::vector<CatPtr>::const_iterator it;

public:
    CatContainerIterator2(const std::vector<CatPtr> *catBox)
    {
        CatBox = catBox;
        it = catBox->begin();
    }
    // ����� ������������� �������� �� ������ ���������� �����
    void First() { it = CatBox->begin(); }
    // ����� ���������� �������� � ���������� �������� ����������
    void Next() { ++it; }
    // ����� ���������� true, ���� �������� ������ ����� ����������
    bool IsDone() const { return it == CatBox->end(); }
    // ����� ���������� ��������� �� ������� ������ �����, �� ������� ��������� ��������
    CatPtr GetCurrent() const { return *it; }
};

    //�������� ��� 3 ����������
class SQL_Container_Iterator_3 : public Iterator<CatPtr>
{
protected:
    BaseContainer * catBox;
    int Pos;
public:
    SQL_Container_Iterator_3(BaseContainer *CatBox)
    {
        catBox = CatBox;
        Pos = 0;
    }
    void First() { Pos = 0; };
    void Next() { Pos++; };
    bool IsDone() const { return Pos >= catBox->GetCount(); };
    CatPtr GetCurrent() const { return catBox->GetByIndex(Pos); };
};

    // �����-��������� �2 ������
class MegaCatContainer : public BaseContainer
{
private:
    // ������ ���������� �� ������� �����
    std::vector<CatPtr> CatBox;

public:
    // ����� ��� ���������� ����� � ���������
    void AddCat(CatPtr newCat) { CatBox.push_back(newCat); }
    // ����� ��� ��������� ���������� ����� � ����������
    int GetCount() const { return CatBox.size();}
    // ����� ��� ��������� ����� �� ������� � ����������
    CatPtr GetByIndex(int index) const { return CatBox[index]; }
    // �����, ������������ �������� ��� ����������
	Iterator<CatPtr> *GetIterator() { return new CatContainerIterator2(&CatBox);}
	void Clear() { CatBox.clear(); }
};

    //��������� �� ������ �� SQLite
class SQLContainer : public BaseContainer
{
protected:
    sqlite3* Database;
    int id;
public:
    SQLContainer(); //�����������
    virtual ~SQLContainer(); //����������
    void AddCat(CatPtr cat);
    int GetCount() const;
    CatPtr GetByIndex(int index) const;

    Iterator<CatPtr> *GetIterator()
    {
        return new SQL_Container_Iterator_3(this);
    };
};


    //����������

    //��������� �1 ��� ������ ����� �� �� ����������
class CatMoodDecorator : public IteratorDecorator<CatPtr>
{
protected:
    CatMood Mood;   // ����������, �� �������� ���������� �����
public:
    CatMoodDecorator(Iterator<CatPtr> *it, CatMood mood) : IteratorDecorator(it)
    {
        Mood = mood;
    }
    // ����� ������������� �������� �� ������ ���������� � ���������� ��� � ������ ����� � ��������� �����������
    void First()
    {
        It->First();
        while (!It->IsDone() && It->GetCurrent()->GetMood() != Mood)
        {
            It->Next();
        }
    }
    // ����� ���������� �������� � ��������� ����� � ��������� �����������
    void Next()
    {
        do
        {
            It->Next();
        } while (!It->IsDone() && It->GetCurrent()->GetMood() != Mood);
    }
};

//��������� �2 ��� ������ ����� �� ����
class CatTypeDecorator : public IteratorDecorator<CatPtr>
{
protected:
    CatType Type;
public:
    CatTypeDecorator(Iterator<CatPtr> *it, CatType type) : IteratorDecorator(it)
    {
        Type = type;
    }
    void First()
    {
        It->First();
        while (!It->IsDone() && It->GetCurrent()->GetType() != Type)
        {
            It->Next();
        }
    }
    void Next()
    {
        do
        {
            It->Next();
        } while (!It->IsDone() && It->GetCurrent()->GetType() != Type);
    }
};

//��������� �3 ��� ������ ����� �� �� �����
class CatColorDecorator : public IteratorDecorator<CatPtr>
{
protected:
    CatColorEnum Color;
public:
    CatColorDecorator(Iterator<CatPtr> *it, CatColorEnum color) : IteratorDecorator(it)
    {
        Color = color;
    }
    void First()
    {
        It->First();
        while (!It->IsDone() && It->GetCurrent()->GetColor() != Color)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();
        } while (!It->IsDone() && It->GetCurrent()->GetColor() != Color);
    }
};


#endif // SHELTER_H
