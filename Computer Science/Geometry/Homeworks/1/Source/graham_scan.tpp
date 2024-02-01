using namespace std;

template < typename T >
void CGraham_Scan < T > :: calculate()
{
	sort(all(this->point), CAngle_Comparision<T>(this->tmin_point));

	for (T i = 0; i < this->point.size(); i++)
	{
		this->aux = (CVector < T >) (*(new CVector < T >(this->point[i])));
		while (this->CH.size() > 1 && side(this->CH.back(), this->aux, this->CH[this->CH.size() - 2]) <= 0)
			this->CH.pop_back();
		this->CH.push_back(this->aux);
	}
}