#ifndef QUICK_HULL_H
#define QUICK_HULL_H

#include "convex_hull.h"
#include <set>

using namespace std;
#define all(x) (x).begin(), (x).end()

template < typename T >
class CQuick_Hull : public CConvex_Hull < T >
{
private:

	set < CVector < T > > bucket;

public:

	void calculate();

	void quick_hull(CVector < T > , CVector < T >, int);
};

#include "quick_hull.tpp"

#endif // !QUICK_HULL_H