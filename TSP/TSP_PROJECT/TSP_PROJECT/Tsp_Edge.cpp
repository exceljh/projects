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
#define endl '\n'
#define NUM_OF_NODE 10000					//The number of nodes
#define THREEOPTTIME 10
#define TWICE 10
#define TWOOPTTIME 2
#define cake 25


string input_txt = "xit1083.txt";			//xit1083.txt input txt file //dcb2086.txt //lsn3119.txt //pbk411.txt  //xqf131.txt
double dropout = 1.0;

struct Edge {
	double cost;
	int start, end;
};

bool cmp(const Edge& e1, const Edge& e2) {
	return e1.cost < e2.cost;
}

Edge e[NUM_OF_NODE*NUM_OF_NODE / 2];
int parent[NUM_OF_NODE];
int node[NUM_OF_NODE][2];							//tsp nodes
double dist[NUM_OF_NODE][NUM_OF_NODE];				//distances from node to node

void readFile(int *len);							//read data file
void printPath(int len, int *route);				//print approximately optimal path
int calcDist(int len);								//calculate distances from node to node
double sumPath(int len, int *route);				//sum tsp path
void twoOptSwap(int len, int a, int b, int *route);	//swap 2 edge
void twoOpt2(int len, int loof, int * rt);
void twoOpt(int len, int * rt);						//2-opt

int opt_number = 1;
clock_t c_start, c_end;
double exe_time;

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

void readFile(int *len) {
	ifstream fin(input_txt);
	string s;
	getline(fin, s);
	//find length of Node
	for (int i = 0; i < 7; i++)
		getline(fin, s, ' ');
	fin >> *len;
	if (*len < 0)
		cout << "length_error" << endl;
	//dummy data
	while (s != "NODE_COORD_SECTION") {
		getline(fin, s);
	}
	//input Node 1 ~ len 
	for (int i = 0; i < *len; i++) {
		int a, x, y;
		fin >> a >> node[i + 1][0] >> node[i + 1][1];
	}
	fin.clear();
	fin.close();	//close input data stream
}

void printPath(int len, int *route) {
	ofstream fout("result.txt");
	for (int i = 0; i <= len; i++) {
		fout << route[i] << endl;
	}
	cout << "result.txt file is generated" << endl;
}

int calcDist(int len) {
	int e_count = 0;
	for (int i = 1; i <= len; i++) {
		for (int j = i + 1; j <= len; j++) {
			int x = node[i][0] - node[j][0];
			int y = node[i][1] - node[j][1];
			int r = x*x + y*y;
			double w = sqrt(r);
			dist[i][j] = w;
			dist[j][i] = w;
		}
	}
	double max_x = -1;
	for (int j = 2; j <= len; j++) {
		if (max_x < dist[1][j])
			max_x = dist[1][j];
	}
	for (int i = 1; i <= len; i++) {
		for (int j = i + 1; j <= len; j++) {
			if (dist[i][j] < max_x * dropout)
				e[e_count++] = { dist[i][j],i,j };
		}
	}
	return e_count;
}

double sumPath(int len, int *rt) {
	double sum = 0;
	for (int i = 0; i < len; i++) {
		sum += dist[rt[i]][rt[i + 1]];
	}
	return sum;
}


void twoOptSwap(int len, int a, int b, int *route) {
	int new_route[NUM_OF_NODE];
	int n_i = 0;
	for (int i = 0; i < a; i++)
		new_route[n_i++] = route[i];
	for (int i = b; i >= a; i--)
		new_route[n_i++] = route[i];
	for (int i = b + 1; i <= len; i++)
		new_route[n_i++] = route[i];

	for (int i = 0; i <= len; i++)
		route[i] = new_route[i];
}


void twoOpt2(int len, int loof, int * rt) {
	int try_i = 0;
	while (try_i < loof) {
		c_end = clock();
		exe_time = (double)(c_end - c_start) / CLOCKS_PER_SEC;
		if (exe_time > TWOOPTTIME)
			break;

		int x = (rand() % (len - 2)) + 2;
		int y = (rand() % (len - 2)) + 2;
	
		if (x > y)
			swap(x, y);
		if (x == y)
			continue;

		double dist_o = dist[rt[x - 1]][rt[x]] + dist[rt[y]][rt[y + 1]];
		double dist_n = dist[rt[x - 1]][rt[y]] + dist[rt[x]][rt[y + 1]];
		double diff = dist_o - dist_n;

		if (diff > 0) {
			twoOptSwap(len, x, y, rt);
			cout << (clock() - c_start) / CLOCKS_PER_SEC << " " << endl;
			double sum = sumPath(len, rt);
			cout << "Sum: " << sum << endl;
		}
		try_i++;
	}
		double sum = sumPath(len, rt); //two line add.
		cout << "Sum: " << sum << endl;

}

