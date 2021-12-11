#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <cmath>
#include <map>

using namespace std;

vector<string> readInput();

int main() {
    //write input to vector
    vector<string> input = readInput();
    //stores all important coords
    map<pair<int, int>, int> map;
    int count = 0;

    for(string line : input) {
        //temp coordinates
        int coordX = 0;
        int coordY = 0;

        //distance across x and y
        int distX = 0;
        int distY = 0;
        //signs
        int distXSign = 1;
        int distYSign = 1;

        pair<int, int> startCoord;
        pair<int, int> endCoord;
        //first coord
        coordX = stoi(line.substr(0, line.find(",")));
        line.erase(line.begin(), line.begin()+line.find(",")+1);
        coordY = stoi(line.substr(0, line.find(" ")));
        line.erase(line.begin(), line.begin()+line.find("-> ")+3);
        startCoord = make_pair(coordX, coordY);
        //second coord
        coordX = stoi(line.substr(0, line.find(",")));
        line.erase(line.begin(), line.begin()+line.find(",")+1);
        coordY = stoi(line.substr(0));
        endCoord = make_pair(coordX, coordY);

        //distances
        distX = endCoord.first - startCoord.first;
        distY = endCoord.second - startCoord.second;

        //get sign of distances
        if(signbit(distX)) {
            distXSign = -1;
        }
        else distXSign = 1;

        if(signbit(distY)) {
            distYSign = -1;
        }
        else distYSign = 1;

        //horizontal
        if(distY == 0 && distX != 0) {
            //iterate across from startCoord to endCoord
            for(int i = 0; i <= abs(distX); i++) {
                //current coord
                pair<int, int> tempPair;
                tempPair = make_pair(startCoord.first+i*distXSign, startCoord.second);
                //check if coord exists
                if(map.find(tempPair) == map.end()) {
                    //add to map
                    map.insert(pair<pair<int, int>, int>(tempPair, 1));
                }
                //overlap
                else map.at(tempPair)++;
            }
        }
        //vertical
        else if (distX == 0 && distY != 0) {
            //iterate down/up from startCoord to endCoord
            for(int i = 0; i <= abs(distY); i++) {
                //current coord
                pair<int, int> tempPair;
                tempPair = make_pair(startCoord.first, startCoord.second+i*distYSign);
                //check if coord exists
                if(map.find(tempPair) == map.end()) {
                    //add to map
                    map.insert(pair<pair<int, int>, int>(tempPair, 1));
                }
                //overlap
                else map.at(tempPair)++;
            }
        }
    }
    //count overlaps
    for(auto elem : map) {
        if(elem.second > 1) {
            count++;
        }
    }
    //answer
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