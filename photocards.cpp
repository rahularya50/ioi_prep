
#include <bits/stdc++.h>

using namespace std;

int main() {
	auto in = fopen("photocards.in", "r");
	auto out = fopen("photocards.out", "w");

	int N, M;
	fscanf(in, "%d %d", &N, &M);
	map<array<short, 26>, long long> cnt;
	array<short, 26> run = {};

	char S[6000000];
	fscanf(in, "%s", S);

	int num_zeros = M;
	++cnt[run];
	for (int i = 0; i != N; ++i) {
		if (run[S[i] - 'a'] == 0) {
			--num_zeros;
		}
		++run[S[i] - 'a'];
		if (num_zeros == 0) {
			for (int j = 0; j != M; ++j) {
				--run[j];
				if (run[j] == 0) {
					++num_zeros;
				}
			}
		}
		++cnt[run];
	}

	long long ans = 0;
	for (auto& x : cnt) {
		ans += x.second * (x.second - 1) / 2;
	}
	fprintf(out, "%d", ans);
}
