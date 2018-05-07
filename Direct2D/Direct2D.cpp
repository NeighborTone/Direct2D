#include "Direct2D.h"
#include "SystemDefs.h"

Direct2D::Direct2D()
{
	pFactory = nullptr;
	pTarget = nullptr;
}

Direct2D::~Direct2D()
{
	Memory::SafeRelease(pFactory);
	Memory::SafeRelease(pTarget);
}

bool Direct2D::Create(HWND hwnd)
{
	HRESULT hr;

	if (pFactory == nullptr)
	{
		//�t�@�N�g���̍쐬
		hr = ::D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
		if (FAILED(hr))
		{
			MessageBox(NULL, "D2D�t�@�N�g���[�̍쐬�Ɏ��s���܂���", "Error", MB_OK);
			return false;
		}
	
	}

	//�����_�����O�^�[�Q�b�g�i�`��Ώۂ̍쐬�j
	if (pTarget == nullptr)
	{
		RECT rect;
		::GetClientRect(hwnd, &rect);
		D2D1_SIZE_U size = D2D1::Size<UINT>(rect.right,rect.bottom);

		hr = pFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hwnd, size),
			&pTarget);

		if (FAILED(hr))
		{
			MessageBox(NULL, "�����_�����O�^�[�Q�b�g�̍쐬�Ɏ��s���܂���", "Error", MB_OK);
			return false;
		}
	}
	return true;
}

void Direct2D::Begine()
{
	//�E�B���h�E�����̃E�B���h�E�ɕ����Ă�����`�揈�������Ȃ�
	if (pTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED)
	{
		return;
	}
	//---------�`��J�n--------
	pTarget->BeginDraw();

	//�w�i�N���A 
	pTarget->Clear(D2D1::ColorF(0, 0, 0));

}

void Direct2D::End()
{
	pTarget->EndDraw();
}

ID2D1Factory * Direct2D::GetFactory()
{
	return pFactory;
}

ID2D1HwndRenderTarget * Direct2D::GetTarget()
{
	return pTarget;
}
