#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <string>
#include <unordered_map>

using namespace std;

class Graph{
public:
    Graph() {}
    void addEdge(int start, int end, int weight) {
        directed_edges[start][end] = weight;
    }
    int outDegree(int node) {
        if (directed_edges.find(node) != directed_edges.end()) {
            return directed_edges[node].size();
        } else {
            return 0;
        }
    }
    int inDegree(int node) {
        int inDegreeCount = 0;
        for (const auto& edge : directed_edges) {
            for (const auto& neighbor : edge.second) {
                if (neighbor.first == node) {
                    inDegreeCount++;
                }
            }
        }
        return inDegreeCount;
    }
    int getEdgeWeight(int start, int end) {
        if (directed_edges.find(start) != directed_edges.end() && directed_edges[start].find(end) != directed_edges[start].end()) {
            return directed_edges[start][end];
        } else {
            return -1; 
        }
    }
    bool hasEdge(int start, int end) {
        return directed_edges.find(start) != directed_edges.end() && directed_edges[start].find(end) != directed_edges[start].end();
    }
    int tWeightSum(int node1, int node2, int node3) {
        int weightSum = 0;
        
        if (graph.hasEdge(node1, node2)) {
            weightSum += graph.getEdgeWeight(node1, node2);
        } 
        if (graph.hasEdge(node2, node3)) {
            weightSum += graph.getEdgeWeight(node2, node3);
        }
        if (graph.hasEdge(node3, node1)) {
            weightSum += graph.getEdgeWeight(node3, node1);
        }
        if (graph.hasEdge(node2, node1)) {
            weightSum += graph.getEdgeWeight(node2, node1);
        }
        if (graph.hasEdge(node3, node2)) {
            weightSum += graph.getEdgeWeight(node3, node2);
        }
        if (graph.hasEdge(node1, node3)) {
            weightSum += graph.getEdgeWeight(node1, node3);
        }
        return weightSum;
    }

private:
    map<int, map<int, int>> directed_edges;  
};

class LabelStatistics {
    private:
        unordered_map<string, int> label_counts;
        int total_labels;
    
    public:
        LabelStatistics() : total_labels(0) {}
    
        void addLabel(const string& label) {
            label_counts[label]++;
            total_labels++;
        }
 
        int getTotalLabels() const {
            return total_labels;
        }
    
        int getUniqueLabelsCount() const {
            return label_counts.size();
        }
        double getP(const string& label) const {
            auto it = label_counts.find(label);
            if (it == label_counts.end()) {
                return 0.0; 
            }
            return static_cast<double>(it->second) / total_labels;
        }
    
        int getLabelCount(const string& label) const {
            auto it = label_counts.find(label);
            if (it == label_counts.end()) {
                return 0; 
            }
            return it->second;
        }
    
        const unordered_map<string, int>& getAllLabelCounts() const {
            return label_counts;
        }
    };