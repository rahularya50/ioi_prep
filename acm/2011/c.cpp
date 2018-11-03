#include "bits/stdc++.h"
#define X real()
#define Y imag()
using namespace std;
typedef complex<double> pt;

const double eps = 1e-6;
const double inf = 1e9;

int T, N;

double dot(pt a, pt b) {
	return (conj(a)*b).X;
}

double cross(pt a, pt b) {
	return (conj(a)*b).Y;
}

double ccw(pt a, pt b, pt c) {
	return cross(b-a, c-a);
}

vector<pt> hull(vector<pt> a) {
	sort(a.begin(), a.end(), [](pt a, pt b) {
		return a.X == b.X? a.Y < b.Y : a.X < b.X;
	});
	vector<pt> uh;
	for(pt p: a) {
		while(uh.size() >= 2 && ccw(uh[uh.size()-2], uh.back(), p) > -eps) {
			uh.pop_back();
		}
		uh.push_back(p);
	}
	uh.pop_back();
	vector<pt> lh;
	for(pt p: a) {
		while(lh.size() >= 2 && ccw(lh[lh.size()-2], lh.back(), p) < eps) {
			lh.pop_back();
		}
		lh.push_back(p);
	}
	reverse(lh.begin(), lh.end());
	lh.pop_back();
	uh.insert(uh.end(), lh.begin(), lh.end());
	return uh;
}

double dist(pt a, pt b, pt u) {
	return abs(dot(b-a, u));
}

void pp(vector<pt> a) {
	for(pt p: a) {
		printf("(%.3lf %.3lf) ", p.X, p.Y);
	}
	puts("");
}

void solve(int test) {
	scanf("%d", &N);
	vector<pt> a;
	for(int i = 0; i < N; i++) {
		double x, y;
		scanf("%lf%lf", &x, &y);
		a.push_back(pt(x, y));
	}
	a = hull(a);
	N = a.size();
	puts("hello");fflush(stdout);
	double ans = inf;
	pp(a);
	if(N <= 2) {
		ans = 0;
	} else {
		pt bestu, bestv;
		for(int i = 0; i < N; i++) {
			//printf("i = %d\n", i);fflush(stdout);
			pt u = a[(i+1)%N] - a[i];
			u = u/abs(u)*pt(0, 1);
			double d1 = 0;
			for(int j = 0; j < N; j++) {
				d1 = max(d1, dist(a[i], a[j], u));
			}
			pt v1 = u*d1;
			double d2 = inf;
			pt v2;
			for(int j = (i+1)%N, k = (i+1)%N; j != i; j = (j+1)%N) {
				//printf("j = %d\n", j);fflush(stdout);
				pt v = a[(j+1)%N] - a[j];
				v = v/abs(v)*pt(0, 1);
				if(abs(cross(u, v)) < eps) {
					continue;
				}
				while(dist(a[j], a[(k+1)%N], v) > dist(a[j], a[k], v) - eps) {
					k = (k+1)%N;
				}
				//printf("i = %d j = %d k = %d dist = %lf\n", i, j, k, dist(a[j], a[k], v));
				double d = dist(a[j], a[k], v);
				if(d < d2) {
					d2 = d;
					v2 = v;
					bestu = a[(i+1)%N] - a[i];
					bestv = a[(j+1)%N] - a[j];
				}
			}
			//printf("d1 = %lf ", d1);
			//printf("d2 = %lf area = %lf\n", d2, d1*d2);
			printf("cross %lf %lf %lf (%lf %lf) (%lf %lf)\n", cross(v1, v2), d1, d2, v1.X, v1.Y, v2.X, v2.Y);
			ans = min(ans, abs(cross(bestu, bestv)));
		}
	}
	printf("Swarm %d Parallelogram Area: %.4lf\n", test, ans);
}

int main() {
	scanf("%d", &T);
	for(int test = 1; test <= T; test++) {
		solve(test);
	}
}