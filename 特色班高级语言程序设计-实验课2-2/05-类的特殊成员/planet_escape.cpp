#include<iostream>
#include<cmath>
#include<vector>
using namespace std;
class universe
{
public:
	const double G;
	universe(double g) :G(g)
	{};
};
class planet
{
public:
	double m;
	double r;
	double vscape;
};
class spaceship
{
public:
	double a;
	double vmax;
};
int main()
{
	double G,t;
	vector<double> v;
	int n,m=0;
	planet Xenon, Folcon;
	cin >> G;
	universe uni(G);
	cin >> Xenon.m >> Xenon.r >> Folcon.m >> Folcon.r >> t;
	Xenon.vscape = sqrt(2 * G * Xenon.m / Xenon.r);
	cin >> n;
	spaceship* p;
	p = new spaceship[n];
	for (int i = 0; i < n; i++)
	{
		cin >> p[i].a >> p[i].vmax;
	}
	for (int i = 0; i < n; i++)
	{
		if (min(p[i].a * t, p[i].vmax) <= Xenon.vscape) continue;
		else
		{
			double distance;
			m++;
			if (p[i].a * t <= p[i].vmax)
			{
				distance = 0.5 * p[i].a * t * t;
				v.push_back(distance);
			}
			else
			{
				double t1 = p[i].vmax / p[i].a;
				distance = 0.5 * p[i].a * t1 * t1 + p[i].vmax * (t - t1);
				v.push_back(distance);
			}
		}
	}
	cout << m<<endl;
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i];
		if (i != v.size() - 1)cout << endl;
	}
	return 0;
}