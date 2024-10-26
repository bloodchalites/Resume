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
	//�������� �����
	void __fastcall AddAllCats();
	//�������� ��������
	void __fastcall UpdateProgressThread();
	// �������� ������� ����� ���������� ���� �����
	void __fastcall UpdateTableAfterAddCats();
    // ������� ����������
	void __fastcall ClearCatContainer();
    // ���������� ������ �������
	void __fastcall UpdateLabel();
	void __fastcall NiceEmotion();
public:
	__fastcall Thread2(bool CreateSuspended, bool allcats, bool nicecats);
};
//---------------------------------------------------------------------------
#endif
