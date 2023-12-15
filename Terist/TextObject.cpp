#include "TextObject.h"

TextObject::TextObject()
{
	text_color_.r = 255;
	text_color_.g = 255;
	text_color_.b = 255;
	text_textture_ = NULL;
	width_ = height_ = 0;
	x_pos_ = y_pos_ = 0;
	SetColor(TextObject::WHITE_TEXT);
}

TextObject::~TextObject()
{

}

bool TextObject::LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen)
{
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, text_string_.c_str(), text_color_);
	if (text_surface != NULL)
	{
		text_textture_ = SDL_CreateTextureFromSurface(screen, text_surface);
		width_ = text_surface->w;
		height_ = text_surface->h;

		SDL_FreeSurface(text_surface);
	}
	return text_textture_ != NULL;
}

void TextObject::Free_Text()
{
	if (text_textture_ != NULL)
	{

		SDL_DestroyTexture(text_textture_);
		text_textture_ = NULL;
	}
}

void TextObject::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	text_color_.r = red;
	text_color_.g = green;
	text_color_.b = blue;
}

void TextObject::SetColor(int type)
{
	SDL_Color color;
	if (type == RED_TEXT)
	{
		color = { 255, 53 ,94 };
		text_color_ = color;
	}
	else if (type == WHITE_TEXT)
	{
		color = { 255, 255, 255 };
		text_color_ = color;
	}
	else if (type == BLACK_TEXT)
	{
		color = { 0, 0, 0 };
		text_color_ = color;
	}
	else if (type == YELLOW_TEXT)
	{
		color = { 238, 220, 130 };
		text_color_ = color;
	}
}

void TextObject::RenderText(SDL_Renderer* screen, int x_pos, int y_pos, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect renderquad = { x_pos, y_pos, width_, height_ };
	if (clip != NULL)
	{
		renderquad.w = clip->w;
		renderquad.h = clip->h;
		;
	}
	SDL_RenderCopyEx(screen, text_textture_, clip, &renderquad, angle, center, flip);
}
