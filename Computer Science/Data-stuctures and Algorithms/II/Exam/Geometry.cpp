	#include <iostream>
	#include <algorithm>
	#include <vector>
	#include <queue>
	#include <set>
	#include <map>
	#include <string>
	#include <string.h>

	#define mp make_pair
	#define pb push_back
	#define np next_permutation
	#define all(x) (x).begin(), (x).end()
	#define is_different(x, y) memcmp(x, y, sizeof(x))
	#define fill(x, y) memset(x, y, sizeof(x))
	#define out_range_map(x,y) ((x) < 0 || (y) < 0 || (i) == N || (j) == M)
	#define optimizar_io ios_base::sync_with_stdio(false);cin.tie(NULL);

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

		friend long long side(const SPoint < long long > a, const SPoint < long long > b, const SPoint < long long > c)
		{
			return sign(cross_product(b - a, c - a));
		}

		friend long long square_dist(SPoint < long long > a, SPoint < long long > b)
		{
			return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
		}
	};

	vector < SPoint < long long > > point[2];
	SPoint < long long > sort_aux;

	bool compara(const SPoint < long long > a, const SPoint < long long > b)
	{
		if (!side(a, b, sort_aux))
			return square_dist(a, sort_aux) < square_dist(b, sort_aux);
		return (side(a, b, sort_aux) > 0);
	}

	template < typename T >
	class CConvex_Hull
	{
	private:

		vector < SPoint < T > > CH;

		SPoint < T > pr;


		bool isbetween(SPoint < T > a, SPoint < T > b, SPoint < T > c)
		{
			if (!side(c, b, a) && dot_product(b - a, c - a) >= 0 && dot_product(b - a, c - a) > square_dist(a, b))
				return true;
			return false;
		}


	public:

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

		CConvex_Hull(T x)
		{


			pr = { INF, INF };

			for (int i = 0; i < N; i++)
			{
				if (pr.y > point[x][i].y || (pr.y == point[x][i].y && pr.x > point[x][i].x))
					pr = point[x][i];
			}

			sort_aux = pr;

			sort(all(point[x]), compara);

			for (T i = 0; i < N; i++)
			{
				while (CH.size() > 1 && side(CH.back(), point[x][i], CH[CH.size() - 2]) <= 0)
					CH.pop_back();
				CH.push_back(point[x][i]);
			}
		}

	};


	void read(long long x)
	{
		SPoint < long long > tmp;
		for (long long i = 0; i < N; i++)
		{
			cin >> tmp.x >> tmp.y;
			point[x].push_back(tmp);
		}
	}

	long long solve(long long x)
	{
		CConvex_Hull < long long > team(x);
		long long ans = 0;
		for (long long i = 0; i < N; i++)
			if (team.inside(point[(x + 1) % 2][i], x))
				ans++;
		return ans;
	}

	int main()
	{
		optimizar_io

			cin >> N;

		read(0);
		read(1);

		cout << solve(0) << " " << solve(1);

		return 0;
	}