void twoOpt(int len, int * rt) {
	int try_i = 0;
	while (1) {
		if (try_i == 100000)
			break;
		int x = (rand() % (len - 2)) + 2;
		int y = (rand() % (len - 2)) + 2;
		if (x > y)
			swap(x, y);
		if (x == y)
			continue;

		double dist_o = dist[rt[x - 1]][rt[x]] + dist[rt[y]][rt[y + 1]];
		double dist_n = dist[rt[x - 1]][rt[y]] + dist[rt[x]][rt[y + 1]];
		double diff = dist_o - dist_n;

		if (diff > 0) {
			twoOptSwap(len, x, y, rt);
			try_i = 0;
			cout << (clock()-c_start)/CLOCKS_PER_SEC << " " << endl;
			double sum = sumPath(len, rt);
			cout << "Sum: " << sum << endl;
		}
		else
			try_i++;
	}
}


////////////////////////////////////////////

int remem_route[NUM_OF_NODE];
double remembest;

void Swap_ThreeOpt1(int len, int *rt, int A, int B, int C, int D, int E, int F)
{

	int new_route[NUM_OF_NODE];

	int k = 0;
	for (int i = 0; i <= A; i++)
	{
		new_route[k] = rt[i];
		k++;
	}
	for (int i = C; i >= E; i--)
	{
		new_route[k] = rt[i];
		k++;
	}
	for (int i = D; i <= B; i++)
	{
		new_route[k] = rt[i];
		k++;
	}
	for (int i = F; i <= len; i++)
	{
		new_route[k] = rt[i];
		k++;
	}
	for (int i = 0; i <= len; i++)
		rt[i] = new_route[i];

}

void Swap_ThreeOpt2(int len, int *rt, int A, int B, int C, int D, int E, int F)
{

	int new_route[NUM_OF_NODE];

	int k = 0;
	for (int i = 0; i <= A; i++)
	{
		new_route[k] = rt[i];
		k++;
	}
	for (int i = E; i <= C; i++)
	{
		new_route[k] = rt[i];
		k++;
	}
	for (int i = D; i <= B; i++)
	{
		new_route[k] = rt[i];
		k++;
	}
	for (int i = F; i <= len; i++)
	{
		new_route[k] = rt[i];
		k++;
	}

	for (int i = 0; i <= len; i++)
		rt[i] = new_route[i];
}

void Swap_ThreeOpt3(int len, int *rt, int A, int B, int C, int D, int E, int F)
{

	int new_route[NUM_OF_NODE];

	int k = 0;
	for (int i = 0; i <= A; i++)
	{
		new_route[k] = rt[i];
		k++;
	}
	for (int i = B; i >= D; i--)
	{
		new_route[k] = rt[i];
		k++;
	}
	for (int i = C; i >= E; i--)
	{
		new_route[k] = rt[i];
		k++;
	}
	for (int i = F; i <= len; i++)
	{
		new_route[k] = rt[i];
		k++;
	}
	for (int i = 0; i <= len; i++)
		rt[i] = new_route[i];


}

void Swap_ThreeOpt4(int len, int *rt, int A, int B, int C, int D, int E, int F)
{

	int new_route[NUM_OF_NODE];

	int k = 0;
	for (int i = 0; i <= A; i++)
	{
		new_route[k] = rt[i];
		k++;
	}
	for (int i = E; i <= C; i++)
	{
		new_route[k] = rt[i];
		k++;
	}
	for (int i = B; i >= D; i--)
	{
		new_route[k] = rt[i];
		k++;
	}
	for (int i = F; i <= len; i++)
	{
		new_route[k] = rt[i];
		k++;
	}

	for (int i = 0; i <= len; i++)
		rt[i] = new_route[i];
}


/////////////////////
void Swap_ThreeOpt5(int len, int *rt, int A, int B, int C, int D, int E, int F)
{

	int new_route[NUM_OF_NODE];

	int k = 0;
	for (int i = 0; i <= B; i++)
	{
		new_route[k] = rt[i];
		k++;
	}
	for (int i = C; i >= E; i--)
	{
		new_route[k] = rt[i];
		k++;
	}
	for (int i = F; i <= len; i++)
	{
		new_route[k] = rt[i];
		k++;
	}
	for (int i = 0; i <= len; i++)
		rt[i] = new_route[i];
}

