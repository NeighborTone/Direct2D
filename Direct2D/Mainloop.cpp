#include "Mainloop.h"
#include "SystemDefs.h"

 
bool Mainloop::Init(HINSTANCE hInstance, int nCmdShow)
{
	//�E�B���h�E����
	const bool iswin = 	window.Create("test2D",hInstance, nCmdShow);
	
	//�E�B���h�E�`��
	const bool isshow = ShowWindow(window.GetWindow(), nCmdShow);
	if (iswin  && isshow && d2d.Create(window.GetWindow()))
	{
		//�e�L�X�g�t�@�N�g���[�̏�����
		DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(pWriteFact),
			reinterpret_cast<IUnknown **>(&pWriteFact));
		pWriteFact->CreateTextFormat(
			L"hogehoge",
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,		
			16.f,										//�t�H���g�T�C�Y
			L"",
			&pFormat);
		pFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		pFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		

		//�u���V�̐F�ݒ�
		d2d.GetTarget()->CreateSolidColorBrush(
			D2D1::ColorF(1.0F, 1.0F, 0.0F), &pGreenBrush);
		return true;
	}

	return false;
}


void Mainloop::Run()
{
	//���b�Z�[�W���擾
	GetMessage(&msg, NULL, 0, 0);
	//���b�Z�[�W���[�v(���͂Ȃǂ̖��߂�ǂ�)
	while (msg.message != WM_QUIT)
	{
	
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//���b�Z�[�W���f�R�[�h����WinProc�ɓn��
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
		
			d2d.Begine();
		

			//�e�L�X�g
			D2D1_SIZE_F size = d2d.GetTarget()->GetSize();
			d2d.GetTarget()->DrawTextA(
				L"hogehoge",
				ARRAYSIZE(L"hogehoge") - 1,
				pFormat,
				D2D1::RectF(0, 0, size.width, size.height),
				pGreenBrush);

			//�����Ŏl�p�`�o������
			static float x=50, y=50, w=100, h=100;
			//�l�p
			D2D1_RECT_F rect1 =
			D2D1::RectF(x, y, w + x, h + y);
			d2d.GetTarget()->FillRectangle(&rect1, pGreenBrush);

			//�ȉ~
			D2D1_ELLIPSE ellipse1 =
			D2D1::Ellipse(D2D1::Point2F(150, 150.f), 50.0F, 50.0F);

			d2d.GetTarget()->FillEllipse(ellipse1, pGreenBrush);

			d2d.End();
		}

	//	ShowCursor(false);	//�}�E�X��\��
	
	}
	pGreenBrush->Release();
	
	pFormat->Release();
	pWriteFact->Release();

}
