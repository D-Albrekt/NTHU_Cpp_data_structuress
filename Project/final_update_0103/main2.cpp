/***********************************************/
//         This .cpp is for Problem2           //
/***********************************************/
#include <iostream>
#include "basicDS.h"
#include "Problem2.cpp"
#include <fstream>
#include <string>
#include <queue>

#include <sys/times.h>
#include <unistd.h>
#include <cstdio>


void graph_input(Graph& G) {
	int vertex_num, edge_num;
	cin >> vertex_num >> edge_num;

	for (int i = 1; i <= vertex_num; i++) {
		G.V.push_back(i);
	}

	for (int i = 0; i < edge_num; i++) {
		graphEdge gE;
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		gE.vertex[0] = a;
		gE.vertex[1] = b;
		gE.b = c;
		gE.be = c;
		gE.ce = d;
		G.E.push_back(gE);
	}
}

void insert_input(int& id, int& s, int& t, Set& D, string input_string) {

	queue<string> q;

	while (1) {
		q.push(input_string.substr(0, input_string.find(" ")));
		input_string = input_string.substr(input_string.find(" ") + 1, input_string.length());

		if (input_string.find(" ") == -1) {
			q.push(input_string);
			break;
		}
	}

	q.pop();
	id = stoi(q.front());
	q.pop();
	s = stoi(q.front());
	q.pop();
	q.pop();

	while (1) {
		string tmp_s = q.front();
		q.pop();
		if (tmp_s == "}") { break; }
		int tmp_i = stoi(tmp_s);
		D.destinationVertices.push_back(tmp_i);
		D.size++;
	}

	t = stoi(q.front());
	q.pop();
}

int stop_input(string input_string) {
	string tmp_s = input_string.substr(input_string.find(" ") + 1, input_string.length());
	return stoi(tmp_s);
}

int main(void) {

	Graph G;
	Tree T;
	Forest F;
	graph_input(G);

	Problem2 P2(G);

	struct tms  tmsstart, tmsend;
    clock_t     start, end;
    static long     clktck = 0;
    clktck = sysconf(_SC_CLK_TCK);
    start = times(&tmsstart);
	
	string input_string;
	int i{0};
	while (getline(cin, input_string)) {
		std::cout << i++ << ' ' << input_string << endl;
		if (input_string[0] == 'i') {
			std::cout << "insert" << endl;
			int id, s, t;
			Set D;
            bool take;
			insert_input(id, s, t, D, input_string);
			take = P2.insert(id, s, D, t, G, T);
			
			if (take)
			{
				std::cout << "Success" << std::endl;
			}
			else{
				std::cout << "Fail" << std::endl;
			}
			

		}
		else if (input_string[0] == 's') {
			std::cout << "stop" << endl;
			int id = stop_input(input_string);
			P2.stop(id, G, F);

		}
		else if (input_string[0] == 'r') {
			
			std::cout << "rearrange" << endl;
			P2.rearrange(G, F);
		}
	}
	end = times(&tmsend);

    printf(" real:  %7.7f\n", (end-start) / (double) clktck);
    printf(" user:  %7.7f\n",
            (tmsend.tms_utime - tmsstart.tms_utime) / (double) clktck);
    printf(" sys:   %7.7f\n",
            (tmsend.tms_stime - tmsstart.tms_stime) / (double) clktck);
	return 0;
}
