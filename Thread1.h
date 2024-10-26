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
	TVirtualStringTree *HistoryDataBase;                  		// Кнопка открытия БД
	TRichEdit *WritePlease;                 // Поле для редактирования
	TCheckBox *CheckProv1;                  // Проверка 1
	TCheckBox *CheckProv2;                  // Проверка 2
	TButton *ThreadButton1;                 // Кнопка запуска потока №1
	TProgressBar *ProgressBarThread;        // Прогресс работы потока(потоков)
	TLabel *ThreadWorkLabel;                // Поле вывода время работы потока(потоков)
	TOpenDialog *OpenError;
	TButton *ThreadButton2;
	TButton *NoGraphicsButton;
	// получить текст в таблице
	void __fastcall HistoryDataBaseGetText(TBaseVirtualTree *Sender, PVirtualNode Node,
		  TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText);
    // редактор
	void __fastcall WritePleaseClick(TObject *Sender);
	// 1 кнопка без потока отвечающий за "интерактив"
	void __fastcall NoGraphicsButtonClick(TObject *Sender);
	// 2 кнопка
	void __fastcall ThreadButton1Click(TObject *Sender);
	void __fastcall ThreadButton2Click(TObject *Sender);
private:	// User declarations
	// Деструткор  удаление итератора
	~TMainForm() { delete it; }

public:		// User declarations
	// указатель на итератор
	Iterator<CatPtr> *it;
	// Добавить кошку
	void AddCatsContainer();
	void ClearContainer();
	void DecoratorNice();
	Iterator<CatPtr> * GetIterator();
	__fastcall TMainForm(TComponent* Owner);
    // мегаконтейнер из Shelter.h
	MegaCatContainer container;
	// указатель на поток2
	Thread2 *th;
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
// Заполнить таблицу
void FillStringTree(TVirtualStringTree *HistoryDataBase, Iterator<CatPtr> *it);   //метод заполнения таблицы
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
