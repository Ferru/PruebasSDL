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
    //the renderer
    this->setRenderer(ren);
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
void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    //Set rendering space and rendering to screen
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    //Set clip rendering dimensions
    if(clip != nullptr)
    {
	std::cout<<"Clip distinto de null"<<std::endl;
	renderQuad.w = clip->w;
	renderQuad.h = clip->h;
    }
    //Render to Screen
    SDL_RenderCopyEx(ren, mTexture, clip, &renderQuad,angle,center,flip);
}
int LTexture::getWidth()
{
    return mWidth;
}
int LTexture::getHeight()
{
    return mHeight;
}
void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    //Modulate texture
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}
void LTexture::setBlendMode(SDL_BlendMode blending)
{
    //Set Blending function
    SDL_SetTextureBlendMode(mTexture, blending);
}
void LTexture::setAlpha(Uint8 alpha)
{
    //Modulat texture alpha
    SDL_SetTextureAlphaMod(mTexture, alpha);
}
void LTexture::setRenderer(SDL_Renderer* render)
{
    ren = render;
}
