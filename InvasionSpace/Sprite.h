#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
class Sprite
{
public:
	SDL_Texture* m_texture;
	SDL_FRect* m_texSize;
	Sprite(SDL_Texture* texture, SDL_FRect* texSize);
};



