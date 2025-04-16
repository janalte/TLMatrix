#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <string>

using namespace std;

class Graph {
public:
    
    Graph() {}

    void addEdge(int start, int end, int weight) {
        edges[start][end] = weight;
    }

    int outDegree(int node) {
        if (edges.find(node) != edges.end()) {
            return edges[node].size();
        } else {
            return 0;
        }
    }

    int inDegree(int node) {
        int inDegreeCount = 0;
        for (const auto& edge : edges) {
            for (const auto& neighbor : edge.second) {
                if (neighbor.first == node) {
                    inDegreeCount++;
                }
            }
        }
        return inDegreeCount;
    }

    int getEdgeWeight(int start, int end) {
        if (edges.find(start) != edges.end() && edges[start].find(end) != edges[start].end()) {
            return edges[start][end];
        } else {
            return -1; 
        }
    }

    bool hasEdge(int start, int end) {
        return edges.find(start) != edges.end() && edges[start].find(end) != edges[start].end();
    }

private:
    map<int, map<int, int>> edges; 
};

// int main() {
//     Graph graph;
//     graph.addEdge(1, 2, 1);
//     graph.addEdge(3, 2, 1);
//     graph.addEdge(1, 3, 1);
//     graph.addEdge(4, 5, 1);
//     graph.addEdge(5, 6, 1);
//     graph.addEdge(6, 4, 1);
//     graph.addEdge(1, 4, 1);
//     graph.addEdge(4, 3, 1);


//     int weight = graph.getEdgeWeight(1, 2);
//     if (weight >= 0) {
//         cout << "Edge weight from node 2 to node 4: " << weight << endl;
//     } else {
//         cout << "Edge does not exist or weight is negative." << endl;
//     }


//     int outDeg = graph.outDegree(1);
//     int inDeg = graph.inDegree(3);
//     cout << "Out-Degree of node 2: " << outDeg << endl;
//     cout << "In-Degree of node 2: " << inDeg << endl;

//     system("pause");
//     return 0;
// }
