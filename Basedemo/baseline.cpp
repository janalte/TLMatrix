#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <tuple>
#include <string>
#include<set>

using namespace std;

struct Edge {
    int u, v, t;
    string lu, lv;
};

int main() {
    vector<Edge> edges = {{1, 2, 1, "A", "B"}, {2, 3, 2, "B", "C"}, {1, 3, 3, "A", "C"}};
    map<int, string> nodeLabels; 
    map<tuple<int, string>, set<int>> nodeNeighbors;
    vector<tuple<int, int, int, string, string, string, int, int, int>> triangles;

    for (const Edge& edge : edges) {
        nodeLabels[edge.u] = edge.lu;
        nodeLabels[edge.v] = edge.lv;
        nodeNeighbors[{edge.u, edge.lu}].insert(edge.v);
        nodeNeighbors[{edge.v, edge.lv}].insert(edge.u);
    }

    for (const Edge& edge : edges) {
        int u = edge.u;
        int v = edge.v;
        int t = edge.t;
        string lu = edge.lu;
        string lv = edge.lv;
        
        for (int w : nodeNeighbors[{u, lu}]) {
            if (nodeNeighbors[{v, lv}].count(w) && w != u && w != v) {
                triangles.push_back(make_tuple(u, v, w, lu, lv, nodeLabels[w], t, 1, 1));
            }
        }
    }

    for (const auto& triangle : triangles) {
        cout << "Triangle: (" << get<0>(triangle) << ", " << get<1>(triangle) << ", " << get<2>(triangle)
             << ") Labels: (" << get<3>(triangle) << ", " << get<4>(triangle) << ", " << get<5>(triangle)
             << ") Degrees: (" << get<7>(triangle) << ", " << get<8>(triangle) << ", " << get<6>(triangle)
             << ") Time: " << get<6>(triangle) << endl;
    }
    system("pause");
    return 0;
}
