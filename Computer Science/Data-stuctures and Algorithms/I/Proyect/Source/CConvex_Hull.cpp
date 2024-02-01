#include "geometry.h"

template < typename T >
void CConvex_Hull < T > :: imp()
{
	cout << "The Points of the Convex Hull are:\n";
	for (auto& x : CH)
	{
		cout << x;
	}
	cout << "\n";
}

template < typename T >
bool CConvex_Hull < T > :: inside(CVector < T > a, T x)
{
	T tmax = CH.size(), tmin = 0, prom;
	while (tmax - tmin > 1)
	{
		prom = (tmax + tmin) / 2;
		if (side(CH[prom], a, pr) <= 0)
			tmax = prom;
		else
			tmin = prom;
	}
	if (tmax == 1 || tmin == CH.size() - 1)
	{
		if (tmax != CH.size() && isbetween(pr, a, CH[tmax]))
			return true;
		if (tmin != 0 && isbetween(pr, a, CH[tmin]))
			return true;
		return false;
	}
	if (side(CH[tmax], a, CH[tmin]) >= 0)
		return true;
	return false;
}

template < typename T >
CConvex_Hull < T > :: CConvex_Hull(vector < CPoint < T > >  point)
{
	pr = *(new CVector < T >(100, 100));

	for (int i = 0; i < point.size(); i++)
	{
		aux = (CVector < T >) (*(new CVector < T >(point[i])));
		pr = min(aux, pr);
	}

	sort_aux = pr;

	sort(all(point), Local<T>(sort_aux));

	for (T i = 0; i < point.size(); i++)
	{
		aux = (CVector < T >) (*(new CVector < T >(point[i])));
		while (CH.size() > 1 && side(CH.back(), aux, CH[CH.size() - 2]) <= 0)
			CH.pop_back();
		CH.push_back(aux);
	}
}

template class CConvex_Hull < int >;