/////////
void Swap_ThreeOpt6(int len, int *rt, int A, int B, int C, int D, int E, int F)
{

	int new_route[NUM_OF_NODE];

	int k = 0;
	for (int i = 0; i <= A; i++)
	{
		new_route[k] = rt[i];
		k++;
	}
	for (int i = C; i >= D; i--)
	{
		new_route[k] = rt[i];
		k++;
	}
	for (int i = F; i <= len; i++)
	{
		new_route[k] = rt[i];
		k++;
	}

	for (int i = 0; i <= len; i++)
		rt[i] = new_route[i];
}

void Swap_ThreeOpt7(int len, int *rt, int A, int B, int C, int D, int E, int F)
{

	int new_route[NUM_OF_NODE];

	int k = 0;
	for (int i = 0; i <= A; i++)
	{
		new_route[k] = rt[i];
		k++;
	}
	for (int i = B; i >=D; i--)
	{
		new_route[k] = rt[i];
		k++;
	}
	for (int i = E; i <= len; i++)
	{
		new_route[k] = rt[i];
		k++;
	}

	for (int i = 0; i <= len; i++)
		rt[i] = new_route[i];
}


void three_opt(int len, int *rt, double ti=0)
{

	cout << "3-opt start" << '\n';
	
	int q = 0; // change count;
	int try_i = 0;
	int START = 2;

	int count = 0;
	while (1) {
		c_end = clock();
		exe_time = (double)(c_end - c_start) / CLOCKS_PER_SEC;

		if (exe_time > THREEOPTTIME+ti) {
			break;
		}
		if (try_i == 1000000000)
			break;

		int A = (rand() % (len - 6)) + 2;
		int B = (rand() % (len - 4)) + 2;
		int C = (rand() % (len - 2)) + 2;
/*		if (count < len - 8)
			count++;
		else
			count = 0;
		int A = START + count;
		int B = A + (rand() % 2) + 2;
		if (B + 2 >= len)
			B = B - len + 2;
		int C = B + (rand() % 2) + 2;
		if (C + 2 >= len)
			C = C - len + 2;
		
		*/
		int d[3] = { A, B, C };
		sort(d, d + 3);
		A = d[0]; B = d[1]; C = d[2];
		
		
		if (A == B)
			continue;
		if (B == C)
			continue;
			


		int D = A + 1; //a-d
		int E = B + 1;// b-e
		int F = C + 1;//f-c


		double x = dist[rt[A]][rt[D]]; //a~an의 길이
		double y = dist[rt[B]][rt[E]];//b~ bn의 길이
		double z = dist[rt[C]][rt[F]];//c~cn의 길이

		double d0 = dist[rt[A]][rt[D]] + dist[rt[B]][rt[E]] + dist[rt[C]][rt[F]]; // 현재길이
		double d1 = dist[rt[A]][rt[C]] + dist[rt[D]][rt[E]] + dist[rt[B]][rt[F]];
		double d2 = dist[rt[A]][rt[E]] + dist[rt[D]][rt[C]] + dist[rt[B]][rt[F]];
		double d3 = dist[rt[A]][rt[B]] + dist[rt[E]][rt[F]] + dist[rt[C]][rt[D]];
		double d4 = dist[rt[A]][rt[E]] + dist[rt[C]][rt[B]] + dist[rt[F]][rt[D]];

		double b1= dist[rt[A]][rt[D]] + dist[rt[B]][rt[C]]+ dist[rt[F]][rt[E]];
		double b2= dist[rt[B]][rt[E]] + dist[rt[A]][rt[C]] + dist[rt[D]][rt[F]];
		double b3= dist[rt[C]][rt[F]] + dist[rt[A]][rt[B]] + dist[rt[D]][rt[E]];

		double p0 = sumPath(len, rt);
		
		
		if (d0 > d1)
		{
			try_i = 0;
			Swap_ThreeOpt1(len, rt, A, B, C, D, E, F);
		}
		else if (d0 > d2)
		{
			try_i = 0;
			Swap_ThreeOpt2(len, rt, A, B, C, D, E, F);
		}
		else if (d0 > d3)
		{
			try_i = 0;
			Swap_ThreeOpt3(len, rt, A, B, C, D, E, F);
		}
		else if (d0 > d4)
		{
			try_i = 0;
			Swap_ThreeOpt4(len, rt, A, B, C, D, E, F);
		}
		else if (d0 > b1)
		{
			try_i = 0;
			Swap_ThreeOpt5(len, rt, A, B, C, D, E, F);
		}
		else if (d0 > b2)
		{
			try_i = 0;
			Swap_ThreeOpt6(len, rt, A, B, C, D, E, F);

		}
		else if (d0>b3)
		{
			try_i = 0;
			Swap_ThreeOpt7(len, rt, A, B, C, D, E, F);

		}
		else {
			try_i++;
		}

		
		if (p0 > sumPath(len, rt))
			cout << (clock()-c_start)/CLOCKS_PER_SEC << " best: " << sumPath(len, rt) << '\n';
			
	}


	cout << "after 3opt Best : " << sumPath(len, rt) << ". 3-opt end." << '\n';


}

