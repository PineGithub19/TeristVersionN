#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 640

using namespace std;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 186;

class BaseObject
{
protected:
	SDL_Texture* p_object_;
	SDL_Rect rect_;
public:
	BaseObject();
	~BaseObject();

	void setRect(const int&, const int&);
	void setRectSize(const int&, const int&);
	SDL_Rect getRect() const;
	SDL_Texture* getTexture() const;

	bool LoadImage(string, SDL_Renderer*);
	void Render(SDL_Renderer*, const SDL_Rect* clip = NULL);
	void Free();
};

namespace CommonFunc
{
	bool CheckCollision(const SDL_Rect& object_1, const SDL_Rect& object_2);
}