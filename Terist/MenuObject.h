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

	int Main_Menu(SDL_Renderer*, SDL_Event, std::vector<TextObject*>&, MenuObject*&, bool&, int&); // Thuc hien hien thi menu chinh
	void Move_Menu(SDL_Renderer*, BaseObject&); // Di chuyen hinh nen menu

	bool LoadLogoGame(SDL_Renderer*, BaseObject&); // Hien thi Logo nhom

	void InitTitleGame(TextObject&, SDL_Renderer*, TTF_Font*); // Hien thi ten game
	void InitPlayGame(TextObject&, SDL_Renderer*, TTF_Font*); // Hien thi chu playgame
	void InitCreditsGame(TextObject&, SDL_Renderer*, TTF_Font*); // Hien thi chu credits
	void InitQuitGame(TextObject&, SDL_Renderer*, TTF_Font*); // Hien thi chu quitgame
	void InitSettingGame(TextObject&, SDL_Renderer*, TTF_Font*); // hien thi chu setting
};