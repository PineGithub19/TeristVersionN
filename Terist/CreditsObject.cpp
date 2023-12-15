#include "CreditsObject.h"

CreditsObject::CreditsObject()
{

}

CreditsObject::~CreditsObject()
{

}

void CreditsObject::InitTextContent(SDL_Renderer* renderer, TTF_Font* font, TextObject& obj, const string& content, const int& ypos)
{
	obj.Set_Text(content);
	obj.LoadFromRenderText(font, renderer);
	obj.Set_Rect(SCREEN_WIDTH / 2.0 - obj.Get_Rect().w / 2.0, ypos);
}

void CreditsObject::LoadCredits(SDL_Renderer* renderer, SDL_Event& g_event, TTF_Font* TitleFont, TTF_Font* NormalFont, bool& is_in_menu, bool& is_in_program)
{
	int x_mouse = 0, y_mouse = 0;
	BaseObject* bg = new BaseObject;
	TextObject title, p1, p2, p3, p4, back_btn;

	title.SetColor(TextObject::YELLOW_TEXT);
	p1.SetColor(TextObject::YELLOW_TEXT);
	p2.SetColor(TextObject::YELLOW_TEXT);
	p3.SetColor(TextObject::YELLOW_TEXT);
	p4.SetColor(TextObject::YELLOW_TEXT);
	back_btn.SetColor(TextObject::YELLOW_TEXT);

	InitTextContent(renderer, TitleFont, title, "CREDITS", 10);
	InitTextContent(renderer, NormalFont, p1, "NGO VAN KHAI        22127174", 200);
	InitTextContent(renderer, NormalFont, p2, "LE PHUOC PHAT       22127322", 250);
	InitTextContent(renderer, NormalFont, p3, "TO QUOC THANH       22127388", 300);
	InitTextContent(renderer, NormalFont, p4, "THAI HUYEN TUNG     22127441", 350);
	InitTextContent(renderer, NormalFont, back_btn, "BACK", 550);

	bool res = bg->LoadImage("assets//credits.png", renderer);
	if (!res)
		return;

	bool selected = false;
	while (true)
	{
		SDL_RenderClear(renderer);

		bg->Render(renderer);
		title.RenderText(renderer, title.Get_Rect().x, title.Get_Rect().y);
		p1.RenderText(renderer, p1.Get_Rect().x, p1.Get_Rect().y);
		p2.RenderText(renderer, p2.Get_Rect().x, p2.Get_Rect().y);
		p3.RenderText(renderer, p3.Get_Rect().x, p3.Get_Rect().y);
		p4.RenderText(renderer, p4.Get_Rect().x, p4.Get_Rect().y);
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
				if (x_mouse >= back_btn.Get_Rect().x && x_mouse <= back_btn.Get_Rect().x + back_btn.Get_Rect().w &&
					y_mouse >= back_btn.Get_Rect().y && y_mouse <= back_btn.Get_Rect().y + back_btn.Get_Rect().h)
				{
					if (selected == false)
					{
						back_btn.SetColor(TextObject::RED_TEXT);
						InitTextContent(renderer, NormalFont, back_btn, "BACK", 550);
						selected = true;
					}
				}
				else
				{
					selected = false;
					back_btn.SetColor(TextObject::YELLOW_TEXT);
					InitTextContent(renderer, NormalFont, back_btn, "BACK", 550);
				}
			}
			else if (g_event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (x_mouse >= back_btn.Get_Rect().x && x_mouse <= back_btn.Get_Rect().x + back_btn.Get_Rect().w &&
					y_mouse >= back_btn.Get_Rect().y && y_mouse <= back_btn.Get_Rect().y + back_btn.Get_Rect().h)
				{
					is_in_menu = true;
					return;
				}
			}
		}
		SDL_RenderPresent(renderer);
	}

	delete bg;
	bg = NULL;
}
