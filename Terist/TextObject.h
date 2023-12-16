#pragma once

#include "Base.h"


class TextObject : public BaseObject
{
public:
	TextObject();
	~TextObject();

	enum TextColor // cac loai mau chu
	{
		RED_TEXT = 0,
		WHITE_TEXT = 1,
		BLACK_TEXT = 2,
		YELLOW_TEXT = 3,
	};

	bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen); // dua text len man hinh nhung chua render
	void Free_Text(); // Xoa text

	void SetColor(Uint8 red, Uint8 green, Uint8 blue); // Chinh mau chu theo (r, g, b)
	void SetColor(int type); // chinh mau chu theo mau co san trong enum

	void RenderText(SDL_Renderer* screen,
		int x_pos, int y_pos,
		SDL_Rect* clip = NULL,
		double angle = 0.0,
		SDL_Point* center = NULL,
		SDL_RendererFlip flip = SDL_FLIP_NONE); // Hien thi text ra man hinh (render)
	int Get_Width() const { return width_; } // lay chieu rong cua dong chu
	int Get_Height() const { return height_; } // lay chieu dai cua dong chu

	void Set_Rect(const int& xPos, const int& yPos) { // Set toa do cua chu (x, y)
		x_pos_ = xPos;
		y_pos_ = yPos;
	}
	SDL_Rect Get_Rect() const { // Lay ra toa do x, y, chieu rong w, chieu cao h
		SDL_Rect rect;
		rect.x = x_pos_;
		rect.y = y_pos_;
		rect.w = width_;
		rect.h = height_;
		return rect;
	}

	void Set_Text(const std::string& text) { text_string_ = text; } // Chuyen noi dung cua nguoi dung muon hien thi thanh mot bien string text_string_
	std::string Get_Text() const { return text_string_; } // Lay bien string text_string_
private:
	std::string text_string_;
	SDL_Color text_color_;
	SDL_Texture* text_textture_;
	int width_, height_;
	int x_pos_, y_pos_;
};
