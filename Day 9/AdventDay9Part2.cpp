#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

vector<string> readInput();
int basin(int x, int y, vector<vector<int>> map, vector<pair<int, int>>& found);

template <typename T>
void printVector(vector<T> vector);

template <typename T>
void printWrapper(vector<vector<T>> vector);

int main() {
    //write input to vector
    vector<string> input = readInput();
    vector<vector<int>> map;
    vector<int> basins;
    int count = 1;

    for(string i : input) {
        vector<int> temp;
        while(i.size() != 0) {
            temp.push_back(stoi(i.substr(0,1)));
            i.erase(i.begin());
        }
        map.push_back(temp);
    }

    for(int i = 0; i < map.size(); i++) {
        for(int j = 0; j < map[0].size(); j++) {
            vector<pair<int, int>> found;
            int curr = map[i][j];
            //north
            if(i-1 > -1) {
                if(map[i-1][j] <= curr) {
                    continue;
                }
            }
            //south
            if(i+1 < map.size()) {
                if(map[i+1][j] <= curr) {
                    continue;
                }
            }
            //west
            if(j-1 > -1) {
                if(map[i][j-1] <= curr) {
                    continue;
                }
            }
            //east
            if(j+1 < map[0].size()) {
                if(map[i][j+1] <= curr) {
                    continue;
                }
            }
            int temp = basin(i, j, map, found);
            basins.push_back(temp);
            cout << "basin at " << j << ", " << i << ": " << temp << endl;
        }
    }

    sort(basins.begin(), basins.end());
    for(int i = basins.size()-1; i > basins.size()-4; i--) {
        count *= basins[i];
        cout << basins[i] << endl;
    }

    cout << count << endl;

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

int basin(int i, int j, vector<vector<int>> map, vector<pair<int, int>>& found) {
    for(auto coord : found) {
        if(j == coord.first && i == coord.second) {
            return 0;
        }
    }
    found.push_back(pair<int, int>(j, i));
    //cout << "basin at " << j << ", " << i << endl;
    int curr = map[i][j];
    int count = 1;

    if(curr == 9) {
        return 0;
    }
    //north
    if(i-1 > -1) {
        if(map[i-1][j] == curr+1) {
            count += basin(i-1, j, map, found);
        }
    }
    //south
    if(i+1 < map.size()) {
        if(map[i+1][j] == curr+1) {
            count += basin(i+1, j, map, found);
        }
    }
    //west
    if(j-1 > -1) {
        if(map[i][j-1] == curr+1) {
            count += basin(i, j-1, map, found);
        }
    }
    //east
    if(j+1 < map[0].size()) {
        if(map[i][j+1] == curr+1) {
            count += basin(i, j+1, map, found);
        }
    }
    return count;
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
}