#include <glut.h>
#include <fstream>
#include <string>
#include <ctime>
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

static int ortho = 0;

string input_txt = "input.txt"; //lsn3119.txt
string result_txt = "result.txt";

int len = -1;

int max_x = 0, max_y = 0;
vector<pair<int, int>> v;
int path[10000] = {0};


static void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glPointSize(3.0);
	glColor3f(1, 0, 0);
	glLoadIdentity();

	glOrtho(-10, max_x + 10, -10, max_y + 10, -1.0, 0.0);

	glBegin(GL_POINTS);
	for (int i = 1; i <= len; i++)
	{
		glVertex2f(v[i].first, v[i].second);
	}
	glEnd();

	
	glColor3f(0, 0, 1);
	glLineWidth(0.5);

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <=len; i++)
	{
		glVertex2f(v[path[i]].first, v[path[i]].second);
	}
	glEnd();
	
	glFinish();
}


void main() {
	ifstream fin(input_txt);
	ifstream fout(result_txt);

	string s;

	getline(fin, s);

	for (int i = 0; i < 7; i++)
		getline(fin, s, ' ');
	fin >> len;
	if (len < 0)
		cout << "length_error" << endl;

	//dummy data
	while (s != "NODE_COORD_SECTION") {
		getline(fin, s);
	}

	//input Node 1 ~ len 
	v.push_back({ 0,0 });
	for (int i = 0; i < len; i++) {
		int a, x, y;
		fin >> a >> x >> y;
		v.push_back(make_pair(x, y));
		if (x > max_x)
			max_x = x;
		if (y > max_y)
			max_y = y;
	}
	fin.clear();
	fin.close();

	
	for (int i = 0; i <= len; i++) {
		int a;
		fout >> a;
		path[i] = a;
	}


	fout.clear();
	fout.close();


	glutInitWindowSize(1200, 600);
	glutCreateWindow("TSP VIEWER");
	glShadeModel(GL_FLAT);
	glutDisplayFunc(display);
	glClearColor(1, 1, 1, 0);
	glutReshapeFunc(reshape);
	glutMainLoop();
}
