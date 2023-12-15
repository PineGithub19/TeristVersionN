#include "Base.h"

BaseObject::BaseObject()
{
	p_object_ = NULL;
	rect_.x = rect_.y = rect_.w = rect_.h = 0;
}

BaseObject::~BaseObject()
{
	Free();
}

void BaseObject::setRectSize(const int& w, const int& h)
{
	rect_.w = w;
	rect_.h = h;
}

void BaseObject::setRect(const int& x, const int& y)
{
	rect_.x = x;
	rect_.y = y;
}

SDL_Rect BaseObject::getRect() const
{
	return rect_;
}

SDL_Texture* BaseObject::getTexture() const
{
	return p_object_;
}

bool BaseObject::LoadImage(string path, SDL_Renderer* screen)
{
	Free();
	SDL_Texture* newTexture = NULL;
	
	SDL_Surface* loadSurface = IMG_Load(path.c_str());
	if (loadSurface)
	{
		SDL_SetColorKey(loadSurface, SDL_TRUE, SDL_MapRGB(loadSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
		newTexture = SDL_CreateTextureFromSurface(screen, loadSurface);
		if (newTexture)
		{
			rect_.w = loadSurface->w;
			rect_.h = loadSurface->h;
		}
		SDL_FreeSurface(loadSurface);
	}
	p_object_ = newTexture;
	return (p_object_ != NULL);
}

void BaseObject::Render(SDL_Renderer* screen, const SDL_Rect* clip)
{
	SDL_Rect renderquad = { rect_.x, rect_.y, rect_.w, rect_.h };
	SDL_RenderCopy(screen, p_object_, clip, &renderquad);
}

void BaseObject::Free()
{
	if (!p_object_)
	{
		SDL_DestroyTexture(p_object_);
		p_object_ = NULL;
		rect_.w = 0;
		rect_.h = 0;
	}
}

bool CommonFunc::CheckCollision(const SDL_Rect& object_1, const SDL_Rect& object_2)
{
	int left_1 = object_1.x, right_1 = object_1.x + object_1.w, top_1 = object_1.y, bottom_1 = object_1.y + object_1.h;
	int left_2 = object_2.x, right_2 = object_2.x + object_2.w, top_2 = object_2.y, bottom_2 = object_2.y + object_2.h;

	// case 1 object_1 small than object_2
	if (right_1 > left_2 && right_1 < right_2 && bottom_1 > top_2 && bottom_1 < bottom_2) return true;
	if (right_1 > left_2 && right_1 < right_2 && top_1 > top_2 && top_1 < bottom_2) return true;
	if (left_1 > left_2 && left_1 < right_2 && bottom_1 > top_2 && bottom_1 < bottom_2) return true;
	if (left_1 > left_2 && left_1 < right_2 && top_1 > top_2 && top_1 < bottom_2) return true;

	// case 2 object_1 bigger than object_2
	if (right_2 > left_1 && right_2 < right_1 && bottom_2 > top_1 && bottom_2 < bottom_1) return true;
	if (right_2 > left_1 && right_2 < right_1 && top_2 > top_1 && top_2 < bottom_1) return true;
	if (left_2 > left_1 && left_2 < right_1 && bottom_2 > top_1 && bottom_2 < bottom_1) return true;
	if (left_2 > left_1 && left_2 < right_1 && top_2 > top_1 && top_2 < bottom_1) return true;

	// case 3 object_1 equals to object_2
	if (left_1 == left_2 && right_1 == right_2 && top_1 == top_2 && bottom_1 == bottom_2) return true;

	return false;
}