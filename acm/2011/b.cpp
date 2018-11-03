#include "bits/stdc++.h"
using namespace std;

const int MAXN = 2000;

int N, M;
char s[MAXN], t[MAXN];
int dp[MAXN][MAXN];

int lcs() {
	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= M; j++) {
			dp[i][j] = s[i] == t[j]? dp[i-1][j-1] + 1 : max(dp[i-1][j], dp[i][j-1]);
		}
	}
	return dp[N][M];
}

bool solve() {
	if(scanf("%s%s", s+1, t+1) != 2) {
		return false;
	}
	N = strlen(s+1);
	M = strlen(t+1);
	int ans = 0;
	for(int i = 0; i < N; i++) {
		ans = max(ans, lcs());
		rotate(s+1, s+2, s+N+1);
		//printf("%s\n", s+1);
		reverse(s+1, s+N+1);
		ans = max(ans, lcs());
		reverse(s+1, s+N+1);
	}
	printf("%d\n", ans*2);
	return true;
}

int main() {
	while(solve());
}