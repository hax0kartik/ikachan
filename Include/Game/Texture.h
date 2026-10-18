#pragma once
#include "types.h"
#include <nn/gr/CTR/gr_Texture.h>
#include <vector>

class Texture {
public:
	Texture();
	virtual ~Texture();
	virtual int Load(const char *filename);
	virtual int Unload();
	virtual int GetTexWidth() = 0;
	virtual int GetTexHeight() = 0;
	virtual int IsRGB() = 0;

protected:
	int width;
	int height;
	int field_C;
	nn::gr::CTR::Texture texture;

public:
	float uvScaleX;
	float uvScaleY;
	bool loaded;
	bool queuedForDraw;
	char *filename;
	int refCount;
	std::vector<void *> batch;
};
