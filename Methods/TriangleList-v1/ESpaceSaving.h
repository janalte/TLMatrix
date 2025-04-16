#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
#include <string>
#include <fstream>

using namespace std;

// pair<int,int> id;

struct EdgeItem
{
    string id;      
    int weight;     
    int error;     
    int index;     

    
    EdgeItem(string a, int b, int c, int d)
    {
        id = a;
        weight = b;
        error = c;
        index = d;
    }
};

typedef unordered_map<string, EdgeItem *> umsn;
typedef vector<EdgeItem *> vn;

class SpaceSaving
{
private:
    vn minHeap;    
    int k;          
    umsn dict;     

public:
    SpaceSaving(int capacity);  
    ~SpaceSaving();             

    void swap(EdgeItem *a, EdgeItem *b);  

 
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return (2 * i + 1); }
    int right(int i) { return (2 * i + 2); }

    void spaceSaving(string id);   
    void increaseKey(int i);        
    vector<pair<int,int>> print();                   
};


SpaceSaving::SpaceSaving(int capacity)
{
    k = capacity;
    minHeap.resize(k, nullptr);

    
    for (int i = 0; i < k; i++)
    {
        EdgeItem *n = new EdgeItem("dummy", 0, 0, i);
        minHeap[i] = n;
    }
}


SpaceSaving::~SpaceSaving()
{
    for (auto &&i : minHeap)
    {
        delete i;
    }
    minHeap.clear();
    dict.clear();
}


void SpaceSaving::swap(EdgeItem *a, EdgeItem *b)
{
    EdgeItem *tmp1 = new EdgeItem(a->id, a->weight, a->error, a->index);
    EdgeItem *tmp2 = new EdgeItem(b->id, b->weight, b->error, b->index);

  
    a->id = tmp2->id, a->weight = tmp2->weight, a->error = tmp2->error;
    b->id = tmp1->id, b->weight = tmp1->weight, b->error = tmp1->error;


    if (dict.find(tmp1->id) != dict.end())
    {
        dict[tmp1->id] = b;
    }

    if (dict.find(tmp2->id) != dict.end())
    {
        dict[tmp2->id] = a;
    }
}


void SpaceSaving::spaceSaving(string id)
{
  
    if (dict.find(id) != dict.end())
    {
        int i = dict[id]->index;
        increaseKey(i);
    }
 
    else
    {
        EdgeItem *min = minHeap[0];

        if (min->id != "dummy")
        {
            dict.erase(min->id);

           
            EdgeItem *n = new EdgeItem(id, min->weight, min->weight, 0);
            minHeap[0] = n;
            dict[id] = n;

           
            increaseKey(0);
        }
        else
        {
            EdgeItem *n = new EdgeItem(id, min->weight, min->weight, 0);
            minHeap[0] = n;
            dict[id] = n;
            increaseKey(0);
        }
    }
}


void SpaceSaving::increaseKey(int i)
{
minHeap[i]->weight += 1;

 
    while (left(i) < k || right(i) < k)
    {
        int curr = minHeap[i]->weight;

        if (left(i) < k && right(i) < k)
        {
            int leftChild = minHeap[left(i)]->weight;
            int rightChild = minHeap[right(i)]->weight;
            int smallerChild = (leftChild <= rightChild) ? leftChild : rightChild;
            int smallerChildIndex = (leftChild <= rightChild) ? left(i) : right(i);

            
            if (curr > smallerChild)
            {
                swap(minHeap[i], minHeap[smallerChildIndex]);
                i = smallerChildIndex;
            }
            else
            {
                break;
            }
        }
        else if (left(i) < k)
        {
            int smallerChild = minHeap[left(i)]->weight;
            int smallerChildIndex = left(i);

            if (curr > smallerChild)
            {
                swap(minHeap[i], minHeap[smallerChildIndex]);
                i = smallerChildIndex;
            }
            else
            {
                break;
            }
        }
        else
        {
            cout << "Should not run into this case" << std::endl;
           
            if (curr > minHeap[right(i)]->weight)
            {
                swap(minHeap[i], minHeap[right(i)]);
                i = right(i);
            }
            else
            {
                break;
            }
        }
    }
}
vector<pair<int,int>> heavyedge;

vector<pair<int,int>> SpaceSaving::print()
{
    ofstream ofs;
    string filename = "spacesaving-phone/ss-heavy-edge.csv";
    ofs << "id"<< "," << "weight" << "," << "error" <<endl;
    ofs.open(filename, ios::out);
    for (int i = 0; i < k; i++)
    {
        cout << "Item: " << minHeap[i]->id << "; ";
        cout << "Weight: " << minHeap[i]->weight << "; ";
        cout << "Error: " << minHeap[i]->error << "\n";
  
        ofs << minHeap[i]->id << "," << minHeap[i]->weight << "," << minHeap[i]->error <<endl;
        heavyedge.push_back(make_pair(stoi(minHeap[i]->id),minHeap[i]->weight));

    }
    return heavyedge;
}

#endif // SPACESAVING_H