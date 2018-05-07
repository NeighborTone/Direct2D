#pragma once
#include "System.h"
#include "Direct2D.h"


//メインループ処理を行う
class Mainloop final
{
private:
	MSG msg;
	System window;
	Direct2D d2d;

	
	ID2D1SolidColorBrush* pGreenBrush = NULL;
	IDWriteFactory* pWriteFact = nullptr;
	IDWriteTextFormat* pFormat=nullptr;

public:
	Mainloop() {};
	~Mainloop() {};
	bool Init(HINSTANCE hInstance, int nCmdShow);
	void Run();
};