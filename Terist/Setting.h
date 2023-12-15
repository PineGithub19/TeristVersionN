#pragma once

#include "Base.h"
#include "TextObject.h"
#include "CreditsObject.h"

class Setting : public CreditsObject
{
public:
	Setting();
	~Setting();

	void LoadSetting(SDL_Renderer*, SDL_Event&, TTF_Font*, TTF_Font*, bool&, bool&, Mix_Music*&);
};