#ifndef RESOURCEHOLDER_H_INCLUDE
#define RESOURCEHOLDER_H_INCLUDE
#include "utility/NonCopyable.h"
#include "utility/NonMovable.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "AudioManager.h"

class ResourceHolder : public NonCopyable, public NonMovable
{
public:
	static ResourceHolder& get();

	TextureManager textures;
	FontManager fonts;
	AudioManager audio;

private:
	ResourceHolder();
};

#endif	/*	end RESOURCEHOLDER_H_INCLUDE	*/