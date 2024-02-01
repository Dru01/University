#ifndef RELATIONAL_OPERATORS_H
#define RELATIONAL_OPERATORS_H

template < typename T >
class relational_operators {
	// friend inline bool operator  < (const T& lhs, const T& rhs);
	// friend inline bool operator == (const T& lhs, const T& rhs);
	friend inline bool operator != (const T& lhs, const T& rhs) { return !operator==(lhs,rhs); }
	friend inline bool operator  > (const T& lhs, const T& rhs) { return  operator <(rhs,lhs); }
	friend inline bool operator <= (const T& lhs, const T& rhs) { return !operator >(lhs,rhs); }
	friend inline bool operator >= (const T& lhs, const T& rhs) { return !operator <(lhs,rhs); }
};

#endif // !RELATIONAL_OPERATORS_H