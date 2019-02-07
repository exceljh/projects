#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>
using namespace std;

string input_txt = "input.txt";
vector<pair<int, int>> v;
vector<int> node[5000];
bool chk[5000];
int parent[5000];

double cal(int a, int b)
{
	int x = v[a].first - v[b].first;
	int y = v[a].second - v[b].second;
	int r = x*x + y*y;
	return sqrt(r);
}

class Edge {
public:
	int head, tail;
	double cost;
};


int Find(int x) {
	if (x == parent[x])
		return x;
	else
		return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
	x = Find(x);
	y = Find(y);
	parent[x] = y;
}


void printPath(const vector<int> v) {
	for (auto x : v)
		cout << x << endl;
}


int main()
{
	clock_t start;
	start = clock();
	ifstream fin(input_txt);
	string s;
	getline(fin, s);
	int len = -1;

	for (int i = 0; i < 7; i++)
		getline(fin, s, ' ');
	fin >> len;
	if (len < 0)
		cout << "len_error" << '\n';

	while (s != "NODE_COORD_SECTION")
	{
		getline(fin, s);
	}

	v.push_back({ 0,0 });
	for (int i = 0; i < len; i++) {
		int a, x, y;
		fin >> a >> x >> y;
		v.push_back(make_pair(x, y));
	}
	fin.clear();
	fin.close();

	vector <vector<double>> dist(len + 1, vector<double>(len + 1));
	vector<Edge> e;
	for (int i = 1; i <= len; i++)
	{
		for (int j = i + 1; j <= len; j++)
		{
			double w = cal(i, j);
			dist[i][j] = w;
			dist[j][i] = w;
			e.push_back({ i,j,w });
		}
	}

	for (int i = 1; i <= len; i++) {
		parent[i] = i;
	}

	vector<int> ans;
	int e_len = e.size();
	for (int i = 0; i < e_len; i++) {
		int u = e[i].head;
		int v = e[i].tail;
		int x = Find(u);
		int y = Find(v);

		if (x != y) {
			if (node[u].size() < 2 && node[v].size() < 2) {
				Union(u, v);
				node[u].push_back(v);
				node[v].push_back(u);
			}
		}
	}
	int last[3];
	int last_i = 0;
	for (int i = 1; i <= len; i++) {
		if (node[i].size() < 2)
			last[last_i++] = i;
	}
	node[last[0]].push_back(last[1]);
	node[last[1]].push_back(last[0]);


	int start_p = 1;
	ans.push_back(start_p);
	chk[start_p] = true;
	int p = start_p;
	for (int i = 1; i <= len; i++) {
		int n_size = node[p].size();
		int j = 0;
		while (n_size--) {
			if (!chk[node[p][j]]) {
				chk[node[p][j]] = true;
				ans.push_back(node[p][j]);
				p = node[p][j];
			}
			else
				j++;
		}
	}
	ans.push_back(start_p);
	cout << ans.size()-1 << endl;

	double sum = 0;
	for (int i = 0; i < len; i++) {
		sum += dist[ans[i]][ans[i + 1]];
	}

	cout << "Best: " << sum << endl;



	cout << (clock() - start) / CLOCKS_PER_SEC << '\n';

	ofstream outf("result.txt");
	{
		for (int i = 1; i <= len; i++)
			outf << ans[i]<<'\n' ;
	}
	outf.close();


}