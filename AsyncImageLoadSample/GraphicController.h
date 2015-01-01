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

	void LoadImageData(std::map<std::string, std::string> loadImageMap);
	void CreateImageHandle();
	int GetImageHandle(std::string tag);
	bool IsRunning();
	bool IsCreated();

private:
	std::future<std::map<std::string, GraphicMemData *>> mLoadFuture;
	std::map<std::string, int> mImageHandleMap;
	bool mIsCreated;
};

