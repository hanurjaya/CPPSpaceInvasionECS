#include "Position.h"

Position::Position(SDL_FRect* posDetail)
{
	m_posDetail = posDetail;
}

Position::~Position()
{
	if (m_posDetail != nullptr)
	{
		delete[] m_posDetail;
		m_posDetail = nullptr;
	}
}
