#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include<mySDL2Tools/MySDLStruct.h>
#include"game2048.h"

int frame = 40;
int msPerFrame = 1000 / frame;

int scr_width = 800, scr_height = 700;
SDL_Color backgroundColor = {.r = 196, .g = 158, .b = 117, .a = 255};
// SDL_Color planeColor = {.r = 205, .g = 193, .b = 180, .a = 255};
const char* imgSrcFilename = "src/2048_.png";
SDL_Color screenBackgroundColor = {.r = 255, .g = 255, .b = 255, .a = 255};


int main(int argv, char* argc[]){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("2048", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        scr_width, scr_height,
                                        SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
                                        SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

    IMG_Init(IMG_INIT_PNG);


    SDL_RenderSetLogicalSize(renderer, scr_width, scr_height);
    int posX = 0.2 * scr_width;
    int posY = 0.2 * scr_height;
    int width = 0.6 * scr_width;
    int spacing = 15;
    SDL_Rect renderRect = {.x = posX, .y = posY, .w = width, .h = width};

    game2048 GameMain{renderer, imgSrcFilename, backgroundColor, renderRect,
                        (width - 3 * spacing) / 4, spacing};
    // std::cout << GameMain.texture.rect.w << "x" << GameMain.texture.rect.h << std::endl;
    GameMain.initialGame();

    SDL_Event eve;
    Uint32 time = SDL_GetTicks(), oldTime, deltaTime;
    while(GameMain.runFlag){
        oldTime = time;
        time = SDL_GetTicks();
        while(SDL_PollEvent(&eve)){
            if(eve.type == SDL_QUIT){
                GameMain.runFlag = false;
            }
            else if(eve.type == SDL_KEYDOWN){
                switch(eve.key.keysym.sym){
                    case SDLK_UP:
                    case SDLK_w:
                        GameMain.moveBlocks(0);
                        break;
                    case SDLK_RIGHT:
                    case SDLK_d:
                        GameMain.moveBlocks(1);
                        break;
                    case SDLK_DOWN:
                    case SDLK_s:
                        GameMain.moveBlocks(2);
                        break;
                    case SDLK_LEFT:
                    case SDLK_a:
                        GameMain.moveBlocks(3);
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, backgroundColor.r,
                                backgroundColor.g, backgroundColor.b,
                                backgroundColor.a);
        SDL_RenderClear(renderer);

        GameMain.render();

        SDL_RenderPresent(renderer);

        deltaTime = SDL_GetTicks() - time;
        if(deltaTime < msPerFrame)
            SDL_Delay(msPerFrame - deltaTime);

    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}