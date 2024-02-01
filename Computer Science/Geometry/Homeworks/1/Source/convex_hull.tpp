using namespace std;

template < typename T >
CConvex_Hull < T > :: CConvex_Hull(){
}

template < typename T >
void CConvex_Hull < T > :: precalculate()
{
	if (!point.size() )
		return;
	
	tmax_point = tmin_point = CVector < T >(point[0]);

	for (int i = 0; i < point.size(); i++)
	{
		aux = CVector < T >(point[i]);
		tmin_point = min(aux, tmin_point);
		tmax_point = max(aux, tmax_point);
	}
}

template < typename T >
CConvex_Hull < T > :: CConvex_Hull(vector < CPoint < T > > point){
	
	this->point=point;

	precalculate();

	calculate();
}

template <typename T>
istream& operator >> (istream& in, CConvex_Hull<T>& ch)
{
	CVector < T > v;
	while(in >> v)
		ch.point.push_back(v);
	ch.precalculate();
	ch.calculate();
	return in;
}

template <typename T>
ostream& operator << (ostream& out, const CConvex_Hull<T>& v)
{
	for (auto& x : v.CH)
		out << x << "\n";
	return out;
}

template < typename T >
bool CConvex_Hull < T > :: inside(CVector < T > a)
{
	T tmax = CH.size(), tmin = 0, prom;
	while (tmax - tmin > 1)
	{
		prom = (tmax + tmin) / 2;
		if (side(CH[prom], a, tmin_point) <= 0)
			tmax = prom;
		else
			tmin = prom;
	}
	if (tmax == 1 || tmin == CH.size() - 1)
	{
		if (tmax != CH.size() && isbetween(tmin_point, a, CH[tmax]))
			return true;
		if (tmin != 0 && isbetween(tmin_point, a, CH[tmin]))
			return true;
		return false;
	}
	if (side(CH[tmax], a, CH[tmin]) >= 0)
		return true;
	return false;
}