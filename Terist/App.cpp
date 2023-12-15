#include "Base.h"
#include "MenuObject.h"

bool Init(SDL_Window*& g_window, SDL_Renderer*& g_screen, TTF_Font*& TitleFont, TTF_Font*& NormalFont)
{
    bool success = true;
    int res = SDL_Init(SDL_INIT_VIDEO);
    if (res < 0)
        return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("GROUP 5 - DESIGN PATTERNS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (!g_window)
        success = false;
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (!g_screen)
            success = false;
        else
        {
            SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
            int img_flag = IMG_INIT_PNG;
            
            if (!(IMG_Init(img_flag) && img_flag))
                success = false;
        }

        if (TTF_Init() == -1)
            return false;
        
        TitleFont = TTF_OpenFont("font//MoonKids1.ttf", 64);
        NormalFont = TTF_OpenFont("font//MoonKids1.ttf", 32);

        if (TitleFont == NULL || NormalFont == NULL)
            return false;

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 4096) < 0)
        {
            printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
            success = false;
        }
    }
    return success;
}

bool LoadBackground(SDL_Renderer* renderer, BaseObject& bg)
{
    bool res = bg.LoadImage("assets//background.png", renderer);
    return res;
}

void Close(SDL_Window*& g_window, SDL_Renderer*& g_screen)
{
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    static SDL_Window* g_window = NULL;
    static SDL_Renderer* g_screen = NULL;
    static SDL_Event g_event;
    static TTF_Font* TitleFont = NULL;
    static TTF_Font* NormalFont = NULL;

    BaseObject bg, logo;
    int decision = -1;

    if (!Init(g_window, g_screen, TitleFont, NormalFont) || !LoadBackground(g_screen, bg))
    {
        return 0;
    }

    /* TEXT */
    int index_hover = -1;
    MenuObject main_menu;
    TextObject title_game, play_game, credits_game, quit_game, setting_game;

    main_menu.LoadLogoGame(g_screen, logo);
    main_menu.InitTitleGame(title_game, g_screen, TitleFont);
    main_menu.InitPlayGame(play_game, g_screen, NormalFont);
    main_menu.InitCreditsGame(credits_game, g_screen, NormalFont);
    main_menu.InitQuitGame(quit_game, g_screen, NormalFont);
    main_menu.InitSettingGame(setting_game, g_screen, NormalFont);

    vector<TextObject*> text_menu_components = {&play_game, &credits_game, &quit_game, &setting_game};

    bool is_quit = false;
    while (!is_quit)
    {
        SDL_RenderClear(g_screen);

        main_menu.Move_Menu(g_screen, bg);
        logo.Render(g_screen);

        title_game.RenderText(g_screen, title_game.Get_Rect().x, title_game.Get_Rect().y);
        play_game.RenderText(g_screen, play_game.Get_Rect().x, play_game.Get_Rect().y);
        credits_game.RenderText(g_screen, credits_game.Get_Rect().x, credits_game.Get_Rect().y);
        quit_game.RenderText(g_screen, quit_game.Get_Rect().x, quit_game.Get_Rect().y);
        setting_game.RenderText(g_screen, setting_game.Get_Rect().x, setting_game.Get_Rect().y);

        while (SDL_PollEvent(&g_event))
        {
            decision = main_menu.Main_Menu(g_screen, g_event, text_menu_components, main_menu, is_quit, index_hover);
            if (index_hover == 0)
                main_menu.InitPlayGame(play_game, g_screen, NormalFont);
            else if (index_hover == 1)
                main_menu.InitCreditsGame(credits_game, g_screen, NormalFont);
            else if (index_hover == 2)
                main_menu.InitQuitGame(quit_game, g_screen, NormalFont);
            else if (index_hover == 3)
                main_menu.InitSettingGame(setting_game, g_screen, NormalFont);
        }

        SDL_RenderPresent(g_screen);
    }
    Close(g_window, g_screen);

    return 0;
}