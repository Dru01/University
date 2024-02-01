using namespace std;

template< typename T >
CPoint<T>::CPoint()
{
	x = y = 0;
}

template < typename T >
CPoint < T > ::CPoint(T x, T y)
{
	this->x = x;
	this->y = y;
}