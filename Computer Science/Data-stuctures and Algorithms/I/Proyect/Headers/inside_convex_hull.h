#ifndef INSIDE_CONVEX_HULL_H
#define INSIDE_CONVEX_HULL_H

#include "point.h"
#include "vector.h"

//es para ordenar radialmente los puntos con respecto de paramA

template < typename T >
class Local
{
public:
	Local(CVector < T > paramA) { this->paramA = paramA; }
	bool operator () (const CVector < T > a, const CVector < T > b)
	{
		if (!side(a, b, paramA))
			return square_dist(a, paramA) < square_dist(b, paramA);
		return (side(a, b, paramA) > 0);
	}

	CVector < T > paramA;
};

#endif // !INSIDE_CONVEX_HULL_H#pragma once
