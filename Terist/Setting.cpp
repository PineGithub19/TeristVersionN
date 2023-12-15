#include "Setting.h"

Setting::Setting()
{

}

Setting::~Setting()
{

}

void Setting::LoadSetting(SDL_Renderer* renderer, SDL_Event& g_event, TTF_Font* TitleFont, TTF_Font*NormalFont, bool&is_in_menu, bool&is_in_program, Mix_Music*& music)
{
	int x_mouse = 0, y_mouse = 0;
	TextObject title, turn_on, turn_off, back_btn;
	BaseObject* bg = new BaseObject;

	bg->LoadImage("assets//credits.png", renderer);

	title.SetColor(TextObject::YELLOW_TEXT);
	turn_on.SetColor(TextObject::YELLOW_TEXT);
	turn_off.SetColor(TextObject::YELLOW_TEXT);
	back_btn.SetColor(TextObject::YELLOW_TEXT);

	InitTextContent(renderer, TitleFont, title, "SETTING", 10);
	InitTextContent(renderer, NormalFont, turn_on, "TURN ON MUSIC", 300);
	InitTextContent(renderer, NormalFont, turn_off, "TURN OFF MUSIC", 400);
	InitTextContent(renderer, NormalFont, back_btn, "BACK", 500);

	vector<TextObject*> items = { &turn_on, &turn_off, &back_btn };

	bool selected = false;
	while (true)
	{
		SDL_RenderClear(renderer);

		bg->Render(renderer);
		title.RenderText(renderer, title.Get_Rect().x, title.Get_Rect().y);
		turn_on.RenderText(renderer, turn_on.Get_Rect().x, turn_on.Get_Rect().y);
		turn_off.RenderText(renderer, turn_off.Get_Rect().x, turn_off.Get_Rect().y);
		back_btn.RenderText(renderer, back_btn.Get_Rect().x, back_btn.Get_Rect().y);

		while (SDL_PollEvent(&g_event))
		{
			x_mouse = g_event.motion.x;
			y_mouse = g_event.motion.y;

			if (g_event.type == SDL_QUIT)
			{
				is_in_program = true;
				is_in_menu = false;
				SDL_Quit();
				return;
			}
			else if (g_event.type == SDL_MOUSEMOTION)
			{
				for (int it = 0; it < items.size(); it++)
				{
					if (x_mouse >= items[it]->Get_Rect().x && x_mouse <= items[it]->Get_Rect().x + items[it]->Get_Rect().w &&
						y_mouse >= items[it]->Get_Rect().y && y_mouse <= items[it]->Get_Rect().y + items[it]->Get_Rect().h)
					{
						if (selected == false)
						{
							items[it]->SetColor(TextObject::RED_TEXT);
							selected = true;
						}
					}
					else
					{
						selected = false;
						items[it]->SetColor(TextObject::YELLOW_TEXT);
					}
					if (it == 0)
						InitTextContent(renderer, NormalFont, turn_on, "TURN ON MUSIC", 300);
					else if (it == 1)
						InitTextContent(renderer, NormalFont, turn_off, "TURN OFF MUSIC", 400);
					else if (it == 2)
						InitTextContent(renderer, NormalFont, back_btn, "BACK", 500);
				}
			}
			else if (g_event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (g_event.button.button == SDL_BUTTON_LEFT)
				{
					for (int it = 0; it < items.size(); it++)
					{
						if (x_mouse >= items[it]->Get_Rect().x && x_mouse <= items[it]->Get_Rect().x + items[it]->Get_Rect().w &&
							y_mouse >= items[it]->Get_Rect().y && y_mouse <= items[it]->Get_Rect().y + items[it]->Get_Rect().h)
						{
							if (it == 0)
							{
								Mix_PlayMusic(music, 1);
							}
							else if (it == 1)
							{
								Mix_HaltMusic();
							}
							else if (it == 2)
							{
								is_in_menu = true;
								return;
							}
							break;
						}
					}
				}
			}
		}

		SDL_RenderPresent(renderer);
	}

	delete bg;
	bg = NULL;
}