//////////////////////////////////////////////////




////////GA
///////////////////////////////////////////////////////////

void order(int len, int(*rt)[NUM_OF_NODE], int sequence[cake])
{
	double length[cake];
	for (int i = 0; i < cake; i++)
	{
		length[i] = sumPath(len, rt[i]);
	}

	for (int i = 0; i < cake; i++)
	{
		double min = 9999999;
		int k = 0;
		for (int j = 0; j < cake; j++) {
			if (length[j] < min)
			{
				min = length[j];
				k = j;
			}

		}
		length[k] = 999999999;
		sequence[i] = k;
	}

	
}

void GA_off(int len, int rt1[NUM_OF_NODE], int rt2[NUM_OF_NODE])
{

	cout << "creat child" << '\n';
	int pair1[NUM_OF_NODE] = { 0 };
	int pair2[NUM_OF_NODE] = { 0 };
	int route1[NUM_OF_NODE];
	int route2[NUM_OF_NODE];


	int x;
	int y;

	while (1)
	{
	x = (rand() % (len - 2)) + 2;
	y = (rand() % (len - 2)) + 2;

	if (x != y)
		break;
	}

	if (x > y)
	{
		int temp;
		temp = x;
		x = y;
		y = temp;
	}

	for (int i = x; i < y; i++)
	{
		route1[i] = rt2[i];
		pair1[rt2[i]] = rt1[i];

		route2[i] = rt1[i];
		pair2[rt1[i]] = rt2[i];
	}


	for (int i = 0; i < x; i++)
	{
		if (pair1[rt1[i]] == 0)
			route1[i] = rt1[i];
		else
			route1[i] = pair1[rt1[i]];


		/////////////////////////
		if (pair2[rt2[i]] == 0)
			route2[i] = rt2[i];
		else
			route2[i] = pair2[rt2[i]];


	}

	for (int i = y; i <= len; i++)
	{
		if (pair1[rt1[i]] == 0)
			route1[i] = rt1[i];
		else
			route1[i] = pair1[rt1[i]];


		/////////////////////////
		if (pair2[rt2[i]] == 0)
			route2[i] = rt2[i];
		else
			route2[i] = pair2[rt2[i]];

	}

	if(sumPath(len, rt1)<sumPath(len, route1))
	for (int i = 0; i <= len; i++)
	{
		rt1[i] = route1[i];
	}

	if (sumPath(len, rt2)<sumPath(len, route2))
		for (int i = 0; i <= len; i++)
		{
			rt2[i] = route2[i];
		}
}


void GA(int len, int (*rt)[NUM_OF_NODE])
{

	cout << "ga start " << '\n';
	int generation = 1;
	
	exe_time = (double)(c_end - c_start) / CLOCKS_PER_SEC;
	
	while (1)
	{
		if (exe_time > 100)
			break;

		int sequence[cake];

		order(len, rt, sequence);


		GA_off(len, rt[sequence[0]], rt[sequence[1]]);
		GA_off(len, rt[sequence[2]], rt[sequence[24]]);
		GA_off(len, rt[sequence[3]], rt[sequence[4]]);
		GA_off(len, rt[sequence[5]], rt[sequence[23]]);
		GA_off(len, rt[sequence[7]], rt[sequence[20]]);
		GA_off(len, rt[sequence[8]], rt[sequence[19]]);
		GA_off(len, rt[sequence[9]], rt[sequence[10]]);
		GA_off(len, rt[sequence[11]], rt[sequence[12]]);
		GA_off(len, rt[sequence[14]], rt[sequence[15]]);


	//	for(int i=0; i<cake; i++)
//		twoOpt2(len, 100000, rt[i]);

		cout << generation++ << "\n";

		if (generation > 10000)
			break;

	}
}


