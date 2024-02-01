#ifndef POINT_H
#define POINT_H

template < typename T>
class CPoint
{
public:
	T x, y;

	CPoint < T >();

	CPoint < T >(T, T);
};

#include "point.tpp"
#endif // !POINT_H