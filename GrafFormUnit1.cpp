//---------------------------------------------------------------------------
#include <vector>
#include <iostream>
#include <vcl.h>

#pragma hdrstop
#include "sqlite3.h"

using namespace std;

#include "GrafFormUnit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma link "VirtualTrees.AncestorVCL"
#pragma link "VirtualTrees.BaseAncestorVCL"
#pragma link "VirtualTrees.BaseTree"
#pragma resource "*.dfm"

TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner) : TForm(Owner)
{
	HistoryDataBase->NodeDataSize = sizeof(NodeStruct); // ����������� ��� ������� ������ ����� ������
														// ����� ���������� ����������� ���-�� ������ ��� �����

	//������ ������ �� ���������� ��� �����������, ���� �� ������� ��
	FillNode->Enabled = false;
	DeleteStrock->Enabled = false;
    DeleteDataBase->Enabled = false;
}
//--------------------------------------------------------------------------

// ����� �������� ��
bool TMainForm::OpenDataBase(const WCHAR *fileName)
{
	int openResult = sqlite3_open16(fileName, &DataBase);
	if (openResult == SQLITE_OK) {
		return true;
	}
	else{
		return false;
    }

}

//�������� �� ��� ������� � ����������� ��������

void __fastcall TMainForm::OpenDBClick(TObject *Sender)
{
	wstring fileName;

	// dialogovoe okno
    if(OpenDataBaseDialog->Execute())
    {
		fileName = OpenDataBaseDialog->FileName.c_str(); //prisvaivanie
    }

	if(!fileName.empty())
	{

		FileNameEdit->Text = fileName.c_str();     //����������� ���� ����� � �������� ����
		InfoLabel->Caption = fileName.c_str();     //����������� ���� ����� � ���������� ����

		FillNode->Enabled = true;         		   //������ ������ ���������� ��� �����������
		// �������� ���������� ����������
		const vector<wstring> Proverka = {L".sqlite", L".db"};  // ���������� ��

		// proverka rashireniya
		bool isProverka = false;
		for(const auto& ext : Proverka)
        {
			if(fileName.size() >= ext.size() &&
				fileName.compare(fileName.size() - ext.size(), ext.size(), ext) == 0)
            {
				isProverka = true;
				break;

            }
        }

		if(isProverka)        //  ������
        {
			if(!OpenDataBase(fileName.c_str()))
            {
                Application->MessageBox(L"������ �������� ���� ������!", L"������", MB_OK);
            }
        }
        else
		{
			// ��� �������� ������ ������
			MessageDlg(L"������������ ������ �����! ����������, �������� ���� ���� ������ Chromium.", mtWarning, TMsgDlgButtons() << mbOK, 0);
			//Application->MessageBox(L"������������ ������ �����! ����������, �������� ���� ���� ������ Chromium.", L"������", MB_OK);
		}
    }
}

//��������� ������� �����
void TMainForm::FillStringTree(TVirtualStringTree *HistoryDataBase)
{
	HistoryDataBase->BeginUpdate();

	//�������� ������
	HistoryDataBase->Clear();

	// ����������� ������������� SQLite � ����� ������
	sqlite3_stmt *pStatement;

    int execResult1 = sqlite3_prepare16_v2(DataBase,
										 L"SELECT url, title, last_visit_time FROM urls",
                                         -1, //����� ����� �������� ����� ������� ���������
										 &pStatement, NULL);
    if(execResult1 != SQLITE_OK)
    {
        wcout << "������ ���������� �������!" << endl;
        const char *errmsg2 = sqlite3_errmsg(DataBase);
		cout << errmsg2 << endl;
	}
	int stepResult = SQLITE_DONE; // �� �������� ������� ������ ���������� ���� ��� ������ � ������ ����������

	for(ULONGLONG i=0; i<1000; i++)
	{
		int stepResult = sqlite3_step(pStatement);
		if(stepResult != SQLITE_ROW)
		{
			break;
		}
		  //��������� ������
		PVirtualNode entryNode = HistoryDataBase->AddChild(HistoryDataBase->RootNode); // ��������� � ��������� ����

		//��������� ������ ����
		NodeStruct *nodeData = (NodeStruct*)HistoryDataBase->GetNodeData(entryNode);   //�������� ��������� �� ������
		nodeData->Id = i;
		nodeData->Url = (wchar_t*)sqlite3_column_text16(pStatement, 0) + UnicodeString(i);                 //��������� ���������
		nodeData->Title = (wchar_t*)sqlite3_column_text16(pStatement, 1) + UnicodeString(i);
		nodeData->LastVisit = sqlite3_column_int64(pStatement, 2);

	}
	sqlite3_finalize(pStatement);

	if(stepResult != SQLITE_DONE)
    {
        wcout << L"������ ���������� �������!" << endl;
    }

	//�������� ���������� ����������
	HistoryDataBase->EndUpdate();
}

