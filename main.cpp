#include <SDL2/SDL.h>
#include <iostream>
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
//Inicia SDL y crea una ventana
SDL_Window* init();
//Carga los medios
SDL_Surface* loadMedia();
//Libera memoria y recursos, además de apagar SDL
void close(SDL_Window *win);
int main(int argc, char** arcv)
{
    SDL_Surface* screenSurface = nullptr;
    SDL_Surface* surfacePrueba = nullptr;
    SDL_Window* window = nullptr;
    window = init();
    if(window == nullptr)
    {
	return 1;
    }
    else
    {
	//Saca el surface
	screenSurface = SDL_GetWindowSurface(window);
	surfacePrueba = loadMedia();
	if(surfacePrueba == nullptr)
	{
	    return 1;
	}
	else
	{
	    //Llena el surface
	    std::cout<<"Intentando lacer el blit";
	    SDL_BlitSurface(surfacePrueba, NULL, screenSurface, NULL);
	    //Actualiza surface
	    SDL_UpdateWindowSurface(window);
	    //Espera de dos segundos
	    SDL_Delay(2000);
	}
	SDL_FreeSurface(surfacePrueba);
	close(window);
	return 0;
    }
}
SDL_Window* init()
{
    SDL_Window* resp = nullptr;
    //Inicia SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
	std::cout<<"SDL no pudo iniciarse, SDL_Error: "<< SDL_GetError();
	return nullptr;
    }
    else
    {
	//Creando ventana
	resp = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
	if(resp == nullptr)
	{
	    std::cout<<"No se pudo crear la ventana, SDL_Error: " << SDL_GetError()<<std::endl;
	    SDL_Quit();
	    return nullptr;
	}
	else
	{
	    return resp;
	}
	
    }
}
SDL_Surface* loadMedia()
{
    //Respuesta que se va a devolver
    SDL_Surface* resp = nullptr;
    resp = SDL_LoadBMP("images/hello.bmp");
    if(resp == nullptr)
    {
	std::cout<<"No se puede cargar la imagen, SDL_Error: " << SDL_GetError()<<std::endl;
	return nullptr;
    }
    else
    {
	return resp;
    }
}
void close(SDL_Window* win)
{
    SDL_DestroyWindow(win);
    win = nullptr;
    SDL_Quit();
}
