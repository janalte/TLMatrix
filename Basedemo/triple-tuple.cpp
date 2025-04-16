#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <set>
using namespace std;


typedef tuple<int, int, int> Triplet;

vector<Triplet> removeDuplicates(vector<Triplet>& triplets) {
    set<int> uniqueElements; 
    vector<Triplet> result;  

    for (const Triplet& triplet : triplets) {
        int a, b, c;
        tie(a, b, c) = triplet;

        if (uniqueElements.count(a) == 0 && uniqueElements.count(b) == 0 && uniqueElements.count(c) == 0) {
            result.push_back(triplet);
            uniqueElements.insert(a);
            uniqueElements.insert(b);
            uniqueElements.insert(c);
        }
    }

    return result;
}

int main() {
    vector<Triplet> triplets = {
        make_tuple(1, 2, 3),
        make_tuple(2, 3, 1),
        make_tuple(3, 2, 1),
        make_tuple(4, 4, 4),
        make_tuple(1, 2, 3),
        make_tuple(5, 6, 7),
        make_tuple(7, 6, 5),
    };

    vector<Triplet> uniqueTriplets = removeDuplicates(triplets);

    for (const Triplet& triplet : uniqueTriplets) {
        int a, b, c;
        tie(a, b, c) = triplet;
        cout << "(" << a << ", " << b << ", " << c << ")" << endl;
    }
    system("pause");
    return 0;
}
