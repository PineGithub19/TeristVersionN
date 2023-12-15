#include "Base.h"
#include "MenuObject.h"
#include "CreditsObject.h"

bool Init(SDL_Window*& g_window, SDL_Renderer*& g_screen, TTF_Font*& TitleFont, TTF_Font*& NormalFont)
{
    bool success = true;
    int res = SDL_Init(SDL_INIT_VIDEO);
    if (res < 0)
        return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("GROUP 5 - TETRIS GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

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

        TitleFont = TTF_OpenFont("font//BULKYPIX.ttf", 64);
        NormalFont = TTF_OpenFont("font//BULKYPIX.ttf", 32);

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

bool LoadBackground(SDL_Renderer* renderer, BaseObject& bg, const string& path)
{
    bool res = bg.LoadImage(path, renderer);
    return res;
}

void Close(SDL_Window*& g_window, SDL_Renderer*& g_screen)
{
    Mix_CloseAudio();
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

    //Sound Effect
    Mix_Chunk* chunk = NULL;
    //Background Music
    Mix_Music* music = NULL;

    BaseObject bg, logo;
    int decision = -1;

    if (!Init(g_window, g_screen, TitleFont, NormalFont) || !LoadBackground(g_screen, bg, "assets//background.png"))
    {
        return 0;
    }

    // MENU 
    int index_hover = -1;
    MenuObject* main_menu = new MenuObject;
    TextObject title_game, play_game, credits_game, quit_game, setting_game;

    main_menu->LoadLogoGame(g_screen, logo);
    main_menu->InitTitleGame(title_game, g_screen, TitleFont);
    main_menu->InitPlayGame(play_game, g_screen, NormalFont);
    main_menu->InitCreditsGame(credits_game, g_screen, NormalFont);
    main_menu->InitQuitGame(quit_game, g_screen, NormalFont);
    main_menu->InitSettingGame(setting_game, g_screen, NormalFont);

    //Init SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    {
        printf("%s", Mix_GetError());
        return -1;
    }

    //Load Sound Effect
    chunk = Mix_LoadWAV("music//enter.wav");
    if (chunk == NULL)
    {
        printf("%s", Mix_GetError());
        return -1;
    }

    //Load Music
    music = Mix_LoadMUS("music//nhacnen.mp3");
    if (music == NULL)
    {
        printf("%s", Mix_GetError());
    }
    Mix_PlayMusic(music, 1);

    vector<TextObject*> text_menu_components = { &play_game, &credits_game, &quit_game, &setting_game };

    // CREDITS
    CreditsObject* credits = NULL;

    bool is_quit = false;
    bool is_in_menu = true;
    while (!is_quit)
    {
        SDL_RenderClear(g_screen);

        if (is_in_menu)
        {
            main_menu->Move_Menu(g_screen, bg);
            logo.Render(g_screen);

            title_game.RenderText(g_screen, title_game.Get_Rect().x, title_game.Get_Rect().y);
            play_game.RenderText(g_screen, play_game.Get_Rect().x, play_game.Get_Rect().y);
            credits_game.RenderText(g_screen, credits_game.Get_Rect().x, credits_game.Get_Rect().y);
            quit_game.RenderText(g_screen, quit_game.Get_Rect().x, quit_game.Get_Rect().y);
            setting_game.RenderText(g_screen, setting_game.Get_Rect().x, setting_game.Get_Rect().y);
        }
        else if (is_in_menu == false)
        {
            if (decision == 1)
            {
                if (credits == NULL)
                {
                    credits = new CreditsObject();
                    credits->LoadCredits(g_screen, g_event, TitleFont, NormalFont, is_in_menu, is_quit);
                    delete credits;
                    credits = NULL;
                }
            }
        }

        while (SDL_PollEvent(&g_event) && is_in_menu)
        {
            decision = main_menu->Main_Menu(g_screen, g_event, text_menu_components, main_menu, is_quit, index_hover);
            if (index_hover == 0)
                main_menu->InitPlayGame(play_game, g_screen, NormalFont);
            else if (index_hover == 1)
                main_menu->InitCreditsGame(credits_game, g_screen, NormalFont);
            else if (index_hover == 2)
                main_menu->InitQuitGame(quit_game, g_screen, NormalFont);
            else if (index_hover == 3)
                main_menu->InitSettingGame(setting_game, g_screen, NormalFont);

            if (decision == 0)
            {
                is_in_menu = false;
            }
            else if (decision == 1)
            {
                is_in_menu = false;
            }
            else if (decision == 2)
            {
                is_in_menu = false;
                is_quit = true;
            }
            else if (decision == 3)
            {
                is_in_menu = false;
            }
        }

        SDL_RenderPresent(g_screen);
    }
    Close(g_window, g_screen);

    if (main_menu)
    {
        delete main_menu;
        main_menu = NULL;
    }

    return 0;
}