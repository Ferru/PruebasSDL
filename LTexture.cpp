#include "LTexture.hpp"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
//Constructor
LTexture::LTexture()
{
    //Inicializando
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}
//Destructor
LTexture::~LTexture()
{
    //Deallocates
    free();
}
bool LTexture::loadFromFile(std::string path, SDL_Renderer* ren)
{
    //Se eliminan texturas ya existentes
    free();
    //the final texture
    SDL_Texture* newTexture = nullptr;
    //Se carga la imagen
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == nullptr)
    {
	std::cout<<"Inpacaz de cargar la imagen " << path << "! SDL_image Error " << IMG_GetError() << "\n";
    }
    else
    {
	//Color key image
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format,0,0xFF,0xFF));
	//creando textura de surface
	newTexture = SDL_CreateTextureFromSurface(ren, loadedSurface);
	if(newTexture == nullptr)
	{
	    std::cout<<"No se pudo crear textura de "<<path <<"! SDL Error: " << SDL_GetError() << std::endl;
	}
	else
	{
	    mWidth = loadedSurface->w;
	    mHeight = loadedSurface->h;
	}
	//Liberamos el surface
	SDL_FreeSurface(loadedSurface);
	
    }
    //Return success
    mTexture = newTexture;
    return mTexture != nullptr;
}
void LTexture::free()
{
    //Libera textura si existe
    if(mTexture != nullptr)
    {
	SDL_DestroyTexture(mTexture);
	mTexture = nullptr;
	mWidth = 0;
	mHeight = 0;
    }
}
void LTexture::render(SDL_Renderer* ren, int x, int y)
{
    //Set rendering space and rendering to screen
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    SDL_RenderCopy(ren, mTexture, NULL, &renderQuad);
}
int LTexture::getWidth()
{
    return mWidth;
}
int LTexture::getHeight()
{
    return mHeight;
}