///////////////////////////////////////////////////////


void EdgeFirst(int e_len, int len, int * route) {
	vector<int> v_node[NUM_OF_NODE];
	bool chk[NUM_OF_NODE];
	memset(chk, 0, sizeof(chk));
	for (int i = 1; i <= len; i++)
		parent[i] = i;
	for (int i = 0; i < e_len; i++) {
		int u = e[i].start;
		int v = e[i].end;
		int x = Find(u);
		int y = Find(v);
		if (x != y) {
			if (v_node[u].size() < 2 && v_node[v].size() < 2) {
				Union(u, v);
				v_node[u].push_back(v);
				v_node[v].push_back(u);
			}
		}
	}
	int no = 0;
	vector<int> no_v;
	for (int i = 1; i <= len; i++) {
		if (v_node[i].size() < 2) {
			no++;
			no_v.push_back(i);
		}
	}

	if (no == 2) {
		int last[3];
		int last_i = 0;
		for (int i = 1; i <= len; i++) {
			if (v_node[i].size() < 2)
				last[last_i++] = i;
		}
		v_node[last[0]].push_back(last[1]);
		v_node[last[1]].push_back(last[0]);
	}
	else {
		cout << "additional edge" << endl;
		int n_len = no_v.size();
		for (int i = 0; i < n_len; i++) {
			for (int j = i + 1; j < n_len; j++) {
				int u = no_v[i];
				int v = no_v[j];
				int x = Find(u);
				int y = Find(v);
				if (x != y) {
					if (v_node[u].size() < 2 && v_node[v].size() < 2) {
						Union(u, v);
						v_node[u].push_back(v);
						v_node[v].push_back(u);
						break;
					}
				}
			}
		}
		int last[3];
		int last_i = 0;
		for (int i = 1; i <= len; i++) {
			if (v_node[i].size() < 2)
				last[last_i++] = i;
		}
		v_node[last[0]].push_back(last[1]);
		v_node[last[1]].push_back(last[0]);
	}
	int start_p = 1;
	route[0] = start_p;
	chk[start_p] = true;
	int p = start_p;
	int count = 1;
	for (int i = 1; i <= len; i++) {
		int n_size = v_node[p].size();
		int j = 0;
		while (n_size--) {
			if (!chk[v_node[p][j]]) {
				chk[v_node[p][j]] = true;
				route[count++] = v_node[p][j];
				p = v_node[p][j];
			}
			else
				j++;
		}
	}
	route[count++] = start_p;
}

int main() {
	int route[NUM_OF_NODE];						//tsp path array
	cout << "edge_sort + 2opt" << endl;
	srand(time(NULL));
	int len = -1;
	readFile(&len);
	cout << len << " node TSP" << endl;

	c_start = clock();

	//calculate distance from i-node to j-node 
	int e_count = calcDist(len);
	stable_sort(e, e + e_count, cmp);

	c_end = clock();
	exe_time = (double)(c_end - c_start) / CLOCKS_PER_SEC;
	cout << "Sorting time: " << exe_time << "seconds" << endl;

	//calculate first TSP Path	
		EdgeFirst(e_count, len, route);
		double sum = sumPath(len, route);
		cout << "first route: " << sum << endl;

		//Optimization

		//three_opt(len, route);

		//	sum = sumPath(len, route);
		//	cout << "3 opt Best route: " << sum << endl;


	//	twoOpt2(len, 5000000000, route);

		three_opt(len, route, TWICE);

		//sum = sumPath(len, route);
		//twoOpt(len, route);

		//sum path
		//sum = sumPath(len, route[i]);
		//cout << i << ": Best route: " << sum << endl;


	

	//GA(len, route);
	//double minPath = 9999999;
	//int bestpath;
//	for (int i = 0; i < cake; i++)
	//{
		//double sum = sumPath(len, route[i]);
		//if (sum < minPath)
		//{
			//minPath = sum;
			//bestpath = i;
		//}
//	}

	//print excute time
	c_end = clock();
	exe_time = (double)(c_end - c_start) / CLOCKS_PER_SEC;
	cout << "Execute time: " << exe_time << "seconds" << endl;
//	cout << "Best sum = " << minPath << '\n';
	//print PATH
	printPath(len, route);

	return 0;
}
