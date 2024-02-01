#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#include "point.h"
#include "vector.h"
#include "angle_comparision.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>

using namespace std;
#define all(x) (x).begin(), (x).end()

template < typename T >
class CConvex_Hull
{
	protected:

	vector < CVector < T > > CH;
	vector < CVector < T > > point;
	CVector < T > tmin_point, tmax_point, aux;

	public:

	bool inside(CVector < T >);

	CConvex_Hull();

	CConvex_Hull(vector < CPoint < T > >);

	virtual void calculate() = 0;

	void precalculate();

	template < typename S >
	friend istream& operator >> (istream&, CConvex_Hull<S>&);
	
	template < typename S >
	friend ostream& operator << (ostream&, const CConvex_Hull<S>&);

};

#include "convex_hull.tpp"

#endif // !CONVEX_HULL_H