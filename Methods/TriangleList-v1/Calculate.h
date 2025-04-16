#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <tuple>
#include <cmath>
#include <unordered_map>
// #include "Graph.h"

using namespace std;

struct Edge {
    int id, u, v, t; 
    string lu, lv; 
    Edge(int id, int u, int v, const string& lu, const string& lv, int t) : id(id), u(u), v(v), lu(lu), lv(lv), t(t) {}
};

struct Node {
    set<int> neighbors;    
    string labels; 

    void print_nei() {
        for(set<int>::iterator it=neighbors.begin();it!=neighbors.end();it++){
		    cout << *it<<" ";
	    }
    }

};

typedef tuple<int, int, int> Triplet;

vector<Triplet> removeDuplicates(vector<Triplet>& triplets) {
    set<int> uniqueElements; 
    vector<Triplet> result; 

    for (const Triplet& triplet : triplets) {
        int a, b, c;
        tie(a, b, c) = triplet;

        if (uniqueElements.count(a) == 0 || uniqueElements.count(b) == 0 || uniqueElements.count(c) == 0) {
            result.push_back(triplet);
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
