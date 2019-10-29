#include "bits/stdc++.h"

using namespace std;
typedef long long ll;
ll givedrive[100001], 
givemotor[100001], 
needdrive[100001], 
needmotor[100001], 
givechild[100001];
ll n, k;
ll INF = 1000000000000;
ll agecar, pricecar, agemotor, pricemotor; 
ll t, d;
vector<ll> age;
int main(){
	cin >> n >> k;
	cin >> agecar >> pricecar >> agemotor >> pricemotor;
	cin >> t >> d;
	ll tmp;
	for (ll i=0;i!=n;++i) {
		cin >> tmp;
		age.push_back(tmp);
	}
	sort(age.begin(),age.end());
	reverse(age.begin(), age.end());

	for (ll i=0;i!=n;++i) {
		givedrive[i] = min(d, max(0LL, age[i]-agecar));
		givemotor[i] = min(d, max(0LL, age[i]-agemotor));
		needdrive[i] = max(0LL, agecar - age[i]);
		needmotor[i] = max(0LL, agemotor - age[i]);
		givechild[i] = min(d, age[i] - 1);

	}
	bool motorvalid = true;
	ll give = 0, need = 0, transfered = 0;
	ll start = 0, end = n;
	ll cost = pricemotor*n;
	for (ll i=0;i!=n;++i) {
		if (givemotor[i]>0) give+=givemotor[i];
		else {
			need+=needmotor[i];
			motorvalid = motorvalid && (needmotor[i] <= d);
		}
	}
	transfered = min(give, need);
	cost += t*transfered;
	ll res = INF;
	if (give>=need && motorvalid){
		res = min(res, cost);
	}




	while (end > start){
		cost += pricecar - pricemotor;
		// do driver
		give += givedrive[start] - givemotor[start];
		need += needdrive[start] - needmotor[start];
		if (needdrive[start] > d){
			break;
		}
		start ++;
		// do children
		ll todo = min(k-1, end-start);
		while (todo --){
			// do 1 children
			end --;
			motorvalid = motorvalid || (end > 0 && needmotor[end-1]<=d);
			give += givechild[end] - givemotor[end];
			need -= needmotor[end];
			cost -= pricemotor;
		}
		//update transfer and cost
		ll newtransfer = min(need, give);
		cost += (newtransfer-transfered)*t;
		transfered = newtransfer;
		//if valid update result
		if (need <= give && motorvalid){
			res = min(res, cost);
		}

	}
	if (res == INF) cout << -1 << endl;
	else cout << res << endl;








}