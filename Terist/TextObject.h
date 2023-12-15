#pragma once

#include "Base.h"


class TextObject : public BaseObject
{
public:
	TextObject();
	~TextObject();

	enum TextColor
	{
		RED_TEXT = 0,
		WHITE_TEXT = 1,
		BLACK_TEXT = 2,
		YELLOW_TEXT = 3,
	};

	bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
	void Free_Text();

	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	void SetColor(int type);

	void RenderText(SDL_Renderer* screen,
		int x_pos, int y_pos,
		SDL_Rect* clip = NULL,
		double angle = 0.0,
		SDL_Point* center = NULL,
		SDL_RendererFlip flip = SDL_FLIP_NONE);
	int Get_Width() const { return width_; }
	int Get_Height() const { return height_; }

	void Set_Rect(const int& xPos, const int& yPos) {
		x_pos_ = xPos;
		y_pos_ = yPos;
	}
	SDL_Rect Get_Rect() const {
		SDL_Rect rect;
		rect.x = x_pos_;
		rect.y = y_pos_;
		rect.w = width_;
		rect.h = height_;
		return rect;
	}

	void Set_Text(const std::string& text) { text_string_ = text; }
	std::string Get_Text() const { return text_string_; }
private:
	std::string text_string_;
	SDL_Color text_color_;
	SDL_Texture* text_textture_;
	int width_, height_;
	int x_pos_, y_pos_;
};
