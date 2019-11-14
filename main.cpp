#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <stdlib.h>
#include "hello.h"

int main(int argc, char* argv[]) {
  std::cout << "Version " VERSION << std::endl;
  sayHello();

  const int width = 1920 / 3;
  const int height = 1080 / 3;

  SDL_Window* window = NULL;
  SDL_Surface* screen = NULL;
  SDL_Renderer* renderTarget = NULL;
  SDL_DisplayMode displayMode;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "Can't initialize SDL: " << SDL_GetError() << std::endl;
    return 1;
  }

  // create the window and surfaces
  window = SDL_CreateWindow("Universal Make " VERSION, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
  screen = SDL_GetWindowSurface(window);
  renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  // create the font
  const std::string textSource = "BalooBhaina-Regular.ttf";
  const std::string textMessage = "You're all set! :)";
  SDL_Color white = { 255, 255, 255, 255 };

  TTF_Font* font = TTF_OpenFont(textSource.c_str(), 100);
  SDL_Surface* textSurface = TTF_RenderText_Blended(font, textMessage.c_str(), white);
  SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderTarget, textSurface);

  SDL_Rect textRect;
  SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);

  textRect.x = (width - textRect.w) / 2;
  textRect.y = (height - textRect.h) / 2;

  SDL_FreeSurface(textSurface);
  textSurface = nullptr;

  // mainloop
  bool running = true;
  SDL_Event event;

  SDL_SetRenderDrawColor(renderTarget, 150, 50, 100, 255);

  while (running) {
    while (SDL_PollEvent(&event) != 0) {
      switch (event.type) {
        case SDL_QUIT:
          running = false;
          break;
        default:
          break;
      }
    }

    SDL_RenderClear(renderTarget);

    SDL_RenderCopy(renderTarget, textTexture, NULL, &textRect);
    SDL_RenderPresent(renderTarget);
  }

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderTarget);

  SDL_DestroyTexture(textTexture);

  IMG_Quit();
  TTF_Quit();
  SDL_Quit();

  return 0;
}
