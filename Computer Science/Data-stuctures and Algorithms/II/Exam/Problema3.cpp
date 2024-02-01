#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <string.h>

#define mp make_pair
#define pb push_back
#define np next_permutation
#define all(x) (x).begin(), (x).end()
#define is_different(x, y) memcmp(x, y, sizeof(x))
#define fill(x, y) memset(x, y, sizeof(x))
#define out_range_map(x,y) ((x) < 0 || (y) < 0 || (i) == N || (j) == M)
#define optimizar_io ios_base::sync_with_stdio(false);cin.tie(NULL)

using namespace std;
const long long LN = 1e3 + 1, LK = 10, INF = 1e9;
long long N, M, pos;

template <typename T>
long long sign(T val) {
	return (T(0) < val) - (val < T(0));
}

template < typename T>
struct SPoint
{
	T x, y;

	SPoint operator + (const SPoint temp) const
	{
		return { x + temp.x, y + temp.y };
	}

	SPoint operator - (const SPoint temp) const
	{
		return { x - temp.x, y - temp.y };
	}

	friend T dot_product(SPoint<T> a, SPoint<T> b)
	{
		return a.x * b.x + a.y * b.y;
	}

	friend T cross_product(SPoint<T> a, SPoint<T> b)
	{
		return a.x * b.y - a.y * b.x;
	}

	friend T side(const SPoint < T > a, const SPoint < T > b, const SPoint < T > c)
	{
		return sign(cross_product(b - a, c - a));
	}

	friend T square_dist(SPoint < T > a, SPoint < T > b)
	{
		return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
	}
};

SPoint < long double > sort_aux;

bool compara(const SPoint < long double > a, const SPoint < long double > b)
{
	if (!side(a, b, sort_aux))
		return square_dist(a, sort_aux) < square_dist(b, sort_aux);
	return (side(a, b, sort_aux) > 0);
}

template < typename T >
class CConvex_Hull
{
private:

	SPoint < T > pr;

	bool isbetween(SPoint < T > a, SPoint < T > b, SPoint < T > c)
	{
		if (!side(c, b, a) && dot_product(b - a, c - a) >= 0 && dot_product(b - a, c - a) > square_dist(a, b))
			return true;
		return false;
	}


public:

	vector < SPoint < T > > CH;

	long double length = 0;

	bool inside(SPoint < T > a, T x)
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

	CConvex_Hull(vector < SPoint < T > > point)
	{

		pr = { INF, INF };

		for (int i = 0; i < N; i++)
		{
			if (pr.y > point[i].y || (pr.y == point[i].y && pr.x > point[i].x))
				pr = point[i];
		}

		sort_aux = pr;

		sort(all(point), compara);

		for (int i = 0; i < N; i++)
		{
			while (CH.size() > 1 && side(CH.back(), point[i], CH[CH.size() - 2]) <= 0)
				CH.pop_back();
			CH.push_back(point[i]);
		}

		for (int i = 0; i < CH.size(); i++)
			length += (long double)sqrt(square_dist(CH[i], CH[(i - 1 + CH.size()) % CH.size()]));

	}

};


int main()
{
	optimizar_io;

	cin >> N;

	vector < SPoint < long double > > point(N);
	for (int i = 0; i < N; i++)
		cin >> point[i].x >> point[i].y;

	CConvex_Hull < long double > rope(point);

	cout << rope.length;

	return 0;
}