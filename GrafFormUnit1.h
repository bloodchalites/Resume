//---------------------------------------------------------------------------
#ifndef GrafFormUnit1H
#define GrafFormUnit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VirtualTrees.AncestorVCL.hpp"
#include "VirtualTrees.BaseAncestorVCL.hpp"
#include "VirtualTrees.BaseTree.hpp"
#include "VirtualTrees.hpp"
#include <Vcl.Dialogs.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *InfoLabel;                     // ���������� ���� � �����������
	TButton *OpenDB;                       // ������� ���� ��
	TOpenDialog *OpenDataBaseDialog;       //���������� ����
	TVirtualStringTree *HistoryDataBase;   // ������� ��
	TButton *DeleteStrock;     // ������� ������ �������
	TButton *DeleteDataBase;   // ������� ��� ��
	TEdit *FileNameEdit;   	   // �������� ����
	TButton *FillNode;
	TRichEdit *Tutorial;    	   //��������� ��������� ��

	void __fastcall OpenDBClick(TObject *Sender);    // ����� ������� ��� �������
	void __fastcall FillNodeClick(TObject *Sender);  // ����� ��������� ��� �������
	void __fastcall HistoryDataBaseGetText(TBaseVirtualTree *Sender, PVirtualNode Node,   // ����� ��������� �������
          TColumnIndex Column, TVstTextType TextType, UnicodeString &CellText);
	void __fastcall HistoryDataBaseAddToSelection(TBaseVirtualTree *Sender, PVirtualNode Node);
	void __fastcall DeleteStrockClick(TObject *Sender);         // ����� ������� �������
	void __fastcall TutorialChange(TObject *Sender);
	void __fastcall DeleteDataBaseClick(TObject *Sender);            // ����� ��������


private:	// User declarations
	sqlite3* DataBase;

    void FillStringTree(TVirtualStringTree *HistoryDataBase);
	bool OpenDataBase(const WCHAR *fileName);
	void DeleteEntryFromDatabase(uint64_t id);
	void DeleteHistoryTable();

public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
};

//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//��������� �������
typedef struct
{
	ULONGLONG Id;
	UnicodeString Url;
	UnicodeString Title;
	LONGLONG LastVisit;
} NodeStruct;

//---------------------------------------------------------------------------
#endif
