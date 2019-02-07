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
#define head 0									//a head of node
#define tail 1									//a tail of node
string input_txt = "input.txt";					//input txt file    //dcb2086.txt //lsn3119.txt //pbk411.txt  //xqf131.txt

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


clock_t c_start, c_end;

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
	int startPoint = 1500;
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
		c_end = clock();
		double exe_time = (double)(c_end - c_start) / CLOCKS_PER_SEC;

		if (exe_time > 29.9) {
			break;
		}
		//if (try_i == 100000)
			//break;
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
	//				cout << opt_number++ << "번째 개선" << endl;
		//			double sum = sumPath(len, rt);
			//		cout << "Sum: " << sum << endl;
		}
		else
			try_i++;
	}
}

int point[NUM_OF_NODE][2];

//int(*point)[2],
void threeOpt_swap( int A, int B, int C, int At, int Bt, int Ct)
{/*
	int A, B, C;
	int At = point[A][tail];
	int Bt = point[B][tail];
	int Ct = point[C][tail];
	*/
	point[A][tail] = Bt;
	point[Bt][head] = A;
	point[B][tail] = Ct;
	point[Ct][head] = B;
	point[C][tail] = At;
	point[At][head] = C;


}


void threeOpt(int len, int *rt, double nowMin)
{

	double CurrentValue = nowMin;
	
	cout << "3-opt start" << '\n';


			//19				//2					//1
	//cout << rt[len - 1] << " " << rt[1] << " " << rt[len] << '\n';
	//cout << rt[0] << '\n'; //1
	point[0][tail] = rt[0];
	point[rt[0]][head] = rt[len - 1];
	point[rt[0]][tail] = rt[1];

	for (int i = 1; i <len; i++)
	{
		point[rt[i]][head]=rt[i-1];
		point[rt[i]][tail]=rt[i+1];
	}
	
	/*
	for (int i = 1; i <=len; i++)
	{
		cout << i << " -> " <<  point[i][tail] << '\n';
	}
	*/

	
	int try_i = 0;
	while (1)
	{
		if (try_i == 100000)
			break;
		
		int x = (rand() % (len - 2))+2;
		int y= (rand() % (len - 2)) + 2;
		int z = (rand() % (len - 2)) + 2;
		
		if (abs(x - y) <= 2)
			continue;
		if (abs(y - z) <= 2)
			continue;
		if (abs(z - x) <= 2)
			continue;
		
		int Numbering[3] = { x,y,z };
		sort(Numbering, Numbering + 3);
		x = Numbering[0];
		y = Numbering[1];
		z = Numbering[2];


		const int xx = x;
		const int yy = y;
		const int zz = z;

		const int xt = point[xx][tail];
		
		const int yt = point[yy][tail];
		
		const int zt = point[zz][tail];
		
		const int xh = point[xx][head];
		
		const int yh = point[yy][head];
		
		const int zh = point[zz][head];
		int d[9] = { xx, yy, zz ,xt, yt ,zt, xh, yh, zh };
		sort(d, d + 9);
		int k = 0;
		for (int i = 0; i < 8; i++)
			if (d[i] == d[i + 1])
			{
				k = 1;
				break;
			}
		if (k == 1)
			continue;
		
		double d1, d2, d3;
		d1 = dist[x][yt];
		d2 = dist[y][zt];
		d3 = dist[z][xt];
		double Nsum = d1 + d2 + d3;
		double Csum = dist[x][xt] + dist[y][yt] + dist[z][zt];

		if ((Csum - Nsum) > 0)
		{
		//	cout << Csum-Nsum << "\n";
			try_i = 0;
			CurrentValue = CurrentValue - Csum + Nsum;
			cout << xx << " " << yt << " " << yy << " " << zt << " " << xt << " " << zz << '\n';

			point[xx][tail] = yt;
			point[yt][head] = x;
			point[yy][tail] = zt;
			point[zt][head] = y;
			point[zz][tail] = xt;
			point[xt][head] = z;
			cout << xx << " " << yt << " " << yy << " " << zt << " " << xt << " " << zz << '\n';

			
			//threeOpt_swap(x, y, z, xt, yt, zt);
			
		}
		else
			try_i++;

	}
	
	
	cout << "3-opt end.the best value : " << CurrentValue << '\n';

	rt[0] = point[1][tail];
	
	for (int i = 1; i <=len; i++)
	{	
		rt[i]= point[rt[i-1]][tail];
	}



}

