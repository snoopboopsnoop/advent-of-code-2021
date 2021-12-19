#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

//https://www.youtube.com/watch?v=Vp5q6xwml1s

vector<string> readInput();
int algorithm(map<string, vector<string>> adjlist, string node, vector<string>& visited, string path);
bool containsLower(string i);

//debug functions
template <typename T>
void printVector(vector<T> vector);

template <typename T>
void printWrapper(vector<vector<T>> vector);

int main() {
    //write input to vector
    vector<string> input = readInput();
    map<string, vector<string>> adjlist;

    //initialize graph
    for(string line : input) {
        string node = line.substr(0, line.find('-'));
        string next = line.substr(line.find('-')+1);
        //cout << node << " -> " << next << endl;
        //forward
        if(adjlist.find(node) == adjlist.end()) {
            vector<string> temp(1, next);
            adjlist.insert(pair<string, vector<string>>(node, temp));
            // cout << node << ": ";
            // printVector(adjlist[node]);
        }
        else {
            adjlist[node].push_back(next);
            // cout << node << ": ";
            // printVector(adjlist[node]);
        }
        //backward
        if(adjlist.find(next) == adjlist.end()) {
            vector<string> temp(1, node);
            adjlist.insert(pair<string, vector<string>>(next, temp));
            // cout << node << ": ";
            // printVector(adjlist[node]);
        }
        else {
            adjlist[next].push_back(node);
            // cout << node << ": ";
            // printVector(adjlist[node]);
        }
    }

    // cout << endl;
    // for(auto i : adjlist) {
    //     cout << i.first << ": ";
    //     printVector(i.second);
    // }

    for(auto& i : adjlist) {
        sort(i.second.begin(), i.second.end());
        //cout << "looking at " << i.first << ": ";
        //printVector(i.second);
        if(i.second.size() == 1) {
            //cout << i.first << " only has " << i.second[0] << endl;
            if(containsLower(i.second[0])) {
                adjlist[i.second[0]].erase(find(adjlist[i.second[0]].begin(), adjlist[i.second[0]].end(), i.first));
                break;
            }
            
        }
    }

    //printVector(input);

    // cout << endl;
    // for(auto i : adjlist) {
    //     cout << i.first << ": ";
    //     printVector(i.second);
    // }
    // cout << endl;

    
    // for(string i : adjlist["start"]) {
    //     vector<string> visited;
    //     cout << "start -> " << i << endl;
    //     if(containsLower(i)) visited.push_back(i);
    //     cout << algorithm(adjlist, i, visited) << endl;
    // }

    vector<string> visited;
    string path = "start";
    cout << algorithm(adjlist, "start", visited, path) << endl;

    return 0;
}

vector<string> readInput() {
    string line;
    vector<string> inputVector;
    ifstream input("input.txt");

    //put each line of input file into vector
    if(input.is_open()) {
        while(getline(input, line)) {
            inputVector.push_back(line);
        }
    }
    return inputVector;
}

int algorithm(map<string, vector<string>> adjlist, string node, vector<string>& visited, string path) {
    int count = 0;
    for(string next : adjlist[node]) {
        vector<string> temp (visited);
        string currPath (path);
        //cout << "visited: ";
        //printVector(temp);
        if(node == "start") {
            visited.clear();
        }
        //cout << "looking at " << node << " -> " << next << endl;
        if(next == "start") {
            //cout << "found a start" << endl;
            continue;
        }
        else if(next == "end") {
            //cout << "end of path" << endl;
            count++;
            currPath.append(" -> end");
            //cout << currPath << endl;
            continue;
        }
        else if(find(temp.begin(), temp.end(), next) != temp.end()) {
            //cout << "already visited" << endl;
            continue;
        }
        else if(containsLower(next)) {
            temp.push_back(next);
            //cout << "adding " << next << " to visited" << endl;
        }
        //cout << "continuing down" << endl;
        currPath.append(" -> ");
        currPath.append(next);
        count += algorithm(adjlist, next, temp, currPath);
    }
    return count;
}

bool containsLower(string i) {
    for(char c : i) {
        if(islower(c)) return true;
    }
    return false;
}

template <typename T>
void printVector(vector<T> vector) {
    for(int i = 0; i < vector.size(); i++) {
        cout << vector[i] << ", ";
    }
    cout << endl;
}

template <typename T>
void printWrapper(vector<vector<T>> vector) {
    for(int i = 0; i < vector.size(); i++) {
        printVector(vector.at(i));
    }
    cout << endl;
}