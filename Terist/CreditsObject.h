#pragma once

#include "Base.h"
#include "TextObject.h"

class CreditsObject : public BaseObject
{
public:
	CreditsObject();
	~CreditsObject();

	void InitTextContent(SDL_Renderer*, TTF_Font*, TextObject&, const string&, const int&); // Render noi dung cua chu trong Credits
	void LoadCredits(SDL_Renderer*, SDL_Event&, TTF_Font*, TTF_Font*, bool&, bool&); // Thuc hien hien thi phan Credits len man hinh chinh
};