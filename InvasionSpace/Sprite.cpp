#include "Sprite.h"

Sprite::Sprite(SDL_Texture* texture, SDL_FRect* texSize)
{
	m_texture = texture;
	m_texSize = texSize;
}

Sprite::~Sprite()
{
	if (m_texSize != nullptr)
	{
		delete[] m_texSize;
		m_texSize = nullptr;
	}
	if (m_texture != nullptr)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
	}
}
