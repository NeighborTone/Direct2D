#pragma once
#pragma warning(disable : 4005)
#include <D2D1.h>
#include <Dwrite.h>
#pragma comment(lib, "d2d1")
#pragma comment(lib, "Dwrite")

class Direct2D
{
private:
	ID2D1Factory*				  pFactory;
	ID2D1HwndRenderTarget* pTarget;

public:
	Direct2D();
	~Direct2D();
	bool Create(HWND hwnd);
	void Begine();
	void End();
	ID2D1Factory* GetFactory();
	ID2D1HwndRenderTarget* GetTarget();
};

