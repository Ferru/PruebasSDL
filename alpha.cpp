#include "SDL.h"
#include <iostream>
#include "SDL_image.h"
#include <string>
#include "LTexture.hpp"
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
//Inicia SDL y crea una ventana
bool init(SDL_Window** win, SDL_Renderer** ren);
//Carga los medios 
bool loadMedia(LTexture* texture, SDL_Renderer* ren);
//Libera memoria y recursos, además de apagar SDL
void close(SDL_Window *win);
//CArga individualmente una imagen
int main(int argc, char** arcv)
{
    SDL_Renderer* ren = nullptr;
    SDL_Window* window = nullptr;
    //Scene Textures
    LTexture arrowTexture;
    bool isInit = init(&window, &ren);
    std::cout<<window<<" " << ren <<std::endl;
    if(!isInit)
    {
	return 1;
    }
    else
    {
	bool test = loadMedia(&arrowTexture, ren);
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
	    //Modulation components
	    Uint8 r = 255;
	    Uint8 g = 255;
	    Uint8 b = 255;
	    Uint8 a = 255;
	    //Angle of rotation
	    double degrees = 0;
	    //Flip type
	    SDL_RendererFlip flipType = SDL_FLIP_NONE;
	    //Mientras no se cierre la aplicación
	    while(!quit)
	    {
		//Manejando eventos de la cola
		while(SDL_PollEvent(&e) != 0)
		{
		    //Se detecta el evento de cierre
		    if(e.type == SDL_QUIT)
		    {
			quit = true;
		    }
		    else if(e.type == SDL_KEYDOWN)
		    {
			switch(e.key.keysym.sym)
			{
			case SDLK_q:
			    r += 32;
			    break;
			case SDLK_o:
			    g += 32;
			    break;
			case SDLK_e:
			    b += 32;
			    break;
			case SDLK_a:
			    r -= 32;
			    break;
			case SDLK_m:
			    g -= 32;
			    break;
			case SDLK_d:
			    b -= 32;
			    break;
			case SDLK_w:
			    if(a + 32 > 255)
			    {
				a = 255;
			    }
			    else
			    {
				a += 32;
			    }
			    break;
			case SDLK_s:
			    if(a - 32 <= 0)
			    {
				a = 0;
			    }
			    else
			    {
				a -= 32;
			    }
			    break;
			case SDLK_r:
			    degrees -= 60;
			    break;
			case SDLK_l:
			    degrees += 60;
			    break;
			case SDLK_h:
			    flipType = SDL_FLIP_HORIZONTAL;
			    break;
			case SDLK_z:
			    flipType = SDL_FLIP_NONE;
			    break;
			case SDLK_v:
			    flipType = SDL_FLIP_VERTICAL;
			    break;  
			    
			}
		    
			
		    }
		   
		}
		//Limpiando el renderer
		SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0xFF);
		SDL_RenderClear(ren);
		//Pintando frente
		arrowTexture.setColor(r,g,b);
		arrowTexture.setAlpha(a);
		arrowTexture.render((SCREEN_WIDTH - arrowTexture.getWidth())/2, (SCREEN_HEIGHT - arrowTexture.getHeight())/2, NULL, degrees, NULL,flipType);
		SDL_RenderPresent(ren);
	    }
	}
	//Liberando recursos
	arrowTexture.free();
	SDL_DestroyRenderer(ren);
	close(window);
	return 0;
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
//Se cargan todas las imagenes
bool loadMedia(LTexture* texture, SDL_Renderer* ren)
{
    //Se carga surface por defecto
    bool success =  true;
    //Cargando textura
    if(!texture->loadFromFile("images/pointer.png", ren))
    {
	std::cout<<"No se pudo cargar la textura: " <<std::endl;
	success = false;
    }
    else
    {
	texture->setBlendMode(SDL_BLENDMODE_BLEND);
    }
    return success;
} 
void close(SDL_Window* win)
{
    SDL_DestroyWindow(win);
    win = nullptr;
    IMG_Quit();
    SDL_Quit();
    
}
//Optimizar la carga del surface
SDL_Surface* loadSurface(std::string path, SDL_Surface* screenSurface)
{
    //Surface optimizado
    SDL_Surface* optimizedSurface = nullptr;
    //Carga el surface del path especificado
    SDL_Surface* loadedSurface = nullptr;
    loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == nullptr)
    {
	std::cout<<"Incapaz de abrir la imagen " << path <<" SDL Error " << IMG_GetError() << std::endl;
    }
    else
    {
	optimizedSurface = SDL_ConvertSurface(loadedSurface,screenSurface->format, 0);
	if(optimizedSurface == nullptr)
	{
	    std::cout<<"Incapaz de optimizar imagen "<< path <<" SDL Error: " << SDL_GetError()<<std::endl; 
	}
	//Liberando surface cargada
	SDL_FreeSurface(loadedSurface);
    }
    return optimizedSurface;
}
SDL_Texture* loadTexture(std::string path, SDL_Renderer* ren)
{
    //Textura a cargar
    SDL_Texture* newTexture = nullptr;
    //Carga el surface del path especificado
    SDL_Surface* loadedSurface = nullptr;
    loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == nullptr)
    {
	std::cout<<"Incapaz de abrir la imagen " << path <<" SDL Error " << IMG_GetError() << std::endl;
    }
    else
    {
	newTexture = SDL_CreateTextureFromSurface(ren, loadedSurface);
	if(newTexture == nullptr)
	{
	    std::cout<<"Incapaz de crear textura "<< path <<" SDL Error: " << SDL_GetError()<<std::endl; 
	}
	//Liberando surface cargada
	SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}
