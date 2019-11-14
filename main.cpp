#include <SDL2/SDL.h>
#include "hello.h"

int main(int argc, char *argv[]) {
  sayHello();

  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Quit();

  return 0;
}
