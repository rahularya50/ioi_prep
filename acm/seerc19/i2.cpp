#include "bits/stdc++.h"

using namespace std;

const int INFTY = 2e9;

int diff[1000][1000];

int main()
{
  int n;
  scanf("%d", &n);
  vector<int> a;
  vector<int> b;
  int num;
  for (int i = 0; i < n; i++)
  {
    scanf("%d", &num);
    a.push_back(num);
  }
  for (int i = 0; i < n; i++)
  {
    scanf("%d", &num);
    b.push_back(num);
  }
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      diff[i][j] = abs(a[i] - b[j]);
    }
  }
  int min_col[1000];
  for (int i = 0; i < n; i++)
  {
    min_col[i] = INFTY;
    for (int j = 0; j < n; j++)
    {
      min_col[i] = min(min_col[i], diff[i][j]);
    }
  }
  int ans = 0;
  for (int i = 0; i < n; i++)
    if (min_col[i] > ans)
      ans = min_col[i];
  printf("%d\n", ans);
  return 0;
}
