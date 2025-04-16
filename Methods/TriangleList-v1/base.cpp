#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <set>
#include <algorithm>
#include <tuple>
#include <ctime>
#include <fstream>
#include <unordered_map>
#include "ESpaceSaving.h"
#include "Graph.h"
#include "Calculate.h"

int main()
{
    vector<string> input;//space saving结构
    Graph graph;
    vector<Edge> edges;
    LabelStatistics stats; 

    ifstream ifs("./dataset.csv");
    if (!ifs) {
        cerr << "无法打开文件！" << endl;
        return 1;
    }

    string line;
    getline(ifs, line);
    while (getline(ifs, line))
    {
        // 对EdgeID,StartNodeID,EndNodeID,StartNodeLabel,EndNodeLabel这个形式进行解析
        vector<string> data_line;
        string number;
        istringstream readstr(line);
        for (int j = 0; j < 5; j++)
        {
            getline(readstr, number, ',');
            data_line.push_back(number);
        }
        stats.addLabel(data_line[3]);
        stats.addLabel(data_line[4]);
        input.push_back(data_line[0]);
        int a=1;
        graph.addEdge(stoi(data_line[1]), stoi(data_line[2]), a);
        edges.push_back(Edge(stoi(data_line[0]), stoi(data_line[1]), stoi(data_line[2]), data_line[3], data_line[4], a));
       
    }
    int capacity = 50;
    SpaceSaving obj(capacity);

    clock_t t;
    t = clock();
    for (auto &&id : input)
    {
        obj.spaceSaving(id);
    }
    t = clock() - t;

    double time = ((double)t) / CLOCKS_PER_SEC;
    cout << "\n";

    obj.print();

    map<int, Node> nodes; 

    for (const Edge& edge : edges) {
        nodes[edge.u].neighbors.insert(edge.v); 
        nodes[edge.v].neighbors.insert(edge.u);
        nodes[edge.u].labels = edge.lu;
        nodes[edge.v].labels = edge.lv;
    }
    vector<Triplet> triangle;
    for (const auto& item : heavyedge){
        for(const Edge& edge : edges){
            if(edge.id==item.second){
                int u = edge.u;               
                int v = edge.v;
                // cout<< u<<endl;
                set<int> w;
                set_intersection(nodes[u].neighbors.begin(), nodes[u].neighbors.end(),nodes[v].neighbors.begin(), nodes[v].neighbors.end(), inserter(w, w.begin())); 
                for(set<int>::iterator it=w.begin();it!=w.end();it++){
		            // cout << "u"<<u<<"v"<<v<<"w"<<*it<<" ";
                    Triplet newTriplet = make_tuple(u, v, *it);
                    triangle.push_back(newTriplet);
	            }
            }
        }
    }
    vector<Triplet> result=removeDuplicates(triangle);
    printTriplets(result);
    int count=0;
     for (const Triplet& it : result) {
        int a, b, c;
        tie(a, b, c) = it;
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

    system("pause");

    return 0;
}