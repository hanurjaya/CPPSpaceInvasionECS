#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
class Position
{
public:
	SDL_FRect* m_posDetail;
	Position(SDL_FRect* posDetail);
};

