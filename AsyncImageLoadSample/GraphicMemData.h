#pragma once

class GraphicMemData
{
public:
	GraphicMemData(unsigned char *imageData, int imageSize);
	~GraphicMemData();

	unsigned char *GetImageData();
	int GetImageSize();

private:
	unsigned char *mImageData;
	int mImageSize;
};

