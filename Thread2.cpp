//---------------------------------------------------------------------------
#include <System.hpp>
#include "Thread1.h"
#include "Shelter.h"

#pragma hdrstop

#include "Thread2.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall Thread2::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall Thread2::Thread2(bool CreateSuspended, bool allcats, bool nicecats)
	: TThread(CreateSuspended)
{
	FreeOnTerminate = true;
	allCats = allcats;
	niceCats = nicecats;
}
//---------------------------------------------------------------------------
void __fastcall Thread2::Execute()
{
	DWORD startTime = GetTickCount();
	if(allCats)
	{
		// кол-во кошек
		Quantity = 100;
		Synchronize(&ClearCatContainer);	 // ќчищаем контейнер перед добавлением новых данных
		for( i = 0; i<Quantity ; i++)
		{
			//ƒобавление кошки в контейнер, указатель на ф-цию
			Synchronize(&AddAllCats);
			Sleep(50);
			//ќбновление прогресса
			Synchronize(&UpdateProgressThread);
			// «аполнение таблицы
			Synchronize(&UpdateTableAfterAddCats);
		}
		// окончание времени
		DWORD endTime = GetTickCount();
		processTime = endTime - startTime;
		// ѕреобразование в юникод
		Synchronize(&UpdateLabel);
	}
	else if(niceCats)
	{
        // кол-во кошек
		Quantity = 100;
		Synchronize(&ClearCatContainer);	 // ќчищаем контейнер перед добавлением новых данных
		for( i = 0; i<Quantity ; i++)
		{
			//ƒобавление кошки в контейнер, указатель на ф-цию
			Synchronize(&AddAllCats);
            // декоратор выборка отличного настроени€
			Synchronize(&NiceEmotion);
			// ќбновл€ем таблицу после добавлени€ кошек с хорошим настроением
			Synchronize(&UpdateTableAfterAddCats);
			Sleep(50);

			//ќбновление прогресса
			Synchronize(&UpdateProgressThread);
			
		}
        // окончание времени
		DWORD endTime = GetTickCount();
		processTime = endTime - startTime;
		// ѕреобразование в юникод
		Synchronize(&UpdateLabel);
	}



}
//---------------------------------------------------------------------------
	// ƒобавить кошек
void __fastcall  Thread2::AddAllCats()
{
	MainForm->AddCatsContainer();

}
	// заполнение таблицы
void __fastcall Thread2::UpdateTableAfterAddCats()
{
	FillStringTree(MainForm->HistoryDataBase, MainForm->GetIterator());
}
	// обновление прогресса
void __fastcall Thread2::UpdateProgressThread()
{
	MainForm->ProgressBarThread->Position = i;
}
	// Ќайти кошек с хорошим настроением
void __fastcall Thread2::NiceEmotion()
{
	MainForm->DecoratorNice();
}
	// очистка пам€ти
void __fastcall Thread2::ClearCatContainer()
{
	MainForm->ClearContainer();
}
// ѕреобразование в юникод
void __fastcall Thread2::UpdateLabel()
{
	UnicodeString timeStr = UnicodeString(processTime);   // ѕереобразование в юникод
	MainForm->ThreadWorkLabel->Caption = timeStr;
}


