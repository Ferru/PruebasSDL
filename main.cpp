#include <SDL2/SDL.h>
#include <iostream>
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
int main(int argc, char** arcv)
{
    SDL_Window* window = nullptr;
    SDL_Surface* screenSurface = nullptr;
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
	std::cout<<"No pudo iniciar SDL " << SDL_GetError()<< std::endl;
	return 1;
    }
    else
    {
	//Creando ventana
	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(window == nullptr)
	{
	    std::cout<<"No pudo crear ventana " << SDL_GetError()<<std::endl;
	    return 1;
	}
	else
	{
	    //Saca el surface
	    screenSurface = SDL_GetWindowSurface(window);
	    //Llena el surface
	    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF,0xFF));
	    //Actualiza surface
	    SDL_UpdateWindowSurface(window);
	    //Espera de dos segundos
	    SDL_Delay(2000);
	}
    }
    //Limpiando recursos
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
