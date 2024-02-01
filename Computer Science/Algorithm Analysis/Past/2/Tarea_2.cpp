#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#define ll long long
#define all(x) (x).begin(), (x).end()
#define fill(x, y) memset(x, y, sizeof(x))
#define optimizar_io ios_base::sync_with_stdio(false);cin.tie(NULL)

using namespace std;
int N, M, Q;

template < typename T >
struct SPoint
{
	T x, y;

	bool operator <= (const SPoint& tmp) const
	{
		return (y <= tmp.y);
	}

	bool operator < (const SPoint& tmp) const
	{
		return (x < tmp.x) || (x == tmp.x && y < tmp.y);
	}

	friend ostream& operator << (ostream& out, const SPoint& p)
	{
		out << "(" << p.x << "," << p.y << ")";
		return out;
	}
	friend istream& operator >> (istream& in, SPoint& p)
	{
		in >> p.x >> p.y;
		return in;
	}
};

map < SPoint < int >, int > domain;

vector < SPoint < int > > merge(vector < SPoint < int > > l, vector < SPoint < int > > r)
{
	vector < SPoint < int > > point(l.size() + r.size());
	ll pos = 0;
	vector < SPoint < int > >::iterator pl = l.begin(), pr = r.begin();
	while (pl != l.end() || pr != r.end())
	{
		if ((pl != l.end() && *pl <= *pr) || pr == r.end())
		{
			point[pos++] = *pl;
			pl++;
		}
		else
		{
			point[pos++] = *pr;
			pr++;
		}
	}
	return point;
}

void dominate(vector < SPoint < int > > l, vector < SPoint < int > > r)
{
	vector < SPoint < int > >::iterator pl = l.begin(), pr = r.begin();
	while (pl != l.end() || pr != r.end())
	{
		if ((pl != l.end() && *pl <= *pr) || pr == r.end())
		{
			domain[*pl] += r.end() - pr;
			pl++;
		}
		else
			pr++;
	}
}

pair < vector < SPoint < int > >, vector < SPoint < int > > > divide(vector < SPoint < int > > point)
{
	vector < SPoint < int > > pl(point.begin(), point.begin() + point.size() / 2);
	vector < SPoint < int > > pr(point.begin() + point.size() / 2, point.end());
	return { pl, pr };
}

vector < SPoint < int > > conquere(vector < SPoint < int > > point)
{
	if (point.size() == 1)
		return point;
	pair < vector < SPoint < int > >, vector < SPoint < int > > > g = divide(point);
	vector < SPoint < int > > pl = conquere(g.first);
	vector < SPoint < int > > pr = conquere(g.second);

	dominate(pl, pr);

	point = merge(pl, pr);

	return point;
}

int main()
{
	optimizar_io;

	cin >> N;

	vector < SPoint < int > > point(N), org_point;

	for (int i = 0; i < N; i++)
		cin >> point[i];

	org_point = point;

	sort(all(point));

	conquere(point);

	for (int i = 0; i < N; i++)
		cout << org_point[i] << " " << domain[org_point[i]] << '\n';

	return 0;
}