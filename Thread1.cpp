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
    // ������ �������������
	srand(time(NULL));
    // ����������� ��� ������� ������ ����� ������
	// ����� ���������� ����������� ���-�� ������ ��� �����
	HistoryDataBase->NodeDataSize = sizeof(NodeStruct);

	// ���������� ���������
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
		// ������� ������
	HistoryDataBase->Clear();

		// ��������, ������� ������ ����� � ������� �����������
	//Iterator<CatPtr> *it = new CatMoodDecorator(container.GetIterator(), CatMood::Nice);
	int i = 0;
	for(it->First(); !it->IsDone(); it->Next())
	{

			// ���������� ��������� �����
		CatPtr newCat = it->GetCurrent();

			// ��������� ������
		PVirtualNode entryNode = HistoryDataBase->AddChild(HistoryDataBase->RootNode);
		// ��������� ������ ����
		NodeStruct *nodeData = (NodeStruct*)HistoryDataBase->GetNodeData(entryNode);

			// ��������� ������ � �����
		nodeData->Id = i++;
		nodeData->Origin = PrintCatOrigin(newCat->GetOrigin());
		nodeData->Color = PrintCatColor(newCat->GetColor());
		nodeData->Mood = PrintCatMood(newCat->GetMood());
		nodeData->Type = PrintCatType(newCat->GetType());

	}

		// ������� ��������
	//delete it;
	HistoryDataBase->EndUpdate();
}
// 1 ������ ��� ������ ���������� �� "����������"
void __fastcall TMainForm::NoGraphicsButtonClick(TObject *Sender)
{
	DWORD startTime = GetTickCount();   // �������� �����
	container.Clear(); 					// ������� ��������� ����� ����������� ����� ������
	__int64 NumberOfObjects = 100;
	for(__int64 i=0; i<NumberOfObjects; i++)
	{
			// ���������� �����
		CatPtr newCat = Cat::Find(RandomCatOrigin());
		container.AddCat(newCat);
		Sleep(50);

			// ��������� ������� ��������-����
		ProgressBarThread->Position = i;
	}

	DWORD endTime = GetTickCount();     		// ����� ��������� ���������
	DWORD processTime = endTime - startTime;    // ������� �������

	UnicodeString timeStr = UnicodeString(processTime);   // ��������������� � ������
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
// ���������� �����
void TMainForm::AddCatsContainer()
{
	container.AddCat(Cat::Find(RandomCatOrigin()));
}
// ������� ����������
void TMainForm::ClearContainer()
{
	container.Clear(); 	 // ������� ��������� ����� ����������� ����� ������
}
void TMainForm::DecoratorNice()
{

	it = new CatMoodDecorator(container.GetIterator(), CatMood::Nice);
}

// ������� �� 2-� ������
void __fastcall TMainForm::ThreadButton1Click(TObject *Sender)
{
	//True - �������� ������ ������������ ����� � Execute()
	th = new Thread2(true, true, false);
	th->Resume();
}
// ������� �� 3 ������
void __fastcall TMainForm::ThreadButton2Click(TObject *Sender)
{
	th = new Thread2(true, false, true);
	th->Resume();
}
//---------------------------------------------------------------------------
// ��������
void __fastcall TMainForm::WritePleaseClick(TObject *Sender)
{
	// ��������� ������
	WritePlease->Lines->Clear();
	WritePlease->SelAttributes->Name = L"Times New Roman";  // �����
	WritePlease->SelAttributes->Size = 16;       // ������ ������
	WritePlease->SelAttributes->Style = TFontStyles() << fsBold;  // ������ �����
	WritePlease->SelAttributes->Color = clBlack;  // ���� ������

	WritePlease->Paragraph->Alignment = taCenter; // ������������ ������ �� ������


	WritePlease->Lines->Add(L"\n�������� ����� ��� �����"); // ��������� �����
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

