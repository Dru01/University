#ifndef VECTOR_H
#define VECTOR_H

#include "point.h"
#include "arithmetic_operators.h"
#include "relational_operators.h"
#include <iostream>
#include <fstream>

using namespace std;

template < typename T >
class CVector : public CPoint < T >, public relational_operators < CVector < T > >, public arithmetic_operators < CVector < T > >
{
public:

	CVector(T, T);

	CVector(CPoint < T >);

	CVector();

	CVector < T > & operator+=(const CVector < T >&);

	CVector < T > & operator-=(const CVector < T >&);

	template < typename S >
	friend inline bool operator  < (const CVector < S >&, const CVector < S >&);
	template < typename S >
	friend inline bool operator == (const CVector < S >&, const CVector < S >&);

	template < typename S >
	friend istream& operator >> (istream&, CVector<S>&);
	template < typename S >
	friend ostream& operator << (ostream&, const CVector<S>&);

};

template < typename  T >
T dot_product(const CVector<T>,const CVector<T>);

template < typename  T >
T cross_product(const CVector<T>, const CVector<T>);

template < typename  T >
T side(const CVector < T >, const CVector < T >, const CVector < T >);

template < typename  T >
T square_dist(const CVector < T >, const CVector < T >);

template < typename  T >
bool isbetween(const CVector < T >, const CVector < T >, const CVector < T >);

template <typename T>
T sign(T val);

#include "vector.tpp"

#endif // !VECTOR_H