#include <iostream>
#include <map>

// ���������[�N�m�F�p ��������
#include "crtdbg.h"
#define malloc(X) _malloc_dbg(X,_NORMAL_BLOCK,__FILE__,__LINE__)
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
// ���������[�N�m�F�p �����܂�

#include "DxLib.h"

#include "GraphicController.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ���������[�N�m�F�p ��������
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_DELAY_FREE_MEM_DF | _CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_LEAK_CHECK_DF);
	// ���������[�N�m�F�p �����܂�

	// �E�B���h�E�^�C�g���̕ύX
	SetMainWindowText("AsyncImageLoadSample");
	// �E�B���h�E���[�h
	ChangeWindowMode(TRUE);
	// �E�B���h�E�T�C�Y��1280x720��32bit�J���[
	SetGraphMode(1280, 720, 32);
	// DX���C�u�����̏���������
	DxLib_Init();

	// �摜�ǂݍ��ݗpMAP�̍쐬
	std::map<std::string, std::string> loadImageMap;
	loadImageMap["TEST1"] = "img/test1.jpg";
	loadImageMap["TEST2"] = "img/test2.jpg";
	loadImageMap["TEST3"] = "img/test3.jpg";

	GraphicController graphicController;
	graphicController.LoadImageData(loadImageMap);

	int imageHandle;
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{
		if (!graphicController.IsCreated())
		{
			DrawString(0, 0, "Loading...", GetColor(GetNowCount() % 255, 255, 255));
			if (graphicController.IsRunning())
			{
				continue;
			}
			graphicController.CreateImageHandle();
			imageHandle = graphicController.GetImageHandle("TEST1");
		}
		else
		{
			if (CheckHitKey(KEY_INPUT_A) == 1)
				imageHandle = graphicController.GetImageHandle("TEST1");
			else if (CheckHitKey(KEY_INPUT_S) == 1)
				imageHandle = graphicController.GetImageHandle("TEST2");
			else if (CheckHitKey(KEY_INPUT_D) == 1)
				imageHandle = graphicController.GetImageHandle("TEST3");

			DrawGraph(0, 0, imageHandle, TRUE);
		}
	}

	// DX���C�u�����̏I������
	DxLib_End();
	return 0;
}
