#include <SDL2/SDL.h>
#include <iostream>
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};
//Inicia SDL y crea una ventana
SDL_Window* init();
//Carga los medios
bool loadMedia(SDL_Surface** surfaces, SDL_Surface* screenSurface);
//Libera memoria y recursos, además de apagar SDL
void close(SDL_Window *win);
//CArga individualmente una imagen
SDL_Surface* loadSurface(std::string path, SDL_Surface* screenSurface);
int main(int argc, char** arcv)
{
    //Surface de la ventana
    SDL_Surface* screenSurface = nullptr;
    //Surface actual 
    SDL_Surface* currentSurface = nullptr;
    SDL_Window* window = nullptr;
    //LAs imagenes correspondientes a las teclas
    SDL_Surface* keyPresSurfaces[KEY_PRESS_SURFACE_TOTAL];
    window = init();
    if(window == nullptr)
    {
	return 1;
    }
    else
    {
	//Saca el surface	
	screenSurface = SDL_GetWindowSurface(window);
	bool test = loadMedia(keyPresSurfaces, screenSurface);
	if(!test)
	{
	    return 1;
	}
	else
	{
	    //Main loog flag
	    bool quit = false;
	    //Manejador de eventos
	    SDL_Event e;
	    //Surface por defecto
	    currentSurface = keyPresSurfaces[KEY_PRESS_SURFACE_DEFAULT];
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
			case SDLK_UP:
			currentSurface = keyPresSurfaces[KEY_PRESS_SURFACE_UP];
			break;
			case SDLK_DOWN:
			currentSurface = keyPresSurfaces[KEY_PRESS_SURFACE_DOWN];
			break;
			case SDLK_LEFT:
			currentSurface = keyPresSurfaces[KEY_PRESS_SURFACE_LEFT];
			break;
			case SDLK_RIGHT:
			currentSurface = keyPresSurfaces[KEY_PRESS_SURFACE_RIGHT];
			break;
			default:
			currentSurface = keyPresSurfaces[KEY_PRESS_SURFACE_DEFAULT];
			break;
			}
		    }
		}
		//Llena el surface
		//Stretching the surface
		SDL_Rect stretchRect;
		stretchRect.x = 0;
		stretchRect.y = 0;
		stretchRect.w = SCREEN_WIDTH;
		stretchRect.h = SCREEN_HEIGHT;
		SDL_BlitScaled(currentSurface, NULL, screenSurface, &stretchRect);
		//Actualiza surface
		SDL_UpdateWindowSurface(window);
	    }
	}
	//SDL_FreeSurface(currentSurface);
	int j = 0;
	while(j < KEY_PRESS_SURFACE_TOTAL)
	{
	    SDL_FreeSurface(keyPresSurfaces[j]);
	    j++;
	}
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
//Se cargan todas las imagenes
bool loadMedia(SDL_Surface** surfaces, SDL_Surface* screenSurface)
{
    //Se carga surface por defecto
    bool success =  true;
    surfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("images/press.bmp", screenSurface);
    if(surfaces[KEY_PRESS_SURFACE_DEFAULT] == nullptr)
    {
	std::cout<<"No se puede cargar la imagen por defecto" <<std::endl;
	success = false;
    }
    //Cargando images para tecla arriba
    surfaces[KEY_PRESS_SURFACE_UP] = loadSurface("images/up.bmp", screenSurface);
    if(surfaces[KEY_PRESS_SURFACE_UP] == nullptr)
    {
	std::cout<<"No se puede cargar la imagen para tecla arriba " <<std::endl;
	success = false;
    }    
    //Cargando imagen para tecla abajo
    surfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("images/down.bmp", screenSurface);
    if(surfaces[KEY_PRESS_SURFACE_DOWN] == nullptr)
    {
	std::cout<<"No se puede cargar la imagen para tecla abajo " <<std::endl;
	success = false;
    }
    //Imagen para la izquierda
    surfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("images/left.bmp", screenSurface);
    if(surfaces[KEY_PRESS_SURFACE_LEFT] == nullptr)
    {
	std::cout<<"No se puede cargar la imagen para tecla izquierda " <<std::endl;
	success = false;
    }
    //CArgando imagen para la derecha
    surfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("images/right.bmp", screenSurface);
    if(surfaces[KEY_PRESS_SURFACE_RIGHT] == nullptr)
    {
	std::cout<<"No se puede cargar la imagen por derecha" <<std::endl;
	success = false;
    }
    std::cout<<"Se han creado los surfaces? "<< success<<std::endl; 
    return success;
}
void close(SDL_Window* win)
{
    SDL_DestroyWindow(win);
    win = nullptr;
    SDL_Quit();
}
//Optimizar la carga del surface
SDL_Surface* loadSurface(std::string path, SDL_Surface* screenSurface)
{
    //Surface optimizado
    SDL_Surface* optimizedSurface = nullptr;
    //Carga el surface del path especificado
    SDL_Surface* loadedSurface = nullptr;
    loadedSurface = SDL_LoadBMP(path.c_str());
    if(loadedSurface == nullptr)
    {
	std::cout<<"Incapaz de abrir la imagen " << path <<" SDL Error " << SDL_GetError() << std::endl;
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
