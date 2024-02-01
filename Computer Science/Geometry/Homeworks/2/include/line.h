#ifndef LINE_H
#define LINE_H

template <typename T>
class CLine {
    T a, b, c;
    CLine() {}
    CLine(T a, T b, T c) : a(a), b(b), c(c) {}
    CLine(CPoint<T> p, CPoint<T> q)
    {
        a = p.y - q.y;
        b = q.x - p.x;
        c = -a * p.x - b * p.y;
        norm();
    }

    void norm()
    {
        double z = sqrt(a * a + b * b);
        if (abs(z) > 1e-9)
            a /= z, b /= z, c /= z;
    }

    double dist(CPoint<T> p) const { return a * p.x + b * p.y + c; }
};

#endif // !LINE_H