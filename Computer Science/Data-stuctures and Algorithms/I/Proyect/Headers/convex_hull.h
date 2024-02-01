#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#include "point.h"
#include "vector.h"
#include "inside_convex_hull.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>

using namespace std;
#define all(x) (x).begin(), (x).end()

template < typename T >
class CConvex_Hull
{
private:

	vector < CVector < T > > CH;
	CVector < T > aux;
	CVector < T > pr;
	CVector < T > sort_aux;

public:

	void imp();

	bool inside(CVector < T >, T);

	CConvex_Hull(vector < CPoint < T > >);

};

#endif // !CONVEX_HULL_H