//int new_route[NUM_OF_NODE];

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
	for (int i = C; i>= E; i--)
	{
		new_route[k] = rt[i];
		k++;
	}
	for (int i = D; i <= B; i++)
	{
		new_route[k] = rt[i];
		k++;
	}
	for (int i = F; i <=len; i++)
	{
		new_route[k] = rt[i];
		k++;
	}

	int go=0;
	double newPath = sumPath(len, new_route);
	for(int i=0; i<=len; i++)
	rt[i] = new_route[i];
		/*	
	if (newPath <remembest)
	{
		for (int i = 0; i <= len; i++)
			remem_route[i] = new_route[i];
		remembest = newPath;
		go++;
	}
	*/
	
}

//int new_route1[NUM_OF_NODE];

void Swap_ThreeOpt2(int len, int *rt, int A, int B, int C, int D, int E, int F)
{
	
	int new_route[NUM_OF_NODE];

	int k = 0;
	for (int i = 0; i <= A; i++)
	{
		new_route[k] = rt[i];
		k++;
	}
	for (int i = E; i<= C; i++)
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

	int go = 0;
	double newPath = sumPath(len, new_route);
	double best = sumPath(len, rt);
	for (int i = 0; i <= len; i++)
		rt[i] = new_route[i];	//	return new_route;

	/*
	if (newPath <remembest)
	{
		for (int i = 0; i <= len; i++)
			remem_route[i] = new_route[i];
		remembest = newPath;
	}
	*/
	/*
	if (go == 1)
	{
		for (int i = 0; i <= len; i++)
			rt[i] = remem_route[i];
	}
	*/
}
//int new_route2[NUM_OF_NODE];

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

	int go = 0;
	double newPath = sumPath(len, new_route);
//	double best = sumPath(len, rt);
	for (int i = 0; i <= len; i++)
		rt[i] = new_route[i];	//	return new_route;

	/*
	if (newPath <remembest)
	{
		for (int i = 0; i <= len; i++)
			remem_route[i] = new_route[i];
		remembest = newPath;
	}
	*/

	
}

//int new_route3[NUM_OF_NODE];

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
	double newPath = sumPath(len, new_route);
	double best = sumPath(len, rt);
	for (int i = 0; i <= len; i++)
		rt[i] = new_route[i];
	//	return new_route;

	/*
	if (newPath <remembest)
	{
		for (int i = 0; i <= len; i++)
			remem_route[i] = new_route[i];
		remembest = newPath;
	}
	*/
}


int times = 1;

