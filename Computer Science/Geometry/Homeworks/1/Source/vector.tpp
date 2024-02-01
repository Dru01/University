using namespace std;

template < typename T >
CVector < T > :: CVector(T x, T y)
{
	this->x = x;
	this->y = y;
}

template < typename T >
CVector < T > :: CVector(CPoint < T > p)
{
	this->x = p.x;
	this->y = p.y;
}

template < typename T >
CVector < T > :: CVector()
{
	this->x = 0;
	this->y = 0;
}

template < typename T >
CVector < T > & CVector < T > :: operator+=(const CVector < T >& rhs)
{
	this->x+=rhs.x;
	this->y+=rhs.y;
	return *this;
}

template < typename T >
CVector < T > & CVector < T > :: operator-=(const CVector < T >& rhs)
{
	this->x-=rhs.x;
	this->y-=rhs.y;
	return *this;
}

template < typename T >
inline bool operator < (const CVector<T>& lhs, const CVector<T>& rhs)
{
	return (lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y));
}
template < typename T >
inline bool operator == (const CVector<T>& lhs, const CVector<T>& rhs)
{
	return (lhs.x == rhs.x && lhs.y == rhs.y);
}

template <typename T>
istream& operator >> (istream& in, CVector<T>& v)
{
	in >> v.x >> v.y;
	return in;
}
template <typename T>
ostream& operator << (ostream& out, const CVector<T>& v)
{
	out << v.x << " " << v.y;
	return out;
}

template <typename T>
T sign(const T val)
{
	return (T(0) < val) - (val < T(0));
}

template < typename  T >
T dot_product(const CVector<T> a, const CVector<T> b)
{
	return a.x * b.x + a.y * b.y;
}

template < typename  T >
T cross_product(const CVector<T> a, const CVector<T> b)
{
	return a.x * b.y - a.y * b.x;
}

template < typename  T >
T side(const CVector < T > a, const CVector < T > b, const CVector < T > c)
{
	return sign(cross_product(b - a, c - a));
}

template < typename  T >
T square_dist(const CVector < T > a, const CVector < T > b)
{
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

template < typename  T >
bool isbetween(const CVector < T > a, const CVector < T > b, const CVector < T > c)
{
	if (!side(c, b, a) && dot_product(b - a, c - a) >= 0 && dot_product(b - a, c - a) > square_dist(a, b))
		return true;
	return false;
}