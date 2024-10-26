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
		// ���-�� �����
		Quantity = 100;
		Synchronize(&ClearCatContainer);	 // ������� ��������� ����� ����������� ����� ������
		for( i = 0; i<Quantity ; i++)
		{
			//���������� ����� � ���������, ��������� �� �-���
			Synchronize(&AddAllCats);
			Sleep(50);
			//���������� ���������
			Synchronize(&UpdateProgressThread);
			// ���������� �������
			Synchronize(&UpdateTableAfterAddCats);
		}
		// ��������� �������
		DWORD endTime = GetTickCount();
		processTime = endTime - startTime;
		// �������������� � ������
		Synchronize(&UpdateLabel);
	}
	else if(niceCats)
	{
        // ���-�� �����
		Quantity = 100;
		Synchronize(&ClearCatContainer);	 // ������� ��������� ����� ����������� ����� ������
		for( i = 0; i<Quantity ; i++)
		{
			//���������� ����� � ���������, ��������� �� �-���
			Synchronize(&AddAllCats);
            // ��������� ������� ��������� ����������
			Synchronize(&NiceEmotion);
			// ��������� ������� ����� ���������� ����� � ������� �����������
			Synchronize(&UpdateTableAfterAddCats);
			Sleep(50);

			//���������� ���������
			Synchronize(&UpdateProgressThread);
			
		}
        // ��������� �������
		DWORD endTime = GetTickCount();
		processTime = endTime - startTime;
		// �������������� � ������
		Synchronize(&UpdateLabel);
	}



}
//---------------------------------------------------------------------------
	// �������� �����
void __fastcall  Thread2::AddAllCats()
{
	MainForm->AddCatsContainer();

}
	// ���������� �������
void __fastcall Thread2::UpdateTableAfterAddCats()
{
	FillStringTree(MainForm->HistoryDataBase, MainForm->GetIterator());
}
	// ���������� ���������
void __fastcall Thread2::UpdateProgressThread()
{
	MainForm->ProgressBarThread->Position = i;
}
	// ����� ����� � ������� �����������
void __fastcall Thread2::NiceEmotion()
{
	MainForm->DecoratorNice();
}
	// ������� ������
void __fastcall Thread2::ClearCatContainer()
{
	MainForm->ClearContainer();
}
// �������������� � ������
void __fastcall Thread2::UpdateLabel()
{
	UnicodeString timeStr = UnicodeString(processTime);   // ��������������� � ������
	MainForm->ThreadWorkLabel->Caption = timeStr;
}


