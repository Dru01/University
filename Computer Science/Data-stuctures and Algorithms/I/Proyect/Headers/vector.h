#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include "point.h"

using namespace std;

template <typename T>
T sign(T val) {
	return (T(0) < val) - (val < T(0));
}

template < typename T >
struct implement_relational_operators {
	friend bool operator<=(const T& a, const T& b) { return a < b || a == b; }
	friend bool operator>(const T& a, const T& b) { return !(a <= b); }
	friend bool operator!=(const T& a, const T& b) { return !(a == b); }
	friend bool operator>=(const T& a, const T& b) { return !(a < b); }
};

template <class T> class CVector;

template <class T>
istream& operator>>(istream&, CVector<T>&);

template <class T>
ostream& operator<<(ostream&, CVector<T>);


template < typename T >
class CVector : public CPoint < T >, public implement_relational_operators< CVector<T> >
{
public:

	CVector(T, T);

	CVector(CPoint < T >);

	CVector();

	CVector < T > operator + (const CVector < T > temp) const
	{
		return { this->x + temp.x, this->y + temp.y };
	}

	CVector < T > operator - (const CVector < T > temp) const
	{
		return { this->x - temp.x, this->y - temp.y };
	}

	bool operator < (const CVector < T >& tmp) const
	{
		return (this->x < tmp.x || (this->x == tmp.x && this->y < tmp.y));
	}

	bool operator == (const CVector < T >& tmp) const
	{
		return (this->x == tmp.x && this->y == tmp.y);
	}

	friend istream& operator>><T>(istream&, CVector<T>&);

	friend ostream& operator<<<T>(ostream&, CVector<T>);

};

template <typename T>
istream& operator>><T>(istream& in, CVector<T>& v)
{
	in >> v.x;
	return in;
}

template <typename T>
ostream& operator<<<T>(ostream& out, CVector<T>v)
{
	out << "(" << v.x << "," << v.y << ")\n";
	return out;
}

template < typename  T >
T dot_product(CVector<T>, CVector<T>);

template < typename  T >
T cross_product(CVector<T>, CVector<T>);

template < typename  T >
T side(const CVector < T >, const CVector < T >, const CVector < T >);

template < typename  T >
T square_dist(CVector < T >, CVector < T >);

template < typename  T >
bool isbetween(CVector < T >, CVector < T >, CVector < T >);

//se que estas definiciones deberian ir en el archivo fuente de este encabezado, pero no lo logre (también la sobre carga de los streams)

template < typename  T >
T dot_product(CVector<T> a, CVector<T> b)
{
	return a.x * b.x + a.y * b.y;
}

template < typename  T >
T cross_product(CVector<T> a, CVector<T> b)
{
	return a.x * b.y - a.y * b.x;
}

template < typename  T >
T side(const CVector < T > a, const CVector < T > b, const CVector < T > c)
{
	return sign(cross_product(b - a, c - a));
}

template < typename  T >
T square_dist(CVector < T > a, CVector < T > b)
{
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

template < typename  T >
bool isbetween(CVector < T > a, CVector < T > b, CVector < T > c)
{
	if (!side(c, b, a) && dot_product(b - a, c - a) >= 0 && dot_product(b - a, c - a) > square_dist(a, b))
		return true;
	return false;
}

#endif // !VECTOR_H