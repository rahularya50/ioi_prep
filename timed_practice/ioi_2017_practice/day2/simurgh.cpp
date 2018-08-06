#include <bits/stdc++.h>

using namespace std;

int count_common_roads(const vector<int>& r);

struct edge {
    int dest;
    int i;
};

int N;

vector<int> gen_query(vector<edge>& edges) {
    vector<int> query(N - 1);
    int curr = 0;
    for (auto x : edges) {
        if (x.i == -1) {
            continue;
        }
        query[curr] = x.i;
        ++curr;
    }
    return query;
}

vector<vector<edge>> graph;
vector<int> find_roads(int n1, vector<int> u, vector<int> v) {
    N = n1;
    graph = vector<vector<edge>>(N);
    for (int i = 0; i != u.size(); ++i) {
        graph[u[i]].push_back({v[i], i});
        graph[v[i]].push_back({u[i], i});
    }

    vector<bool> explored(N, false);
    vector<edge> parent(N);
    vector<vector<edge>> tree_edges(N);
    vector<pair<int, edge>> todo = {{0, {-1, -1}}};
    while (todo.size() > 0) {
        auto n = todo.back();
        todo.pop_back();
        if (explored[n.first]) {
            continue;
        }
        explored[n.first] = true;
        parent[n.first] = n.second;
        if (n.second.dest != -1) {
//            cout << n.first << ", " << n.second.dest << endl;
            tree_edges[n.second.dest].push_back({n.first, n.second.i});
            tree_edges[n.first].push_back(n.second);
        }
        for (auto x : graph[n.first]) {
            todo.push_back({x.dest, {n.first, x.i}});
        }
    }

//    cout << "ok" << endl;

    vector<bool> curr_tree(u.size(), false);
    for (auto x : parent) {
        if (x.i == -1) {
            continue;
        }
//        cout << x.i << ", ";
        curr_tree[x.i] = true;
    }
//    cout << "\n";

    auto def_query = gen_query(parent);
    auto baseline = count_common_roads(def_query);

    vector<int> lookup(u.size(), -1);
    for (int i = 0; i != def_query.size(); ++i) {
        lookup[def_query[i]] = i;
    }

    // otherwise, point to the guy who we're based on

    vector<bool> include(u.size(), false);

    for (int i = 0; i != u.size(); ++i) {
        if (curr_tree[i]) {
//            cout << "Tree edge: " << i << endl;
            include[i] = true;
        }
    }

    for (int i = 0; i != u.size(); ++i) {
        if (curr_tree[i]) {
            // either the edge is necessary for the graph to be connected, or it is not
            // if it is necessary, we know it must be included in the golden set
            // if it isn't, it'll be considered at some point by an alternative, which clearly must exist, so we'll figure it out
            // either way, we don't need to solve it *now*
            continue;
        } else {
//            cout << "Considering edge " << i << "( " << u[i] << " <-> " << v[i] << ")" << endl;
            vector<int> alternatives;
            vector<edge> prev(N);
            vector<pair<int, edge>> todo2 = { {u[i], {-1, -1}} };
            while (todo2.size() > 0) {
                auto n = todo2.back();
                todo2.pop_back();
                prev[n.first] = n.second;
                if (n.first == v[i]) {
                    break;
                }
//                cout << "at " << n.first << endl;
                for (auto x : tree_edges[n.first]) {
                    if (x.dest == n.second.dest) {
                        continue;
                    }
//                    cout << "going to " << x.dest << endl;
                    todo2.push_back({x.dest, {n.first, x.i}});
                }
            }
//            cout << "end?" << endl;
            int curr = v[i];
            while (curr != u[i]) {
//                cout << "curr = " << curr << endl;
                alternatives.push_back(prev[curr].i);
                curr = prev[curr].dest;
            }
//            for (auto x : alternatives) {
//                cout << u[x] << " <-> " << v[x] << endl;
//            }

            vector<int> same = {i};
            vector<int> diff = {};
            bool ans = false;
            for (auto x : alternatives) {
//                cout << "removing edge #" << x << endl;
                def_query[lookup[x]] = i;
                auto res = count_common_roads(def_query);
                def_query[lookup[x]] = x;

//                cout << "math time!" << endl;

                if (res > baseline) {
//                    cout << "Excluding edge #" << x << endl;
                    ans = true;
                    diff.push_back(x);
                } else if (res < baseline) {
                    ans = false;
                    diff.push_back(x);
                } else {
//                    cout << "pushing " << x << " to solved!" << endl;
                    same.push_back(x);
                }
            }

//            cout << "ans = " << ans << "\n";
            for (auto x : same) {
//                cout << "same = " << x << "\n";
                include[x] = ans;
            }
            for (auto x : diff) {
//                cout << "diff = " << x << "\n";
                include[x] = !ans;
            }
        }
    }

    vector<int> out;
    for (int i = 0; i != u.size(); ++i) {
        if (include[i]) {
//            cout  << i << ", ";
            out.push_back(i);
        }
    }

    return out;

}
//
//static int MAXQ = 30000;
//
//static int n, m, q = 0;
//static vector<int> u, v;
//static vector<bool> goal;
//
//static void wrong_answer() {
//	printf("NO\n");
//	exit(0);
//}
//
//static bool is_valid(const vector<int>& r) {
//	if(int(r.size()) != n - 1)
//		return false;
//
//	for(int i = 0; i < n - 1; i++)
//		if (r[i] < 0 || r[i] >= m)
//			return false;
//
//	return true;
//}
//
//static int _count_common_roads_internal(const vector<int>& r) {
//	if(!is_valid(r))
//		wrong_answer();
//
//	int common = 0;
//	for(int i = 0; i < n - 1; i++) {
//		bool is_common = goal[r[i]];
//		if (is_common)
//			common++;
//	}
//
//	cout << "responded to query!<< endl;
//	return common;
//}
//
//int count_common_roads(const vector<int>& r) {
//    cout << "received query!<< endl;
//	q++;
//	if(q > MAXQ)
//		wrong_answer();
//
//	return _count_common_roads_internal(r);
//}
//
//int main() {
//	assert(2 == scanf("%d %d", &n, &m));
//
//	u.resize(m);
//	v.resize(m);
//
//	for(int i = 0; i < m; i++)
//		assert(2 == scanf("%d %d", &u[i], &v[i]));
//
//	goal.resize(m, false);
//
//	for(int i = 0; i < n - 1; i++) {
//		int id;
//		assert(1 == scanf("%d", &id));
//		goal[id] = true;
//	}
//
//	vector<int> res = find_roads(n, u, v);
//
//	if(_count_common_roads_internal(res) != n - 1)
//		wrong_answer();
//
//	printf("YES\n");
//
//	return 0;
//}

