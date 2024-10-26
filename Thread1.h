//---------------------------------------------------------------------------

#ifndef Thread1H
#define Thread1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VirtualTrees.AncestorVCL.hpp"
#include "VirtualTrees.BaseAncestorVCL.hpp"
#include "VirtualTrees.BaseTree.hpp"
#include "VirtualTrees.hpp"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "Thread2.h"
#include "Shelter.h"
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TVirtualStringTree *HistoryDataBase;                  		// ������ �������� ��
	TRichEdit *WritePlease;                 // ���� ��� ��������������
	TCheckBox *CheckProv1;                  // �������� 1
	TCheckBox *CheckProv2;                  // �������� 2
	TButton *ThreadButton1;                 // ������ ������� ������ �1
	TProgressBar *ProgressBarThread;        // �������� ������ ������(�������)
	TLabel *ThreadWorkLabel;                // ���� ������ ����� ������ ������(�������)
	TOpenDialog *OpenError;
	TButton *ThreadButton2;
	TButton *NoGraphicsButton;
	// �������� ����� � �������
	void __fastcall HistoryDataBaseGetText(TBaseVirtualTree *Sender, PVirtualNode Node,
		  TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText);
    // ��������
	void __fastcall WritePleaseClick(TObject *Sender);
	// 1 ������ ��� ������ ���������� �� "����������"
	void __fastcall NoGraphicsButtonClick(TObject *Sender);
	// 2 ������
	void __fastcall ThreadButton1Click(TObject *Sender);
	void __fastcall ThreadButton2Click(TObject *Sender);
private:	// User declarations
	// ����������  �������� ���������
	~TMainForm() { delete it; }

public:		// User declarations
	// ��������� �� ��������
	Iterator<CatPtr> *it;
	// �������� �����
	void AddCatsContainer();
	void ClearContainer();
	void DecoratorNice();
	Iterator<CatPtr> * GetIterator();
	__fastcall TMainForm(TComponent* Owner);
    // ������������� �� Shelter.h
	MegaCatContainer container;
	// ��������� �� �����2
	Thread2 *th;
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
// ��������� �������
void FillStringTree(TVirtualStringTree *HistoryDataBase, Iterator<CatPtr> *it);   //����� ���������� �������
//---------------------------------------------------------------------------
typedef struct
{
	ULONGLONG Id;
	UnicodeString Origin;
	UnicodeString Color;
	UnicodeString Mood;
    UnicodeString Type;
} NodeStruct;

#endif
