#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <tuple>
#include <cmath>
// #include "Graph.h"

using namespace std;

// 定义边的结构
struct Edge {
    int id, u, v, t;        // 起点、终点、时间戳
    string lu, lv;       // 起点标签、终点标签
    
    Edge(int id, int u, int v, const string& lu, const string& lv, int t) : id(id), u(u), v(v), lu(lu), lv(lv), t(t) {}
};

// 定义节点的结构
struct Node {
    set<int> neighbors;     // 邻居节点集合
    string labels; // 标签

    void print_nei() {
        for(set<int>::iterator it=neighbors.begin();it!=neighbors.end();it++){
		    cout << *it<<" ";
	    }
    }

};

// 定义一个三元组类型
typedef tuple<int, int, int> Triplet;

// 去重函数，仅保留三个元素都不同的三元组
vector<Triplet> removeDuplicates(vector<Triplet>& triplets) {
    set<int> uniqueElements; // 用于跟踪唯一的元素
    vector<Triplet> result;  // 用于存储去重后的三元组

    for (const Triplet& triplet : triplets) {
        int a, b, c;
        tie(a, b, c) = triplet;

        // 检查当前三元组是否至少有一个元素与其他元组不同
        if (uniqueElements.count(a) == 0 || uniqueElements.count(b) == 0 || uniqueElements.count(c) == 0) {
            result.push_back(triplet);

            // 将这三个元素添加到uniqueElements中
            uniqueElements.insert(a);
            uniqueElements.insert(b);
            uniqueElements.insert(c);
        }
    }

    return result;
}
void printTriplets(const vector<Triplet>& triplets) {
    for (const Triplet& triplet : triplets) {
        int a, b, c;
        tie(a, b, c) = triplet;
        cout << "(" << a << ", " << b << ", " << c << ")" << endl;
    }
}

double calculateDiversity(double P1, double P2, double P3) {
    if (P1 == 0.0 || P2 == 0.0 || P3 == 0.0) {
        return 0.0;  // 避免计算log(0)
    }

    double diversity = -(P1 * log2(P1) + P2 * log2(P2) + P3 * log2(P3));
    return diversity;
}
