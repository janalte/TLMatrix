#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

#define m 200

struct Cell {
    string neigh_fp;
    string label;
    int weight;

    Cell() : neigh_fp("Null"), label("Null"), weight(0) {}
    Cell(const string& v1, const string& v2, int v3)
        : neigh_fp(v1), label(v2), weight(v3) {}
    
    bool operator<(const Cell& other) const {
        return neigh_fp < other.neigh_fp;
    }
    
    bool operator==(const Cell& other) const {
        return (neigh_fp == other.neigh_fp);
    }
};

bool compareCells(const Cell& a, const Cell& b) {
    return a < b;
}


vector<vector<Cell>> matrix(m, vector<Cell>(m, {"Null", "Null", 0}));

void neigh_update(const string&u_fp, const string&u_label, const string& fp, const string& l, int w) {
    for(int i = 0; i < m; i++){
        
        if(matrix[i][0].neigh_fp == u_fp && l==u_label ){
            for(int j = 1; j < m/2; j++){
                
                if(matrix[i][j].neigh_fp == fp ){
                    matrix[i][j].weight += w;
                    return ;
                }
                else if(matrix[i][j].neigh_fp == "Null" ){
              
                    matrix[i][j].neigh_fp = fp;
                    matrix[i][j].label = l;
                    matrix[i][j].weight = w;
                    return ;
                }

            }
        }
        else if(matrix[i][0].neigh_fp == u_fp && l!=u_label ){
            bool is_exist = false;
            for(int j = m/2; j < m; j++){
                if(matrix[i][j].neigh_fp == fp ){
                    matrix[i][j].weight += w;
                    is_exist = true;
                    return ;
                }
                else if(matrix[i][j].neigh_fp == "Null" ){
                   
                    matrix[i][j].neigh_fp = fp;
                    matrix[i][j].label = l;
                    matrix[i][j].weight = w;
                    return ;
                }

            }
        }
       
        else if(matrix[i][0].neigh_fp == "Null" && l==u_label)
        {
            matrix[i][0].neigh_fp = u_fp;//id占位
            matrix[i][0].label = u_label;
            matrix[i][0].weight = w;
            for(int j = 1; j < m/2; j++){
                if(matrix[i][j].neigh_fp == "Null" ){
                    
                    matrix[i][j].neigh_fp = fp;
                    matrix[i][j].label = l;
                    matrix[i][j].weight = w;
                    return ;
                }

            }

        }
       
        else if(matrix[i][0].neigh_fp == "Null" && l!=u_label )
        {
            matrix[i][0].neigh_fp = u_fp;
            matrix[i][0].label = u_label;
            matrix[i][0].weight = w;
            for(int j = m/2; j < m; j++){
                if(matrix[i][j].neigh_fp == "Null" ){
                   
                    matrix[i][j].neigh_fp = fp;
                    matrix[i][j].label = l;
                    matrix[i][j].weight = w;
                    return ;
                }

            }
        }
    }
}
// type:1:一种label 2:两种label 边标签相同 3:两种label 边标签不同 第三个节点与u相同
// 4:两种label 边标签不同 第三个节点与v相同 5:三种label
vector<Cell> neigh_query(string u_fp, string v_fp, int type){
    // 使用set_intersection找到两行的交集
    vector<Cell> intersection_result;
    // 找出u,v的邻居
    vector<Cell> u_neigh;
    vector<Cell> v_neigh;

    if(type == 1){
        for(int i = 0; i < m; i++)
        {
            if(matrix[i][0].neigh_fp == u_fp){
                for(int j = 1; j < m/2; j++){
                    if(matrix[i][j].neigh_fp != "Null"){
                        Cell newCell;
                        newCell.neigh_fp = matrix[i][j].neigh_fp;
                        newCell.label = matrix[i][j].label;
                        newCell.weight = matrix[i][j].weight;
                        u_neigh.push_back(newCell);
                    }
                }
            }
            if(matrix[i][0].neigh_fp == v_fp){
                for(int j = 1; j < m/2; j++){
                    if(matrix[i][j].neigh_fp != "Null"){
                        Cell newCell;
                        newCell.neigh_fp = matrix[i][j].neigh_fp;
                        newCell.label = matrix[i][j].label;
                        newCell.weight = matrix[i][j].weight;
                        v_neigh.push_back(newCell);
                    }
                }
            }
        }
        sort(u_neigh.begin(), u_neigh.end(), compareCells);
        sort(v_neigh.begin(), v_neigh.end(), compareCells);

        // 
        // for (const Cell& element : u_neigh) {
        //     cout << "u_neigh: " << element.neigh_fp << " ";
        // }
        // cout<<"u_size: " <<u_neigh.size()<<endl;
        // cout << endl;

        // for (const Cell& element : v_neigh) {
        //     cout << "v_neigh: " <<  element.neigh_fp << " ";
        // }
        // cout<<"v_size: " <<v_neigh.size()<<endl;
        
       
        set_intersection(u_neigh.begin(), u_neigh.end(),
                          v_neigh.begin(), v_neigh.end(),
                            back_inserter(intersection_result));

        // 
        // for (const Cell& element : intersection_result) {
        //     cout << "intersection_result: " <<  element.neigh_fp << " ";
        // }
    }
    // 两种label 边的两个标签相同
    else if(type == 2){
        for(int i = 0; i < m; i++)
        {
            if(matrix[i][0].neigh_fp == u_fp){
                for(int j = m/2; j < m; j++){
                    if(matrix[i][j].neigh_fp != "Null"){
                        Cell newCell;
                        newCell.neigh_fp = matrix[i][j].neigh_fp;
                        newCell.label = matrix[i][j].label;
                        newCell.weight = matrix[i][j].weight;
                        u_neigh.push_back(newCell);
                    }
                }
            }
            if(matrix[i][0].neigh_fp == v_fp){
                for(int j = m/2; j < m; j++){
                    if(matrix[i][j].neigh_fp != "Null"){
                        Cell newCell;
                        newCell.neigh_fp = matrix[i][j].neigh_fp;
                        newCell.label = matrix[i][j].label;
                        newCell.weight = matrix[i][j].weight;
                        v_neigh.push_back(newCell);
                    }
                }
            }
        }
        sort(u_neigh.begin(), u_neigh.end(), compareCells);
        sort(v_neigh.begin(), v_neigh.end(), compareCells);

        set_intersection(u_neigh.begin(), u_neigh.end(),
                          v_neigh.begin(), v_neigh.end(),
                            back_inserter(intersection_result));


    }
    // 两种label 但是边的两个标签不同 第三个节点与u相同
    else if(type == 3){
        for(int i = 0; i < m; i++)
        {
            if(matrix[i][0].neigh_fp == u_fp){
                for(int j = 1; j < m/2; j++){
                    if(matrix[i][j].neigh_fp != "Null"){
                        Cell newCell;
                        newCell.neigh_fp = matrix[i][j].neigh_fp;
                        newCell.label = matrix[i][j].label;
                        newCell.weight = matrix[i][j].weight;
                        u_neigh.push_back(newCell);
                    }
                }
            }
            if(matrix[i][0].neigh_fp == v_fp){
                for(int j = m/2; j < m; j++){
                    if(matrix[i][j].neigh_fp != "Null"){
                        Cell newCell;
                        newCell.neigh_fp = matrix[i][j].neigh_fp;
                        newCell.label = matrix[i][j].label;
                        newCell.weight = matrix[i][j].weight;
                        v_neigh.push_back(newCell);
                    }
                }
            }
        }
        sort(u_neigh.begin(), u_neigh.end(), compareCells);
        sort(v_neigh.begin(), v_neigh.end(), compareCells);
        
        set_intersection(u_neigh.begin(), u_neigh.end(),
                          v_neigh.begin(), v_neigh.end(),
                            back_inserter(intersection_result));


    }
    // 两种label 但是边的两个标签不同 第三个节点与v相同
    else if(type == 4){
        for(int i = 0; i < m; i++)
        {
            if(matrix[i][0].neigh_fp == u_fp){
                for(int j = m/2; j < m; j++){
                    if(matrix[i][j].neigh_fp != "Null"){
                        Cell newCell;
                        newCell.neigh_fp = matrix[i][j].neigh_fp;
                        newCell.label = matrix[i][j].label;
                        newCell.weight = matrix[i][j].weight;
                        u_neigh.push_back(newCell);
                    }
                }
            }
            if(matrix[i][0].neigh_fp == v_fp){
                for(int j = 1; j < m/2; j++){
                    if(matrix[i][j].neigh_fp != "Null"){
                        Cell newCell;
                        newCell.neigh_fp = matrix[i][j].neigh_fp;
                        newCell.label = matrix[i][j].label;
                        newCell.weight = matrix[i][j].weight;
                        v_neigh.push_back(newCell);
                    }
                }
            }
        }
        sort(u_neigh.begin(), u_neigh.end(), compareCells);
        sort(v_neigh.begin(), v_neigh.end(), compareCells);

        set_intersection(u_neigh.begin(), u_neigh.end(),
                          v_neigh.begin(), v_neigh.end(),
                            back_inserter(intersection_result));


    }
    // 三种label
    else if(type == 5){
        for(int i = 0; i < m; i++)
        {
            if(matrix[i][0].neigh_fp == u_fp){
                for(int j = m/2; j < m; j++){
                    if(matrix[i][j].neigh_fp != "Null"){
                        Cell newCell;
                        newCell.neigh_fp = matrix[i][j].neigh_fp;
                        newCell.label = matrix[i][j].label;
                        newCell.weight = matrix[i][j].weight;
                        u_neigh.push_back(newCell);
                    }
                }
            }
            if(matrix[i][0].neigh_fp == v_fp){
                for(int j = m/2; j < m; j++){
                    if(matrix[i][j].neigh_fp != "Null"){
                        Cell newCell;
                        newCell.neigh_fp = matrix[i][j].neigh_fp;
                        newCell.label = matrix[i][j].label;
                        newCell.weight = matrix[i][j].weight;
                        v_neigh.push_back(newCell);
                    }
                }
            }
        }
        sort(u_neigh.begin(), u_neigh.end(), compareCells);
        sort(v_neigh.begin(), v_neigh.end(), compareCells);

        set_intersection(u_neigh.begin(), u_neigh.end(),
                          v_neigh.begin(), v_neigh.end(),
                            back_inserter(intersection_result));



    }
    return intersection_result;
}


// int main() {
//     // void neigh_update(const string&u_fp, const string&u_label, const string& fp, const string& l, int w) 

//     neigh_update("1", "1", "2", "2", 1);
//     neigh_update("1", "1", "3", "2", 1);
//     neigh_update("3", "3", "2", "2", 1);
//     neigh_update("2", "1", "4", "2", 1);


//     for(int i = 0; i < m; i++)
//     {
//         for(int j = 0; j < m; j++)
//         {
//             cout << matrix[i][j].neigh_fp << " " <<matrix[i][j].label << " " << matrix[i][j].weight << "; " ;
//         }
//         cout << endl;
//     }
//     vector<Cell> result = neigh_query("1", "3", 5);
//     for (const Cell& element : result) {
//         cout << element.neigh_fp << " ";
//     }
//     cout << endl;
//     system("pause");
//     return 0;
// }
