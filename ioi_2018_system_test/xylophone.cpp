#include <bits/stdc++.h>

using namespace std;

int ask(int s, int t);
void answer(int i, int a);

static int A[5000];

void detect_pitch(int N) {
	vector<int> raw_diff(N - 1);
	for (int i = 0; i != N - 1; ++i) {
		raw_diff[i] = ask(i, i + 1);
//        cout << "raw_diff[" << i << "] = " << raw_diff[i] << "\n";
    }

    vector<int> delta_sign = {1};
    for (int i = 1; i != N - 1; ++i) {
        // is A[i + 1] > A[i] > A[i - 1] ??
        if (ask(i - 1, i + 1) == raw_diff[i - 1] + raw_diff[i]) {
            delta_sign.push_back(delta_sign.back());
        } else {
            delta_sign.push_back(-1 * delta_sign.back());
        }
//        cout << "delta_sign[" << i << "] = " << delta_sign[i] << "\n";
    }

    vector<int> temp_out(N);
    for (int i = 1; i != N; ++i) {
        temp_out[i] = temp_out[i - 1] + delta_sign[i - 1] * raw_diff[i - 1];
    }

    int min_i = 0;
    int max_i = 0;

    for (int i = 0; i != N; ++i) {
        if (temp_out[i] < temp_out[min_i]) {
            min_i = i;
        }
        if (temp_out[i] > temp_out[max_i]) {
            max_i = i;
        }
    }

    int m_factor = 1;
    int real_min_i = min_i;
    int real_max_i = max_i;
    if (min_i > max_i) {
        m_factor = -1;
        swap(real_min_i, real_max_i);
    }

    for (int i = 0; i != N; ++i) {
        A[i] = m_factor * (temp_out[i] - temp_out[real_min_i]);
//        cout << A[i] << ", ";
        answer(i, A[i]);
    }
}
//
//// grading
//
//static const int N_MAX = 5000;
//static const int Q_MAX = 10000;
//static int N;
//static bool used[N_MAX];
//static int query_c;
//static int answer_c;
//
//int ask(int s, int t) {
//    cout << "Querying between " << s << " and " << t << "!\n";
//	if(query_c >= Q_MAX) {
//		printf("Too many queries\n");
//		exit(0);
//	}
//	query_c++;
//	if(!(0 <= s && s <= t && t < N)) {
//		printf("Invalid query\n");
//		exit(0);
//	}
//	int mx = -1, mn = N;
//	for(int i = s; i <= t; i++) {
//		if(mx < A[i]) {
//			mx = A[i];
//		}
//		if(mn > A[i]) {
//			mn = A[i];
//		}
//	}
//	return mx - mn;
//}
//
//void answer(int i, int a) {
//	answer_c++;
//	if(!(0 <= i && i < N)) {
//		printf("Wrong Answer\n");
//		exit(0);
//	}
//	if(!(0 <= a && a < N)) {
//		printf("Wrong Answer\n");
//		exit(0);
//	}
//	if(used[i]) {
//		printf("Wrong Answer\n");
//		exit(0);
//	}
//	if(a != A[i]) {
//		printf("Wrong Answer\n");
//		exit(0);
//	}
//	used[i] = true;
//}
//
//int main() {
//	query_c = 0;
//	answer_c = 0;
//	if(scanf("%d", &N) != 1) {
//		fprintf(stderr, "Error while reading input\n");
//		exit(1);
//	}
//	for(int i = 0; i < N; i++) {
//		if(scanf("%d", A + i) != 1) {
//			fprintf(stderr, "Error while reading input\n");
//			exit(1);
//		}
//		used[i] = false;
//	}
//	detect_pitch(N);
//	if(!(answer_c == N)) {
//		printf("Wrong Answer\n");
//		exit(0);
//	}
//	printf("Accepted : %d\n", query_c);
//}
