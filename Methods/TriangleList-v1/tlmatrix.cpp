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
    int MEM=200,K=100;
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
	if(dataset[0]=='\0') strcpy(dataset, default_dataset);
	cout<<"dataset: "<<dataset<<endl<<endl;
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
        nodes[stoi(data_line[1])] = data_line[3];
        nodes[stoi(data_line[2])] = data_line[4];
    
		neigh_update(data_line[1], data_line[3], data_line[2], data_line[4], 1);
        neigh_update(data_line[2], data_line[4], data_line[1], data_line[3], 1);

		s[i] = data_line[0];
		B[s[i]]++;
		i++;
        m_fl++;
        stats.addLabel(data_line[3]);
        stats.addLabel(data_line[4]);

        graph.addEdge(stoi(data_line[1]), stoi(data_line[2]), 1);
        edges.push_back(Edge(stoi(data_line[0]), stoi(data_line[1]), stoi(data_line[2]), data_line[3], data_line[4], 1));
	}
    // for(int i = 0; i < m; i++)
    // {
    //     if(matrix[i][0].neigh_fp=="70"||matrix[i][0].neigh_fp=="6"){
    //     for(int j = 0; j < m; j++)
    //     {

    //         cout << matrix[i][j].neigh_fp << " " <<matrix[i][j].label << " " << matrix[i][j].weight << "; " ;
    //     }
    //     }
    //     cout << endl;
    // }

	//CC
	for (int i = 1; i <= m_fl; i++) {
		cc->Insert(s[i]);
	}
	cc->work();
	
    printf("\npreparing true flow\n");

	// preparing true flow
	int cnt=0;
    for (map <string,int>::iterator sit=B.begin(); sit!=B.end(); sit++)
    {
        p[++cnt].x=sit->first;
        p[cnt].y=sit->second;
    }
    sort(p+1,p+cnt+1,cmp);
    for (int i=1; i<=K; i++) {
        C[p[i].x]=p[i].y;
    }

    // Calculating PRE, ARE, AAE
    cout<<"Calculating\n"<<endl;
	int cc_sum = 0, cc_AAE = 0; double cc_ARE = 0;
	string cc_string; int cc_num;
    vector<Triplet> triangle_result;
    // vector<Cell> tempresult = neigh_query("70", "6", 1);
    // for (const Cell& element : tempresult) {
    //     cout <<"70-6:"<< element.neigh_fp << " ";
   
    // }
	for (int i = 0; i < K; i++)
	{
		cc_string = (cc->Query(i)).first; cc_num = (cc->Query(i)).second;
        
		cc_AAE += abs(B[cc_string] - cc_num); cc_ARE += abs(B[cc_string] - cc_num) / (B[cc_string] + 0.0);
        cout<<cc_string<<" "<<B[cc_string]<<" "<<cc_num<<endl;
		if (C[cc_string]) cc_sum++;
        for(const Edge& edge : edges){
            if(stoi(cc_string)==edge.id){
                string node1 = to_string(edge.u);
                string node2 = to_string(edge.v);
                int a=edge.u;
                int b=edge.v;
                vector<Cell> result = neigh_query(node1, node2, 1);
               
                for (const Cell& element : result) {
                    // cout << element.neigh_fp << " ";
                    int c=stoi(element.neigh_fp);
                    Triplet newTriplet(a, b, c);
                    // triangle.push_back(newTriplet);
                    if(findValue(triangle_result, newTriplet) == false){
                        insertValue(triangle_result, newTriplet, hash_and_sort(a, b, c));
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
    cout<<"count"<<count<<endl;
    printf("cuckoocounter:\nAccepted: %d/%d  %.10f\nARE: %.10f\nAAE: %.10f\n\n", cc_sum, K, (cc_sum / (K + 0.0)), cc_ARE / K, cc_AAE / (K + 0.0));

    system("pause");
	return 0;
}

int hash_and_sort(int a, int b, int c) {
    int arr[3] = {a, b, c};
    sort(arr, arr + 3);
    size_t seed = 0;
    
    seed ^= static_cast<size_t>(arr[0]) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    seed ^= static_cast<size_t>(arr[1]) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    seed ^= static_cast<size_t>(arr[2]) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    
    return static_cast<int>(seed & 0x7FFFFFFF); 
}

void insertValue(unordered_map<Triplet, int>& myMap, const Triplet& key, int value) {
    myMap[key] = value;
}

bool findValue(const unordered_map<Triplet, int>& myMap, const Triplet& key) {
    auto it = myMap.find(key);
    if (it != myMap.end()) {
        return true;
    } else {
        return false;
    }
}