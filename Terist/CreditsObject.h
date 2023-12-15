#pragma once

#include "Base.h"
#include "TextObject.h"

class CreditsObject : public BaseObject
{
public:
	CreditsObject();
	~CreditsObject();

	void InitTextContent(SDL_Renderer*, TTF_Font*, TextObject&, const string&, const int&);
	void LoadCredits(SDL_Renderer*, SDL_Event&, TTF_Font*, TTF_Font*, bool&, bool&);
};