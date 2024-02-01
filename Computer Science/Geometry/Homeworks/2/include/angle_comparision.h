#ifndef ANGLE_COMPARISION_H
#define ANGLE_COMPARISION_H

#include "point.h"
#include "vector.h"

template < typename T >
class CAngle_Comparision
{
public:
	CAngle_Comparision(CVector < T > origin) { this->origin = origin; }
	bool operator () (const CVector < T > u, const CVector < T > v)
	{
		if (!side(origin, u, v))
			return square_dist(u, origin) < square_dist(v, origin);
		return (side(origin, u, v) > 0);
	}

	CVector < T > origin;
};

#endif // !ANGLE_COMPARISION_H