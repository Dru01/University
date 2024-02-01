using namespace std;

template < typename T >
void CQuick_Hull < T > :: calculate()
{

	quick_hull(this->tmin_point, this->tmax_point, 1);
    quick_hull(this->tmin_point, this->tmax_point, -1);

	this->CH.reserve(bucket.size ());
    copy(bucket.begin (), bucket.end (), back_inserter (this->CH));
    sort(all(this->CH), CAngle_Comparision<T>(this->tmin_point));
}

template < typename T >
void CQuick_Hull < T > :: quick_hull(CVector < T > tl_point, CVector < T > tr_point, int orient)
{
    int ind = -1, tmax_dist = 0;

    for (int i=0; i<this->point.size(); i++)
    {
        if (side(tl_point, tr_point, this->point[i]) != orient)
            continue;
        int dist = abs(cross_product(tr_point-tl_point, this->point[i]-tl_point));
        if (dist > tmax_dist)
        {
            ind = i;
            tmax_dist = dist;
        }
    }

	if (ind == -1)
    {
        bucket.insert(tl_point);
        bucket.insert(tr_point);
        return;
    }

    quick_hull(this->point[ind], tl_point, -side(this->point[ind], tl_point, tr_point));
    quick_hull(this->point[ind], tr_point, -side(this->point[ind], tmax_point, tl_point));
}