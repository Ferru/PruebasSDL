#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <string>
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
//Inicia SDL y crea una ventana
bool init(SDL_Window** win, SDL_Renderer** ren);
//Carga los medios
bool loadMedia();
//Libera memoria y recursos, además de apagar SDL
void close(SDL_Window *win);
//CArga individualmente una imagen
SDL_Surface* loadSurface(std::string path, SDL_Surface* screenSurface);
SDL_Texture* loadTexture(std::string path, SDL_Renderer* ren);
int main(int argc, char** argv)
{
    SDL_Renderer* ren = nullptr;
    SDL_Window* window = nullptr;
    SDL_Texture* texture = nullptr;
    bool isInit = init(&window, &ren);
    std::cout<<window<<" " << ren <<std::endl;
    if(!isInit)
    {
	return 1;
    }
    else
    {
	bool test = loadMedia();
	if(!test)
	{
	    std::cout<<"Texture nulo"<<std::endl;
	    return 1;
	}
	else
	{
	    //Main loog flag
	    bool quit = false;
	    //Manejador de eventos
	    SDL_Event e;
	    //Surface por defecto
	    //Mientras no se cierre la aplicación
	    while(!quit)
	    {
	    	//Manejo de eventos en la cola de eventos
		while(SDL_PollEvent(&e) != 0)
		{
		    //Evento de salida
		    if(e.type == SDL_QUIT)
		    {
			quit = true;
		    }
		}
		//Limpiando screen
		SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF,0xFF);
		SDL_RenderClear(ren);
		//render red filled quad
		SDL_Rect fillRect = {SCREEN_WIDTH/4, SCREEN_HEIGHT/4, SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
		SDL_SetRenderDrawColor(ren, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(ren, &fillRect);
		//render green outlined quad
		SDL_Rect outlineRect = {SCREEN_WIDTH/6, SCREEN_HEIGHT/6, SCREEN_WIDTH * 2 /3, SCREEN_HEIGHT * 2 / 3};
		SDL_SetRenderDrawColor(ren, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderDrawRect(ren, &outlineRect);
		//Draw Blue horizontal line
		SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0xFF, 0xFF);
		SDL_RenderDrawLine(ren, 0, SCREEN_HEIGHT/2, SCREEN_WIDTH, SCREEN_HEIGHT/2);
		//Draw vertica line of yellow dots
		SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0x00, 0xFF);
		for(int i = 0; i < SCREEN_HEIGHT; i+=4)
		{
		    SDL_RenderDrawPoint(ren, SCREEN_WIDTH/2, i);
		}
		//Update screen
		SDL_RenderPresent(ren);
	    }
	    SDL_DestroyRenderer(ren);
	    close(window);
	    return 0;
	}
    }
}
bool init(SDL_Window** win, SDL_Renderer** ren)
{
    //Inicia SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
	std::cout<<"SDL no pudo iniciarse, SDL_Error: "<< SDL_GetError();
	return false;
    }
    else
    {
	//Creando ventana
	*win = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
	if(*win == nullptr)
	{
	    std::cout<<"No se pudo crear la ventana, SDL_Error: " << SDL_GetError()<<std::endl;
	    SDL_Quit();
	    return false;
	}
	else
	{
	    //Inicializa el SDL_image
	    int initFlags = IMG_INIT_PNG;
	    if( !(IMG_Init(initFlags) & initFlags))
	    {
		std::cout<<"No se pudo cargar SDL_image, SDL_Error: " << IMG_GetError() << std::endl;
		return false;
	    }
	    else
	    {
		*ren = SDL_CreateRenderer(*win, -1, SDL_RENDERER_ACCELERATED);
		if(*ren == nullptr)
		{
		    std::cout<<"No se pudo crear el Renderer "<<SDL_GetError()<<std::endl;
		    return false;
		}
		else
		{
		    SDL_SetRenderDrawColor(*ren, 0xFF, 0xFF, 0xFF, 0xFF);
		    std::cout<<*win<<" "<<*ren<<std::endl;
		    return true;
		}

	    }
	}	
    }
}
bool loadMedia()
{
    bool succes = true;
    //No hay que cargar nada
    return succes;
}
void close(SDL_Window* win)
{
    SDL_DestroyWindow(win);
    win = nullptr;
    SDL_Quit();
}