void three_opt(int len, int *rt)
{

/*	
	for(int i=0; i<=len; i++)
	remem_route[i] = rt[i];
	remembest = sumPath(len, remem_route);
	*/

	cout << "3-opt start" << '\n';

	int q = 0;

	int try_i = 0;

	while (1) {
		c_end = clock();
		double exe_time = (double)(c_end - c_start) / CLOCKS_PER_SEC;

		if (exe_time > 29) {
			break;
		}
		if (try_i == 1000000)
			break;

		int A = (rand() % (len - 6)) + 2;
		int B = A + (rand() % 5) + 2;
		if (B+2 >=len)
			B = B - len+3;
		int C = B + (rand() % 5) + 2;
		if (C+2>=len)
			C = C - len+3;
	/*	
		int d[3] = { A, B, C };
		sort(d, d + 3);
		A = d[0]; B = d[1]; C = d[2];
		*/
		
		if (A==B)
			continue;
		if (B==C)
			continue;

	

		int D = A + 1; //a-d
		int E = B + 1;// b-e
		int F = C + 1;//f-c


		double x = dist[rt[A]][rt[D]]; //a~an의 길이
		double y = dist[rt[B]][rt[E]];//b~ bn의 길이
		double z = dist[rt[C]][rt[F]];//c~cn의 길이
		
		double d0 = dist[rt[A]][rt[D]] + dist[rt[B]][rt[E]] + dist[rt[C]][rt[F]]; // 현재길이
		double d1 = dist[rt[A]][rt[C]] + dist[rt[D]][rt[E]] + dist[rt[B]][rt[F]];
		double d2= dist[rt[A]][rt[E]]+dist[rt[D]][rt[C]]+dist[rt[B]][rt[F]];
		double d3= dist[rt[A]][rt[B]]+dist[rt[E]][rt[F]]+dist[rt[C]][rt[D]];
		double d4= dist[rt[A]][rt[E]]+dist[rt[C]][rt[B]]+dist[rt[F]][rt[D]];


		double p0 = sumPath(len, rt);
//		double p1 = 0;
//		double p2 = 0;
//		double p3 = 0;
//		double p4 = 0;


		if (d0 > d1)
		{

		//	cout << delta << " " << d1 << '\n';
			try_i = 0;
			Swap_ThreeOpt1(len, rt, A, B, C, D, E, F);
			q++;

		//	cout <<q<< " d1 " << sumPath(len, remem_route) << " "<< sumPath(len, rt)  <<'\n';
	//		sumPath(len, rt1);
		}
		else if(d0 > d2)
		{
			try_i = 0;
			Swap_ThreeOpt2(len, rt, A, B, C, D, E, F);
			q++;
			//cout <<q<< " d2 " << sumPath(len, remem_route) << " " << sumPath(len, rt) << '\n';
	//		p2 = sumPath(len, rt2);
		}
		else if (d0 > d3)
		{
			try_i = 0;
			Swap_ThreeOpt3(len, rt, A, B, C, D, E, F);
			q++;
		//	cout << q << " d3 " << sumPath(len, remem_route) << " " << sumPath(len, rt) << '\n';
	//		p3 = sumPath(len, rt3);
		}	
		else if (d0 > d4)
		{
			try_i = 0;
			Swap_ThreeOpt4(len, rt, A, B, C, D, E, F);
			q++;
		//	cout << q << " d4 " << sumPath(len, remem_route) << " " << sumPath(len, rt) << '\n';
		//	sumPath(len, rt4);
		}
		else {
			//cout << q << "d0" << sumPath(len, rt) << " " << sumPath(len, rt) << '\n';
			try_i++;
		}
		if (q == 5000)
			break;


		//if (p0 > sumPath(len, rt)) 
		//	cout << q << " best: " << sumPath(len, rt) << '\n';

		//	for (int i = 0; i <= len; i++)
			//	rt[i] = remem_route[i];


	}
	
	
	cout << "3-opt end." << '\n';


}


void SA(int len, double T, int * route) {
	int i = 1;
	double best = sumPath(len, route);
	while (T > 1) {
		cout << i << "번째 SA" << endl;
		int new_route[NUM_OF_NODE];
		for (int i = 0; i <= len; i++)
			new_route[i] = route[i];
		int aa = 0;
		while (1) {
			if (aa == (int)1)
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

	//clock_t c_start, c_end;
	c_start = clock();

	//calculate distance from i-node to j-node 
	calcDist(len);

	//calculate first TSP Path
	NearestNeighbor(len, route);
//	random(len, route);


	//Optimization
//	three_opt(len, route);

	double law = sumPath(len, route);
	cout << "RAW ROUTE: " << law  << '\n';

	
	twoOpt(len, 10000000, route);

	
//SA(len, 50, route);

//	three_opt(len, route);

	//sum path
	double sum = sumPath(len, route);
	cout << "2opt Best route: " << remembest <<" 2opt+3opt Best route: " << sum << endl;

	
	
	//print excute time
	c_end = clock();
	double exe_time = (double)(c_end - c_start) / CLOCKS_PER_SEC;
	cout << "Execute time: " << exe_time << "seconds" << endl;


	
	//print PATH
	//printPath(len, route);

	//3-opt	
	//threeOpt(len, route, sum);
	
//	three_opt(len, sum, route);

	printPath(len, route);

	

}
