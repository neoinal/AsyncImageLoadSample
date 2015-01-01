#include "GraphicMemData.h"


GraphicMemData::GraphicMemData(unsigned char *imageData, int imageSize)
	: mImageData(imageData), mImageSize(imageSize)
{
}


GraphicMemData::~GraphicMemData()
{
	delete mImageData;
}

unsigned char *GraphicMemData::GetImageData()
{
	return mImageData;
}

int GraphicMemData::GetImageSize()
{
	return mImageSize;
}