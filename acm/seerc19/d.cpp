#include "bits/stdc++.h"

using namespace std;

char str[1000001];

int main()
{
  scanf("%s", str);
  int arr[26]; // number of occurrences of each letter
  for (int i = 0; i < 26; i++)
    arr[i] = 0;
  for (size_t i = 0; str[i]; i++)
    arr[str[i] - 'a']++;
  int len = 0; // len of string
  for (int i = 0; i < 26; i++)
    len += arr[i];
  int repeated = -1; // index of letter that occurs more than half the time
  int unique = 0; // number of different letters
  int count;
  for (int i = 0; i < 26; i++)
  {
    if (arr[i] > len / 2)
    {
      repeated = i;
      count = arr[i];
    }
    if (arr[i])
      unique++;
  }
  if (repeated == -1)
  {
    sort(str, str + len);
    printf("YES\n");
    printf("%s\n", str);
    return 0;
  }
  if (count < len - 1 && !(unique == 2 && count == len - 2))
  {
    printf("YES\n");
    for (int i = 0; i < len / 2; i++)
      printf("%c", 'a' + repeated);
    for (int i = 25; i >= 0; i--)
    {
      if (i == repeated)
        continue;
      if (arr[i])
      {
        arr[i]--;
        printf("%c", 'a' + i);
        break;
      }
    }
    for (int i = 0; i < count - len / 2; i++)
      printf("%c", 'a' + repeated);
    for (int i = 0; i < 26; i++)
    {
      if (i == repeated)
        continue;
      for (int j = 0; j < arr[i]; j++)
        printf("%c", 'a' + i);
    }
    printf("\n");
  }
  else
  {
    printf("NO\n");
  }
  return 0;
}
