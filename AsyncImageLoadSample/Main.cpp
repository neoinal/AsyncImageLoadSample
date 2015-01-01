#include <iostream>
#include <map>

// メモリリーク確認用 ここから
#include "crtdbg.h"
#define malloc(X) _malloc_dbg(X,_NORMAL_BLOCK,__FILE__,__LINE__)
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
// メモリリーク確認用 ここまで

#include "DxLib.h"

#include "GraphicController.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// メモリリーク確認用 ここから
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_DELAY_FREE_MEM_DF | _CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_LEAK_CHECK_DF);
	// メモリリーク確認用 ここまで

	// ウィンドウタイトルの変更
	SetMainWindowText("AsyncImageLoadSample");
	// ウィンドウモード
	ChangeWindowMode(TRUE);
	// ウィンドウサイズを1280x720の32bitカラー
	SetGraphMode(1280, 720, 32);
	// DXライブラリの初期化処理
	DxLib_Init();

	// 画像読み込み用MAPの作成
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

	// DXライブラリの終了処理
	DxLib_End();
	return 0;
}
