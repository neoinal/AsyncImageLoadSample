#include "DxLib.h"

#include "GraphicController.h"

GraphicController::GraphicController()
{
}


GraphicController::~GraphicController()
{
}

/* 
 * 非同期に画像ファイルをロードする
 */
void GraphicController::LoadImageData(std::map<std::string, std::string> loadImageMap)
{
	mIsCreated = false;
	// 非同期に画像ファイルをメモリ上にロードする
	mLoadFuture = std::async(std::launch::async, [](std::map<std::string, std::string> imageMap)
	{
		std::map<std::string, GraphicMemData *> imageDataMap;
		for (std::map<std::string, std::string>::iterator itr = imageMap.begin(); itr != imageMap.end(); ++itr)
		{
			const char *filePath = itr->second.c_str();
			int fileSize = FileRead_size(filePath);
			int fileHandle = FileRead_open(filePath);
			unsigned char *buf = new unsigned char[fileSize];
			FileRead_read(buf, fileSize, fileHandle);
			FileRead_close(fileHandle);

			imageDataMap[itr->first] = new GraphicMemData(buf, fileSize);
		}
		// 確認用のスリープ
		Sleep(5000);
		return imageDataMap;
	}, loadImageMap);
}

/* 
 * イメージハンドラの作成
 */
void GraphicController::CreateImageHandle()
{
	std::map<std::string, GraphicMemData *> imageDataMap = mLoadFuture.get();
	std::map<std::string, GraphicMemData *>::iterator itr = imageDataMap.begin();
	while (itr != imageDataMap.end())
	{
		GraphicMemData *graphicData = itr->second;
		int imageHandle = CreateGraphFromMem(graphicData->GetImageData(), graphicData->GetImageSize());
		mImageHandleMap[itr->first] = imageHandle;

		delete graphicData;
		imageDataMap.erase(itr++);
	}
	for (std::map<std::string, GraphicMemData *>::iterator itr = imageDataMap.begin(); itr != imageDataMap.end(); ++itr)
	{
		GraphicMemData *graphicData = itr->second;
		int imageHandle = CreateGraphFromMem(graphicData->GetImageData(), graphicData->GetImageSize());
		delete graphicData;
		mImageHandleMap[itr->first] = imageHandle;
	}
	mIsCreated = true;
}

/*
 * タグに対応したイメージハンドラを返す
 * 但し、タグが存在しない場合は -1 を返す
 */
int GraphicController::GetImageHandle(std::string tag)
{
	if (mImageHandleMap.count(tag) == 0)
	{
		return -1;
	}
	else
	{
		return mImageHandleMap.find(tag)->second;
	}
}

bool GraphicController::IsRunning()
{
	return (mLoadFuture.wait_for(std::chrono::seconds(0)) != std::future_status::ready);
}

bool GraphicController::IsCreated()
{
	return mIsCreated;
}