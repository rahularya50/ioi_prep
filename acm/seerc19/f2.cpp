#include "bits/stdc++.h"

using namespace std;

vector<int> neighbors[100001];
int ordered_v[100001];
int parent[100001];
bool win_state[100001];

int main()
{
  int n, u, v;
  scanf("%d", &n);
  if (n == 1)
  {
    printf("Alice\n");
    return 0;
  }
  for (int i = 1; i < n; i++)
  {
    scanf("%d %d", &u, &v);
    neighbors[u].push_back(v);
    neighbors[v].push_back(u);
  }
  memset(parent, -1, sizeof(parent));
  parent[1] = 0;
  ordered_v[0] = 1;
  int size = 1;
  for (int i = 0; size < n; i++)
  {
    for (auto x : neighbors[ordered_v[i]])
    {
      if (parent[x] == -1)
      {
        ordered_v[size] = x;
        parent[x] = ordered_v[i];
        size++;
      }
    }
  }
  for (int i = n - 1; i >= 0; i--)
  {
    int cur = ordered_v[i];
    if (neighbors[cur].size() == 1 && i)
    {
      win_state[cur] = true;
      continue;
    }
    bool can_win = false;
    for (auto x : neighbors[cur])
    {
      if (x == parent[cur])
        continue;
      can_win |= win_state[x];
    }
    win_state[cur] = !can_win;
  }
  for (int i = 1; i < n; i++)
  {
    int cur = ordered_v[i];
    int par = parent[cur];
    if (!win_state[cur])
      continue;
    if (win_state[par])
    {
      win_state[cur] = false;
    }
  }
  bool ans = false;
  for (int i = 1; i <= n; i++)
  {
    ans |= win_state[i];
    printf("%d\n", win_state[i]);
  }
  if (ans)
    printf("Alice\n");
  else
    printf("Bob\n");
  return 0;
}
