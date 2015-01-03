#include "DxLib.h"

#include "GraphicController.h"

GraphicController::GraphicController()
{
}


GraphicController::~GraphicController()
{
	std::map<std::string, int>::iterator itr = mImageHandleMap.begin();
	while (itr != mImageHandleMap.end())
	{
		DeleteGraph(itr->second);
		mImageHandleMap.erase(itr++);
	}
}

void GraphicController::AddLoadImageData(std::string tag, std::string filePath)
{
	mImageDataMap[tag] = filePath;
}

void GraphicController::RemoveImageData(std::string tag)
{
	if (mImageHandleMap.count(tag) == 1)
	{
		std::map<std::string, int>::iterator itr = mImageHandleMap.find(tag);
		DeleteGraph(itr->second);
		mImageHandleMap.erase(itr);
	}
	mImageHandleMap.erase(tag);
}

/* 
 * �񓯊��ɉ摜�t�@�C�������[�h����
 */
void GraphicController::LoadImageData()
{
	mIsCreated = false;
	// �񓯊��ɉ摜�t�@�C������������Ƀ��[�h����
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
		// �m�F�p�̃X���[�v
		Sleep(5000);
		return imageDataMap;
	}, mImageDataMap);
}

/* 
 * �C���[�W�n���h���̍쐬
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
 * �^�O�ɑΉ������C���[�W�n���h����Ԃ�
 * �A���A�^�O�����݂��Ȃ��ꍇ�� -1 ��Ԃ�
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