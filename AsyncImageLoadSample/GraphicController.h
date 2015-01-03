#pragma once

#include <iostream>
#include <map>
#include <future>

#include "GraphicMemData.h"

class GraphicController
{
public:
	GraphicController();
	~GraphicController();

	void AddLoadImageData(std::string tag, std::string filePath);
	void RemoveImageData(std::string tag);
	void LoadImageData();
	void CreateImageHandle();
	int GetImageHandle(std::string tag);
	bool IsRunning();
	bool IsCreated();

private:
	std::map<std::string, std::string> mImageDataMap;
	std::future<std::map<std::string, GraphicMemData *>> mLoadFuture;
	std::map<std::string, int> mImageHandleMap;
	bool mIsCreated;
};

