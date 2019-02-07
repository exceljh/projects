//
//		NN방식 or random 방식 + SA or 2-OPT(random)
//		
//

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
#define NUM_OF_NODE 5000							//The number of nodes
string input_txt = "xit1083.txt";					//input txt file    //dcb2086.txt //lsn3119.txt //pbk411.txt  //xqf131.txt
clock_t c_start, c_end;

int node[NUM_OF_NODE][2];							//tsp nodes
double dist[NUM_OF_NODE][NUM_OF_NODE];				//distances from node to node
bool chk_opt[NUM_OF_NODE][NUM_OF_NODE];				//chk 2opt

void readFile(int *len);							//read data file
void printPath(int len, int *route);				//print approximately optimal path
void calcDist(int len);								//calculate distances from node to node
double sumPath(int len, int *route);				//sum tsp path
void NearestNeighbor(int len, int *route);			//make nearest neighbor path
void twoOptSwap(int len, int a, int b, int *route);	//swap 2 edge
void twoOpt(int len, int loof, int * rt);			//2-opt
void SA(int len, double T, int * route);			//simulated annealing
void random(int len, int *rt);						//make randome path

int opt_number = 1;

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

void calcDist(int len) {
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
}

double sumPath(int len, int *rt) {
	double sum = 0;
	for (int i = 0; i < len; i++) {
		sum += dist[rt[i]][rt[i + 1]];
	}
	return sum;
}


void NearestNeighbor(int len, int * route) {
	bool chk[NUM_OF_NODE];						//chk is visited
	memset(chk, 0, sizeof(chk));
	int startPoint = 1;
	route[0] = startPoint;
	chk[startPoint] = true;
	int cnt = 1;
	while (1) {
		int min = -1;
		int next = 0;
		for (int i = 1; i <= len; i++) {
			if (chk[i])
				continue;
			if (min == -1 || min > dist[route[cnt - 1]][i]) {
				min = dist[route[cnt - 1]][i];
				next = i;
			}
		}
		route[cnt++] = next;
		chk[next] = true;
		if (cnt == len)
			break;
	}
	route[cnt] = startPoint;
	cout << "starting point: " << startPoint << endl;
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

//
//void twoOpt(int len, int loof, int * rt) {
//	int try_i = 0;
//	while (try_i < loof) {
//		int x = (rand() % (len - 2)) + 2;
//		int y = (rand() % (len - 2)) + 2;
//		if (x > y)
//			swap(x, y);
//		if (x == y)
//			continue;
//
//		double dist_o = dist[rt[x - 1]][rt[x]] + dist[rt[y]][rt[y + 1]];
//		double dist_n = dist[rt[x - 1]][rt[y]] + dist[rt[x]][rt[y + 1]];
//		double diff = dist_o - dist_n;
//
//		if (diff > 0) {
//			twoOptSwap(len, x, y, rt);
//		//	cout << opt_number++ << "번째 개선" << endl;
//		//	double sum = sumPath(len, rt);
//		//	cout << "Sum: " << sum << endl;
//		}
//		try_i++;
//	}
//}

void twoOpt(int len, int loof, int * rt) {
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
			//		cout << opt_number++ << "번째 개선" << endl;
			//		double sum = sumPath(len, rt);
			//		cout << "Sum: " << sum << endl;
		}
		else
			try_i++;
	}
}

void SA(int len, double T, int * route) {
	int i = 1;
	double best = sumPath(len, route);
	while (i<4000) {
		cout << i << "번째 SA" << endl;
		int new_route[NUM_OF_NODE];
		for (int i = 0; i <= len; i++)
			new_route[i] = route[i];
		int aa = 0;
		while (1) {
			if (aa == (int)T)
				break;
			int x = (rand() % (len - 2)) + 2;
			int y = (rand() % (len - 2)) + 2;
			if (x > y)
				swap(x, y);
			if (x == y)
				continue;
			//	if (chk_opt[x][y])
			//	continue;

			twoOptSwap(len, x, y, new_route);
			//chk_opt[x][y] = true;
			aa++;
		}

		twoOpt(len, 10000000, new_route);
		double new_sum = sumPath(len, new_route);
		double diff;

		if (new_sum < best)
			diff = 1.0;
		else
			diff = exp(best - new_sum) / T;

		if ((double)rand() / RAND_MAX - 0.000001 < diff) {
			for (int i = 0; i <= len; i++)
				route[i] = new_route[i];
			best = new_sum;
		}
		cout << "현재온도: " << T << ", Best: " << best << endl;
		T *= 0.9;
		
		i++;
		c_end = clock();
		double exe_time = (double)(c_end - c_start) / CLOCKS_PER_SEC;
		cout << "Execute time: " << exe_time << "seconds" << endl;

	}

}


void random(int len, int *rt) {
	bool chk[NUM_OF_NODE];
	memset(chk, 0, sizeof(chk));
	int cnt = 0;
	while (cnt != len) {
		int tmp = rand() % len + 1;
		if (!chk[tmp]) {
			rt[cnt++] = tmp;
			chk[tmp] = true;
		}
	}
	rt[cnt] = rt[0];
}

int main() {
	int route[NUM_OF_NODE];						//tsp path array
	cout << "sa_2" << endl;
	srand(time(NULL));
	int len = -1;
	readFile(&len);
	cout << len << " node TSP" << endl;

	c_start = clock();

	//calculate distance from i-node to j-node 
	calcDist(len);

	//calculate first TSP Path
	NearestNeighbor(len, route);
	//random(len, route);


	//Optimization
	//twoOpt(len, 100000000, route);
	SA(len, 100, route);

	//sum path
	double sum = sumPath(len, route);
	cout << "Best route: " << sum << endl;

	//print excute time
	c_end = clock();
	double exe_time = (double)(c_end - c_start) / CLOCKS_PER_SEC;
	cout << "Execute time: " << exe_time << "seconds" << endl;

	//print PATH
	printPath(len, route);
}
