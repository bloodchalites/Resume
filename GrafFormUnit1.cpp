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
	HistoryDataBase->NodeDataSize = sizeof(NodeStruct); // прописываем для таблицы размер одной записи
														// чтобы выделялось необходимое кол-во памяти для узлов

	//Делает кнопки не доступными для пользования, пока не откроют БД
	FillNode->Enabled = false;
	DeleteStrock->Enabled = false;
    DeleteDataBase->Enabled = false;
}
//--------------------------------------------------------------------------

// метод открытия БД
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

//Открытие БД при нажатии и последующая проверка

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

		FileNameEdit->Text = fileName.c_str();     //отображение пути файла в вводимом окне
		InfoLabel->Caption = fileName.c_str();     //отображение пути файла в невводимом окне

		FillNode->Enabled = true;         		   //Делает кнопки доступными для пользования
		// Проверка допустимых расширений
		const vector<wstring> Proverka = {L".sqlite", L".db"};  // расширения БД

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

		if(isProverka)        //  ошибки
        {
			if(!OpenDataBase(fileName.c_str()))
            {
                Application->MessageBox(L"Ошибка открытия базы данных!", L"Ошибка", MB_OK);
            }
        }
        else
		{
			// Два варианта вывода ошибки
			MessageDlg(L"Неправильный формат файла! Пожалуйста, выберите файл базы данных Chromium.", mtWarning, TMsgDlgButtons() << mbOK, 0);
			//Application->MessageBox(L"Неправильный формат файла! Пожалуйста, выберите файл базы данных Chromium.", L"Ошибка", MB_OK);
		}
    }
}

//Заполнить данными буфер
void TMainForm::FillStringTree(TVirtualStringTree *HistoryDataBase)
{
	HistoryDataBase->BeginUpdate();

	//очистить дерево
	HistoryDataBase->Clear();

	// Стандартное использование SQLite в одном классе
	sqlite3_stmt *pStatement;

    int execResult1 = sqlite3_prepare16_v2(DataBase,
										 L"SELECT url, title, last_visit_time FROM urls",
                                         -1, //здесь можно написать длину второго параметра
										 &pStatement, NULL);
    if(execResult1 != SQLITE_OK)
    {
        wcout << "Ошибка подготовки запроса!" << endl;
        const char *errmsg2 = sqlite3_errmsg(DataBase);
		cout << errmsg2 << endl;
	}
	int stepResult = SQLITE_DONE; // то значение которое должно получиться если все хорошо и запрос закончился

	for(ULONGLONG i=0; i<1000; i++)
	{
		int stepResult = sqlite3_step(pStatement);
		if(stepResult != SQLITE_ROW)
		{
			break;
		}
		  //Добавляем запись
		PVirtualNode entryNode = HistoryDataBase->AddChild(HistoryDataBase->RootNode); // добавлять к корневому узлу

		//заполняем данные узла
		NodeStruct *nodeData = (NodeStruct*)HistoryDataBase->GetNodeData(entryNode);   //получили указатель на данные
		nodeData->Id = i;
		nodeData->Url = (wchar_t*)sqlite3_column_text16(pStatement, 0) + UnicodeString(i);                 //заполнили структуру
		nodeData->Title = (wchar_t*)sqlite3_column_text16(pStatement, 1) + UnicodeString(i);
		nodeData->LastVisit = sqlite3_column_int64(pStatement, 2);

	}
	sqlite3_finalize(pStatement);

	if(stepResult != SQLITE_DONE)
    {
        wcout << L"Ошибка выполнения запроса!" << endl;
    }

	//Включаем обновление интерфейса
	HistoryDataBase->EndUpdate();
}

//---------------------------------------------------------------------------

// Заполняем таблицу при помощи метода FillStringTree по кнопке
void __fastcall TMainForm::FillNodeClick(TObject *Sender)
{
	//Делает кнопки доступными для пользования
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
            Application->MessageBox(L"Ошибка удаления записи из базы данных!", L"Ошибка", MB_OK);
        }
    }
    else
    {
        Application->MessageBox(L"Ошибка подготовки запроса для удаления записи!", L"Ошибка", MB_OK);
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

// Метод для удаления таблицы истории браузера
void TMainForm::DeleteHistoryTable()
{
    const char *sql = "DROP TABLE IF EXISTS urls"; // SQL-запрос на удаление таблицы

    char *errorMessage;
    int result = sqlite3_exec(DataBase, sql, NULL, 0, &errorMessage); // Выполняем запрос

	if (result != SQLITE_OK)       //Ошибки
	{
		Application->MessageBox(L"Ошибка удаления таблицы истории браузера", L"Ошибка", MB_OK);
		sqlite3_free(errorMessage);
    }
    else
    {
		Application->MessageBox(L"Таблица истории браузера успешно удалена", L"Успех", MB_OK | MB_ICONINFORMATION);
	}

}
//---------------------------------------------------------------------------
	// Вызываем метод для удаления таблицы
 void __fastcall TMainForm::DeleteDataBaseClick(TObject *Sender)
{
	DeleteHistoryTable();   		 //метод удаления БД
	FillStringTree(HistoryDataBase); // метод заполнения структур, чтобы сделать таблицу снова пустой

}
//---------------------------------------------------------------------------

// панель с туториалом
void __fastcall TMainForm::TutorialChange(TObject *Sender)
{
	Tutorial->Lines->Clear();
	Tutorial->SelAttributes->Style = TFontStyles() << fsBold;
    Tutorial->Lines->Add("Данное приложение написано в одном классе, без использования доп. файлов *.cpp/*.h");
    Tutorial->SelAttributes->Style = TFontStyles() << fsBold;
	Tutorial->Lines->Add("Приветствую в приложении!");
	Tutorial->SelAttributes->Style = TFontStyles();
	Tutorial->Lines->Add("Как работать с этим приложением?");
	Tutorial->Lines->Add("1. Нажмите кнопку <Открыть БД> и выберите необходимый файл");
	Tutorial->Lines->Add("2. После, кликните заполнить структуры, чтобы отобразилось содержимое файла.");
	Tutorial->Lines->Add("3. Используете кнопки <Удалить строку> и <Удалить историю БД> для редактирования истории браузера.");
	Tutorial->Lines->Add("");
	Tutorial->SelAttributes->Style = TFontStyles() << fsItalic;
	Tutorial->Lines->Add("Спасибо за использование данного приложения!");
    Tutorial->ReadOnly = true;
}
//---------------------------------------------------------------------------

