#include "MenuObject.h"

MenuObject::MenuObject(const double& speed, const bool& is_in_menu, const bool& is_quit_program) : menu_speed(speed), is_in_menu(is_in_menu), is_quit_program(is_quit_program)
{

}

MenuObject::~MenuObject()
{

}

int MenuObject::Main_Menu(SDL_Renderer* screen, SDL_Event events, std::vector<TextObject*>& text_menu_components, MenuObject& main_menu, bool& is_quit_program, int& index_hover)
{
	const int size = text_menu_components.size();
	int x_mouse = 0, y_mouse = 0;

	if (events.type == SDL_QUIT)
	{
		this->is_quit_program = true;
		is_quit_program = this->is_quit_program;
		this->is_in_menu = false;
		main_menu.Free();
		SDL_Quit();
		return -1;
	}
	if (events.type == SDL_MOUSEMOTION)
	{
		x_mouse = events.motion.x;
		y_mouse = events.motion.y;
		bool* selected = new bool[size] { false };

		for (int items = 0; items < size; items++)
		{
			if (x_mouse >= text_menu_components[items]->Get_Rect().x && x_mouse <= text_menu_components[items]->Get_Rect().x + text_menu_components[items]->Get_Rect().w
				&& y_mouse >= text_menu_components[items]->Get_Rect().y && y_mouse <= text_menu_components[items]->Get_Rect().y + text_menu_components[items]->Get_Rect().h)
			{
				if (selected[items] == false)
				{
					index_hover = items;
					selected[items] = true;
					text_menu_components[items]->SetColor(TextObject::RED_TEXT);
				}
			}
			else
			{
				selected[items] = false;
				text_menu_components[items]->SetColor(TextObject::WHITE_TEXT);
			}
		}
		delete[]selected;
	}
	if (events.type == SDL_MOUSEBUTTONDOWN)
	{
		if (events.button.button == SDL_BUTTON_LEFT)
		{
			x_mouse = events.button.x;
			y_mouse = events.button.y;

			for (int items = 0; items < size; items++)
			{
				/*std::cout << x_mouse << " " << y_mouse << std::endl;
				std::cout << text_menu_components[items]->Get_Rect().x << " " << text_menu_components[items]->Get_Rect().y << " " << text_menu_components[items]->Get_Rect().w << " " << text_menu_components[items]->Get_Rect().h << std::endl;*/
				if (x_mouse >= text_menu_components[items]->Get_Rect().x && x_mouse <= text_menu_components[items]->Get_Rect().x + text_menu_components[items]->Get_Rect().w
					&& y_mouse >= text_menu_components[items]->Get_Rect().y && y_mouse <= text_menu_components[items]->Get_Rect().y + text_menu_components[items]->Get_Rect().h)
				{
					return items;
				}
			}
		}

	}
	return -1;
}

void MenuObject::Move_Menu(SDL_Renderer* screen, BaseObject& menu)
{
	menu_speed -= MENU_SPEED;
	menu.setRect(0, menu_speed);
	menu.Render(screen);
	menu.setRect(0, menu_speed + SCREEN_HEIGHT);
	menu.Render(screen);
	if (menu_speed <= -SCREEN_HEIGHT)
		menu_speed = 0;
}

bool MenuObject::LoadLogoGame(SDL_Renderer* renderer, BaseObject& logo)
{
	bool res = logo.LoadImage("assets//logo.png", renderer);
	logo.setRectSize(256, 256);
	logo.setRect(SCREEN_WIDTH / 2.0 - logo.getRect().w / 2.0, 80);
	if (!res)
		cout << "Loi Hinh Anh LoGo!!!\n";
	return res;
}

void MenuObject::InitTitleGame(TextObject& title_game, SDL_Renderer* renderer, TTF_Font* font)
{
	std::string title = "TETRIS GAME";

	title_game.Set_Text(title);
	title_game.LoadFromRenderText(font, renderer);
	title_game.Set_Rect(SCREEN_WIDTH / 2.0 - title_game.Get_Rect().w / 2.0, 10);
}

void MenuObject::InitPlayGame(TextObject& playgame, SDL_Renderer* renderer, TTF_Font* font)
{
	std::string title = "PLAY GAME";

	playgame.Set_Text(title);
	playgame.LoadFromRenderText(font, renderer);
	playgame.Set_Rect(SCREEN_WIDTH / 2.0 - playgame.Get_Rect().w / 2.0, 350);
}

void MenuObject::InitCreditsGame(TextObject& credits, SDL_Renderer* renderer, TTF_Font* font)
{
	std::string title = "CREDITS GAME";

	credits.Set_Text(title);
	credits.LoadFromRenderText(font, renderer);
	credits.Set_Rect(SCREEN_WIDTH / 2.0 - credits.Get_Rect().w / 2.0, 450);
}

void MenuObject::InitQuitGame(TextObject& quit_game, SDL_Renderer* renderer, TTF_Font* font)
{
	std::string title = "QUIT GAME";

	quit_game.Set_Text(title);
	quit_game.LoadFromRenderText(font, renderer);
	quit_game.Set_Rect(SCREEN_WIDTH / 2.0 - quit_game.Get_Rect().w / 2.0, 550);
}

void MenuObject::InitSettingGame(TextObject& setting_game, SDL_Renderer* renderer, TTF_Font* font)
{
	std::string title = "SETTING";

	setting_game.Set_Text(title);
	setting_game.LoadFromRenderText(font, renderer);
	setting_game.Set_Rect(1120, 600);
}