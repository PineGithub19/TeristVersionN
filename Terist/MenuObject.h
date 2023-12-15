#pragma once
#include "Base.h"
#include "TextObject.h"

#define MENU_SPEED 0.0125

class MenuObject : public BaseObject
{
private:
	double menu_speed;
	bool is_in_menu;
	bool is_quit_program;
public:
	MenuObject(const double& = 0, const bool& = false, const bool& = false);
	~MenuObject();

	int Main_Menu(SDL_Renderer*, SDL_Event, std::vector<TextObject*>&, MenuObject&, bool&, int&);
	void Move_Menu(SDL_Renderer*, BaseObject&);

	bool LoadLogoGame(SDL_Renderer*, BaseObject&);

	void InitTitleGame(TextObject&, SDL_Renderer*, TTF_Font*);
	void InitPlayGame(TextObject&, SDL_Renderer*, TTF_Font*);
	void InitCreditsGame(TextObject&, SDL_Renderer*, TTF_Font*);
	void InitQuitGame(TextObject&, SDL_Renderer*, TTF_Font*);
	void InitSettingGame(TextObject&, SDL_Renderer*, TTF_Font*);
};