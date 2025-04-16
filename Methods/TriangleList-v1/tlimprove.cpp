#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <map>
#include <fstream>
#include <unordered_map>
#include "BOBHASH32.h"
#include "params.h"
#include "ssummary.h"
#include "CuckooCounter.h"
#include <string.h>
#include "matrix3.h"
#include <vector>
#include "Graph.h"
#include "Edge.h"
#include <sstream>
#include <utility>
#include "TopNei.h"
using namespace std;

map <string ,int> B,C;
unordered_map<int, string> nodes;

struct node {string x;int y;} p[300002];
//ifstream fin("../../real_data/1.dat",ios::in|ios::binary);
string s[300002];
char tmp[1005];
int cmp(node i,node j) {return i.y>j.y;}
int main()
{
    int MEM=400,K=100;
    int c;
    char dataset[70]={'\0'};
    Graph graph;
    vector<Edge> edges;
    LabelStatistics stats; 
    int m_fl=0;
    // preparing cuckoocounter
    int cc_M;
    for (cc_M = 1; 32 * cc_M*CC_d + 432 * K <= MEM * 1024 * 8; cc_M++); if (cc_M % 2 == 0) cc_M--;
    cuckoocounter *cc; cc = new cuckoocounter(cc_M, K); cc->clear();
    char default_dataset[70]="./dataset.csv";
	ifstream fin(dataset, ios::in);
	if (!fin)
    {
        cerr << "Open Failed" << endl;
        exit(1);
    }
    string line;
    getline(fin, line);
	int i=1;
    while (getline(fin, line))
    {
        vector<string> data_line;
        string number;
        istringstream readstr(line);
        for (int j = 0; j < 5; j++)
        {
            getline(readstr, number, ',');
            data_line.push_back(number);
        }
        if(data_line[1]==data_line[2]) continue;
        update_neighbors(stoi(data_line[1]), stoi(data_line[2]), 1.0, 50);
        update_neighbors(stoi(data_line[2]), stoi(data_line[1]), 1.0, 50);
        nodes[stoi(data_line[1])] = data_line[3];
        nodes[stoi(data_line[2])] = data_line[4];
		s[i] = data_line[0];
		B[s[i]]++;
		i++;
        m_fl++;

        graph.addEdge(stoi(data_line[1]), stoi(data_line[2]), 1);
        edges.push_back(Edge(stoi(data_line[0]), stoi(data_line[1]), stoi(data_line[2]), data_line[3], data_line[4], 1));
	}
	
	//CC
	for (int i = 1; i <= m_fl; i++) {
		cc->Insert(s[i]);
	}
	
	cc->work();
	
	int cnt=0;
    for (map <string,int>::iterator sit=B.begin(); sit!=B.end(); sit++)
    {
        p[++cnt].x=sit->first;
        p[cnt].y=sit->second;
    }
    sort(p+1,p+cnt+1,cmp);
    for (int i=1; i<=K; i++) C[p[i].x]=p[i].y;

    // Calculating PRE, ARE, AAE
    cout<<"Calculating\n"<<endl;
	int cc_sum = 0, cc_AAE = 0; double cc_ARE = 0;
	string cc_string; int cc_num;
    vector<Triplet> triangle_result;
    unordered_map<Triplet, int> int_result;
    int num=0;

	for (int i = 0; i < K; i++)
	{
		cc_string = (cc->Query(i)).first; cc_num = (cc->Query(i)).second;
		cc_AAE += abs(B[cc_string] - cc_num); cc_ARE += abs(B[cc_string] - cc_num) / (B[cc_string] + 0.0);
		if (C[cc_string]) cc_sum++;

        for(const Edge& edge : edges){
            if(stoi(cc_string)==edge.id){
                string node1 = to_string(edge.u);
                string node2 = to_string(edge.v);
                int a=edge.u;
                int b = edge.v;
                unordered_set<int> result = common_neighbor(a,b);
                for (const auto& c : result) {
                    Triplet newTriplet(a, b, c);
                    if(findValue(int_result, newTriplet) == false){
                        insertValue(int_result, newTriplet, hash_and_sort(a, b, c));
                        num++;
                    }
                    else{
                        continue;
                    }

                }
            }
        }

	}
    
	int count=0;
    for (const Triplet& it : triangle_result) {
        int a=it.a;
        int b=it.b;
        int c=it.c;
        count++;
        string la = nodes[a].labels;
        string lb = nodes[b].labels;
        string lc = nodes[c].labels;
        count++;
        int node_sum = graph.inDegree(a)+graph.inDegree(b)+graph.inDegree(c);
        int edge_sum = graph.tWeightSum(a, b, c);
        double label_sum = calculateDiversity(stats.getP(la), stats.getP(lb), stats.getP(lc));
        double ps = node_sum + edge_sum + label_sum;
        cout << "(" << a << ", " << b << ", " << c << ")";
        cout << "(" << la << ", " << lb << ", " << lc << ")"<< ps << endl;
    }
    cout<<"count: "<<count<<endl;
    printf("cuckoocounter:\nAccepted: %d/%d  %.10f\nARE: %.10f\nAAE: %.10f\n\n", cc_sum, K, (cc_sum / (K + 0.0)), cc_ARE / K, cc_AAE / (K + 0.0));
    cout<<"num: "<<num<<endl;
    system("pause");
	return 0;
}
