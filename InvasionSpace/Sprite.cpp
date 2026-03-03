#include "Sprite.h"

Sprite::Sprite(SDL_Texture* texture, SDL_FRect* texSize)
{
	m_texture = texture;
	m_texSize = texSize;
}
