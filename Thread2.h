//---------------------------------------------------------------------------

#ifndef Thread2H
#define Thread2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class Thread2 : public TThread
{
private:
	DWORD processTime;
	bool allCats;
    bool niceCats;
	int Quantity;
	float ratio;
	int i;
protected:
	void __fastcall Execute();
	//Добавить кошек
	void __fastcall AddAllCats();
	//Обновить прогресс
	void __fastcall UpdateProgressThread();
	// Обновить таблицу после добавления всех кошек
	void __fastcall UpdateTableAfterAddCats();
    // Очистка контейнера
	void __fastcall ClearCatContainer();
    // Обновление табеля времени
	void __fastcall UpdateLabel();
	void __fastcall NiceEmotion();
public:
	__fastcall Thread2(bool CreateSuspended, bool allcats, bool nicecats);
};
//---------------------------------------------------------------------------
#endif
