#include<iostream>
#include"SDL.h"
#include<thread>


const int WIDTH = 800, HEIGHT = 600;

void SetWalkingPath(float &x, float &y, SDL_KeyboardEvent key){
    if (key.type == SDL_KEYDOWN){
        switch (key.keysym.sym)
        {
        case SDLK_UP:
            y --;
            break;
        case SDLK_DOWN:
            y++;
            break;
        case SDLK_RIGHT:
            x++;
            break;
        case SDLK_LEFT:
            x--;
            break;
        
        default:
            return;
        }
    }else if(key.type == SDL_KEYUP){
        switch (key.keysym.sym)
        {
        case SDLK_UP:
            y++;
            break;
        case SDLK_DOWN:
            y--;
            break;
        case SDLK_RIGHT:
            x--;
            break;
        case SDLK_LEFT:
            x++;
            break;
        
        default:
            return;
        }
    }
    if(y>1) y=1;
    else if (y<-1) y = -1;
    if (x>1) x = 1;
    else if (x<-1) x = -1;
}

int main(int argc, char* argv[]){

    SDL_Init( SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow( "I love cubes!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Point pMousePos;
    SDL_Rect rRect{0, 0, 50, 50};

    float vx = 0;
    float vy = 0;

    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_RenderClear(renderer);
    

    if (window == NULL){
        std::cout << "No se pudo crear ventana: " << SDL_GetError() << std::endl;
        return 1;
    }
    SDL_Log("Hello World");

    SDL_Event windowEvent;

    while(true){
        std::this_thread::sleep_for<int64_t, std::milli>(std::chrono::milliseconds(1000/35));
        //INPUT
        if (SDL_PollEvent(&windowEvent))
            if (windowEvent.type == SDL_QUIT) break;
            else if(windowEvent.type == SDL_KEYDOWN|| windowEvent.type == SDL_KEYUP) SetWalkingPath(vx, vy, windowEvent.key);

        
        //PROCESING
        rRect.x += (vx*5);
        rRect.y += (vy*5);
        if (rRect.x < 0) rRect.x = 0;
        else if (rRect.x > WIDTH-rRect.w) rRect.x = WIDTH-rRect.w;
        if (rRect.y < 0) rRect.y = 0;
        else if (rRect.y > HEIGHT-rRect.h) rRect.y = HEIGHT-rRect.h;
        


        //RENDERING
        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rRect);
        SDL_RenderPresent(renderer);

    }

    SDL_DestroyWindow(window);

    SDL_Quit();

    return EXIT_SUCCESS;
    
    return 0;
}