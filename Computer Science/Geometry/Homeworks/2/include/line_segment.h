#ifndef LINE_SEGMENT_H
#define LINE_SEGMENT_H

#include "vector.h"
#include "line.h"

template < typename T >
class CLine_Segment : CLine<T>
{
    public:

    CVector < T > tl, tr;

    CLine_Segment();

    CLine_Segment(CVector < T >, CVector <T>);

    CLine_Segment(CPoint < T >, CPoint <T>);

    bool inside(CVector <T>);
};

double EPS = 1e-9;

template< typename T>
inline bool intersect_1d(T a, T b, T c, T d)
{
    if (a > b)
        swap(a, b);
    if (c > d)
        swap(c, d);
    return max(a, c) <= min(b, d) + EPS;
}

template <typename T> 
T det(T a, T b, T c, T d)
{
    return a * d - b * c;
}

template <typename T> 
inline bool betw(T l, T r, T x)
{
    return min(l, r) <= x + EPS && x <= max(l, r) + EPS;
}

template < typename  T >
pair < bool, CLine_Segment <T> > intersect(CLine_Segment < T > p, CLine_Segment < T > q)
{
    CLine_Segment <T> ans;
    if (
        !intersect_1d(p.tl.x, p.tr.x, q.tl.x, q.tr.x) ||
        !intersect_1d(p.tl.y, p.tr.y, q.tl.y, q.tr.y)
    )
        return {false, ans};
    double zn = det(p.a, p.b, q.a, q.b);
    if (abs(zn) < EPS)
    {
        if (abs(p.dist(q.tl)) > EPS || abs(q.dist(p.tl)) > EPS)
            return {false, ans};
        if (p.tr < p.tl)
            swap(p.tl, p.tr);
        if (q.tr < q.tl)
            swap(q.tl, q.tr);
        return { true, max(p.tl, q.tl), min(p.tr, q.tr) };
    }
    else
    {
        ans.tl.x = ans.tr.x = -det(p.c, p.b, q.c, q.b) / zn;
        ans.tl.y = ans.tr.y = -det(p.a, p.c, q.a, q.c) / zn;
        return {
            betw(p.tl.x, p.tr.x, ans.tl.x) &&
            betw(p.tl.y, p.tr.y, ans.tl.y) &&
            betw(q.tl.x, q.tr.x, ans.tl.x) &&
            betw(q.tl.y, q.tr.y, ans.tl.y),
            ans
        };
    }
}

template < typename T >
CLine_Segment < T > :: CLine_Segment(CPoint < T > tl, CPoint < T > tr)
{
    CLine_Segment(CVector <T> (tl), CVector <T> (tr));
}

template < typename T >
CLine_Segment < T > :: CLine_Segment(CVector < T > tl, CVector < T > tr) : tl(tl), tr(tr), CLine<T>(tl,tr){}

template < typename T >
CLine_Segment < T > :: CLine_Segment()
{
    CLine_Segment(CVector<T>(0,0), CVector<T>(0,0));
}

template < typename T >
bool CLine_Segment < T > :: inside(CVector <T> p)
{
    return cross_product(tl,tr,p) == 0 && dot_product(p - tl, p-tr) < 0;
}

#endif // !LINE_SEGMENT_H