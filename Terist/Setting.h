#pragma once

#include "Base.h"
#include "TextObject.h"
#include "CreditsObject.h"

class Setting : public CreditsObject
{
private:
	int volumn;
public:
	Setting();
	~Setting();

	void setVolumn(const int&);
	int getVolumn() const;

	void LoadSetting(SDL_Renderer*, SDL_Event&, TTF_Font*, TTF_Font*, bool&, bool&, Mix_Music*&); // dieu chinh setting, bao gom tang, giam, tat, mo am thanh
};