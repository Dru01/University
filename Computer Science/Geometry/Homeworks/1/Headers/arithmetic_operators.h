#ifndef ARITHMETIC_OPERATORS_H
#define ARITHMETIC_OPERATORS_H

template < typename T >
class arithmetic_operators {
	// X& operator+=(const X& rhs)
	// {
	// 	// actual addition of rhs to *this
	// 	return *this;
	// }
	// X& operatoR-=(const X& rhs)
	// {
	// 	// actual addition of rhs to *this
	// 	return *this;
	// }
	friend T operator+(T lhs, const T& rhs)
    {
        lhs += rhs;
        return lhs;
    }
	friend T operator-(T lhs, const T& rhs)
    {
        lhs -= rhs;
        return lhs;
    }
};

#endif // !ARITHMETIC_OPERATORS_H