//---------------------------------------------------------------------------

// ��������� ������� ��� ������ ������ FillStringTree �� ������
void __fastcall TMainForm::FillNodeClick(TObject *Sender)
{
	//������ ������ ���������� ��� �����������
	DeleteStrock->Enabled = true;
    DeleteDataBase->Enabled = true;
	FillStringTree(HistoryDataBase);
}


//---------------------------------------------------------------------------

void __fastcall TMainForm::HistoryDataBaseGetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVstTextType TextType, UnicodeString &CellText)

{
	if (!Node) return;

	NodeStruct *nodeData = (NodeStruct*)Sender->GetNodeData(Node);
	switch(Column)
	{
		 case 0: CellText = nodeData->Id; break;
		 case 1: CellText = nodeData->Url; break;
		 case 2: CellText = nodeData->Title; break;
    }

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::HistoryDataBaseAddToSelection(TBaseVirtualTree *Sender,
          PVirtualNode Node)
{
	if(!Node) return;
	NodeStruct *nodeData = (NodeStruct*)Sender->GetNodeData(Node);
    InfoLabel->Caption = nodeData->LastVisit;
}
//---------------------------------------------------------------------------
void TMainForm::DeleteEntryFromDatabase(uint64_t id)
{

	sqlite3_stmt *pStatement;
	const char *sql = "DELETE FROM urls WHERE id = ?";

	if (sqlite3_prepare_v2(DataBase, sql, -1, &pStatement, NULL) == SQLITE_OK)
    {
		sqlite3_bind_int(pStatement, 1, id);

		if (sqlite3_step(pStatement) != SQLITE_DONE)
        {
            Application->MessageBox(L"������ �������� ������ �� ���� ������!", L"������", MB_OK);
        }
    }
    else
    {
        Application->MessageBox(L"������ ���������� ������� ��� �������� ������!", L"������", MB_OK);
    }

	sqlite3_finalize(pStatement);
}

void __fastcall TMainForm::DeleteStrockClick(TObject *Sender)
{
    PVirtualNode selectedNode = HistoryDataBase->FocusedNode;
    if (!selectedNode) return;

    NodeStruct *nodeData = (NodeStruct*)HistoryDataBase->GetNodeData(selectedNode);
    if (!nodeData) return;

    DeleteEntryFromDatabase(nodeData->Id);
	HistoryDataBase->DeleteNode(selectedNode);
}
//---------------------------------------------------------------------------

// ����� ��� �������� ������� ������� ��������
void TMainForm::DeleteHistoryTable()
{
    const char *sql = "DROP TABLE IF EXISTS urls"; // SQL-������ �� �������� �������

    char *errorMessage;
    int result = sqlite3_exec(DataBase, sql, NULL, 0, &errorMessage); // ��������� ������

	if (result != SQLITE_OK)       //������
	{
		Application->MessageBox(L"������ �������� ������� ������� ��������", L"������", MB_OK);
		sqlite3_free(errorMessage);
    }
    else
    {
		Application->MessageBox(L"������� ������� �������� ������� �������", L"�����", MB_OK | MB_ICONINFORMATION);
	}

}
//---------------------------------------------------------------------------
	// �������� ����� ��� �������� �������
 void __fastcall TMainForm::DeleteDataBaseClick(TObject *Sender)
{
	DeleteHistoryTable();   		 //����� �������� ��
	FillStringTree(HistoryDataBase); // ����� ���������� ��������, ����� ������� ������� ����� ������

}
//---------------------------------------------------------------------------

// ������ � ����������
void __fastcall TMainForm::TutorialChange(TObject *Sender)
{
	Tutorial->Lines->Clear();
	Tutorial->SelAttributes->Style = TFontStyles() << fsBold;
    Tutorial->Lines->Add("������ ���������� �������� � ����� ������, ��� ������������� ���. ������ *.cpp/*.h");
    Tutorial->SelAttributes->Style = TFontStyles() << fsBold;
	Tutorial->Lines->Add("����������� � ����������!");
	Tutorial->SelAttributes->Style = TFontStyles();
	Tutorial->Lines->Add("��� �������� � ���� �����������?");
	Tutorial->Lines->Add("1. ������� ������ <������� ��> � �������� ����������� ����");
	Tutorial->Lines->Add("2. �����, �������� ��������� ���������, ����� ������������ ���������� �����.");
	Tutorial->Lines->Add("3. ����������� ������ <������� ������> � <������� ������� ��> ��� �������������� ������� ��������.");
	Tutorial->Lines->Add("");
	Tutorial->SelAttributes->Style = TFontStyles() << fsItalic;
	Tutorial->Lines->Add("������� �� ������������� ������� ����������!");
    Tutorial->ReadOnly = true;
}
//---------------------------------------------------------------------------

