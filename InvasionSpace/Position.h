#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
class Position
{
public:
	static constexpr auto in_place_delete = true;
	SDL_FRect* m_posDetail = nullptr;
	Position(SDL_FRect* posDetail);
	~Position();
};

