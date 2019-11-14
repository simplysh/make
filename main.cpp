//#include <SDL2/SDL.h>
#include "hello.h"
#include <iostream>

int main(int argc, char* argv[]) {
  std::cout << "Version " VERSION << std::endl;
  sayHello();

  //SDL_Init(SDL_INIT_EVERYTHING);
  //SDL_Quit();

  return 0;
}
