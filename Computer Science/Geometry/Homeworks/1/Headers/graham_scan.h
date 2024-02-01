#ifndef GRAHAM_SCAN_H
#define GRAHAM_SCAN_H

#include "convex_hull.h"

using namespace std;
#define all(x) (x).begin(), (x).end()

template < typename T >
class CGraham_Scan : public CConvex_Hull < T >
{
	private:

	public:

	void calculate();

};

#include "graham_scan.tpp"

#endif // !GRAHAM_SCAN_H