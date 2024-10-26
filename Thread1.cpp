//---------------------------------------------------------------------------
#include <vector>
#include <iostream>
#include <vcl.h>
#include <windows.h>
#pragma hdrstop

using namespace std;
#include "Thread2.h"
#include "Thread1.h"
#include "Iterator.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma link "VirtualTrees.AncestorVCL"
#pragma link "VirtualTrees.BaseAncestorVCL"
#pragma link "VirtualTrees.BaseTree"
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
    // Рандом характеристик
	srand(time(NULL));
    // прописываем для таблицы размер одной записи
	// чтобы выделялось необходимое кол-во памяти для узлов
	HistoryDataBase->NodeDataSize = sizeof(NodeStruct);

	// добавление итератора
	it = container.GetIterator();

}
Iterator<CatPtr>* TMainForm::GetIterator()
{
    return it;
}
//---------------------------------------------------------------------------
void FillStringTree(TVirtualStringTree *HistoryDataBase, Iterator<CatPtr> *it)
{
	HistoryDataBase->BeginUpdate();
		// Очищаем дерево
	HistoryDataBase->Clear();

		// Итератор, выборка только кошек с хорошим настроением
	//Iterator<CatPtr> *it = new CatMoodDecorator(container.GetIterator(), CatMood::Nice);
	int i = 0;
	for(it->First(); !it->IsDone(); it->Next())
	{

			// Генерируем случайную кошку
		CatPtr newCat = it->GetCurrent();

			// Добавляем запись
		PVirtualNode entryNode = HistoryDataBase->AddChild(HistoryDataBase->RootNode);
		// Заполняем данные узла
		NodeStruct *nodeData = (NodeStruct*)HistoryDataBase->GetNodeData(entryNode);

			// Заполняем данные о кошке
		nodeData->Id = i++;
		nodeData->Origin = PrintCatOrigin(newCat->GetOrigin());
		nodeData->Color = PrintCatColor(newCat->GetColor());
		nodeData->Mood = PrintCatMood(newCat->GetMood());
		nodeData->Type = PrintCatType(newCat->GetType());

	}

		// Удаляем итератор
	//delete it;
	HistoryDataBase->EndUpdate();
}
// 1 кнопка без потока отвечающий за "интерактив"
void __fastcall TMainForm::NoGraphicsButtonClick(TObject *Sender)
{
	DWORD startTime = GetTickCount();   // замерять время
	container.Clear(); 					// Очищаем контейнер перед добавлением новых данных
	__int64 NumberOfObjects = 100;
	for(__int64 i=0; i<NumberOfObjects; i++)
	{
			// Добавление кошки
		CatPtr newCat = Cat::Find(RandomCatOrigin());
		container.AddCat(newCat);
		Sleep(50);

			// Установка позиции прогресс-бара
		ProgressBarThread->Position = i;
	}

	DWORD endTime = GetTickCount();     		// время окончания обработки
	DWORD processTime = endTime - startTime;    // Разница времени

	UnicodeString timeStr = UnicodeString(processTime);   // Переобразование в юникод
	ThreadWorkLabel->Caption = timeStr;

	FillStringTree(HistoryDataBase, it);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::HistoryDataBaseGetText(TBaseVirtualTree *Sender, PVirtualNode Node,
		  TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)

{
	if (!Node) return;

	NodeStruct *nodeData = (NodeStruct*)Sender->GetNodeData(Node);
	switch(Column)
	{
		 case 0: CellText = nodeData->Id; break;
		 case 1: CellText = nodeData->Origin; break;
		 case 2: CellText = nodeData->Color; break;
		 case 3: CellText = nodeData->Mood; break;
		 case 4: CellText = nodeData->Type; break;
	}
}
//---------------------------------------------------------------------------
// добавление кошек
void TMainForm::AddCatsContainer()
{
	container.AddCat(Cat::Find(RandomCatOrigin()));
}
// очистка контейнера
void TMainForm::ClearContainer()
{
	container.Clear(); 	 // Очищаем контейнер перед добавлением новых данных
}
void TMainForm::DecoratorNice()
{

	it = new CatMoodDecorator(container.GetIterator(), CatMood::Nice);
}

// нажатие на 2-ю кнопку
void __fastcall TMainForm::ThreadButton1Click(TObject *Sender)
{
	//True - означает запуск определнного цикла в Execute()
	th = new Thread2(true, true, false);
	th->Resume();
}
// Нажатие на 3 кнопку
void __fastcall TMainForm::ThreadButton2Click(TObject *Sender)
{
	th = new Thread2(true, false, true);
	th->Resume();
}
//---------------------------------------------------------------------------
// редактор
void __fastcall TMainForm::WritePleaseClick(TObject *Sender)
{
	// Настройка текста
	WritePlease->Lines->Clear();
	WritePlease->SelAttributes->Name = L"Times New Roman";  // шрифт
	WritePlease->SelAttributes->Size = 16;       // размер шрифта
	WritePlease->SelAttributes->Style = TFontStyles() << fsBold;  // жирный шрифт
	WritePlease->SelAttributes->Color = clBlack;  // цвет текста

	WritePlease->Paragraph->Alignment = taCenter; // Выравнивание текста по центру


	WritePlease->Lines->Add(L"\nСТРАННЫЙ ПРИЮТ ДЛЯ КОШЕК"); // Добавляем текст
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

