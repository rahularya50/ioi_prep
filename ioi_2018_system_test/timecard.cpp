#include "bits/stdc++.h"

static int N;

void init(int n) {
  N = n;
}

std::string convert(std::string s) {
    for (int i = 0; i != s.size(); ++i) {
        if (s[i] < 'a') {
            s[i] = s[i] - 'A' + 'a';
        }
    }
    return s;
}

//
//int readInt(){
//	int i;
//	if(scanf("%d",&i)!=1){
//		fprintf(stderr,"Error while reading input\n");
//		exit(1);
//	}
//	return i;
//}
//
//int main(){
//	int n;
//	n=readInt();
//	init(n);
//
//	for(int i=0;i!=n;i++){
//		std::string s;
//		std::cin >> s;
//		s = convert(s);
//		std::cout << s << std::endl;
//	}
//}
