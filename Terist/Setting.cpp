#include "Setting.h"

Setting::Setting()
{
	volumn = 64;
}

Setting::~Setting()
{

}

void Setting::setVolumn(const int& vol)
{
	volumn = vol;
}

int Setting::getVolumn() const
{
	return volumn;
}

void Setting::LoadSetting(SDL_Renderer* renderer, SDL_Event& g_event, TTF_Font* TitleFont, TTF_Font*NormalFont, bool&is_in_menu, bool&is_in_program, Mix_Music*& music)
{
	int x_mouse = 0, y_mouse = 0;
	TextObject title, turn_on, turn_off, inc_music, dec_music, back_btn;
	BaseObject* bg = new BaseObject;

	bg->LoadImage("assets//credits.png", renderer);

	title.SetColor(TextObject::YELLOW_TEXT);
	turn_on.SetColor(TextObject::YELLOW_TEXT);
	turn_off.SetColor(TextObject::YELLOW_TEXT);
	inc_music.SetColor(TextObject::YELLOW_TEXT);
	dec_music.SetColor(TextObject::YELLOW_TEXT);
	back_btn.SetColor(TextObject::YELLOW_TEXT);

	InitTextContent(renderer, TitleFont, title, "SETTING", 10);
	InitTextContent(renderer, NormalFont, turn_on, "TURN ON MUSIC", 200);
	InitTextContent(renderer, NormalFont, turn_off, "TURN OFF MUSIC", 300);
	InitTextContent(renderer, NormalFont, inc_music, "INCREASE VOLUMN", 400);
	InitTextContent(renderer, NormalFont, dec_music, "DECREASE VOLUMN", 500);
	InitTextContent(renderer, NormalFont, back_btn, "BACK", 600);

	vector<TextObject*> items = { &turn_on, &turn_off, &inc_music, &dec_music, &back_btn };

	bool selected = false;
	while (true)
	{
		SDL_RenderClear(renderer);

		bg->Render(renderer);
		title.RenderText(renderer, title.Get_Rect().x, title.Get_Rect().y);
		turn_on.RenderText(renderer, turn_on.Get_Rect().x, turn_on.Get_Rect().y);
		turn_off.RenderText(renderer, turn_off.Get_Rect().x, turn_off.Get_Rect().y);
		inc_music.RenderText(renderer, inc_music.Get_Rect().x, inc_music.Get_Rect().y);
		dec_music.RenderText(renderer, dec_music.Get_Rect().x, dec_music.Get_Rect().y);
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
						InitTextContent(renderer, NormalFont, turn_on, "TURN ON MUSIC", 200);
					else if (it == 1)
						InitTextContent(renderer, NormalFont, turn_off, "TURN OFF MUSIC", 300);
					else if (it == 2)
						InitTextContent(renderer, NormalFont, inc_music, "INCREASE VOLUMN", 400);
					else if (it == 3)
						InitTextContent(renderer, NormalFont, dec_music, "DECREASE VOLUMN", 500);
					else if (it == 4)
						InitTextContent(renderer, NormalFont, back_btn, "BACK", 600);
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
								if (getVolumn() >= 100)
									setVolumn(100);
								setVolumn(getVolumn() + 20);
								Mix_VolumeMusic(getVolumn() + 20);
								Mix_PlayMusic(music, 1);
							}
							else if (it == 3)
							{
								if (getVolumn() <= 0)
									setVolumn(0);
								setVolumn(getVolumn() - 20);
								Mix_VolumeMusic(getVolumn() - 20);
								Mix_PlayMusic(music, 1);
							}
							else if (it == 4)
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

