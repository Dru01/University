#include "vector.h"

template < typename T >
CVector < T > :: CVector(T x, T y)
{
	this->x = x;
	this->y = y;
}

template < typename T >
CVector < T > :: CVector(CPoint < T > p)
{
	this->x = p.x;
	this->y = p.y;
}

template < typename T >
CVector < T > :: CVector()
{
	this->x = 0;
	this->y = 0;
}

template class CVector < int >;