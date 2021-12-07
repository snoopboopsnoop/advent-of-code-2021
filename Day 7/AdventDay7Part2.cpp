#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

vector<string> readInput();
long long getFuelCount(vector<int> crabs, int num);

template <typename T>
void printVector(vector<T> vector);

template <typename T>
void printWrapper(vector<vector<T>> vector);

int main() {
    //write input to vector
    vector<string> input = readInput();
    vector<int> crabs;
    long long lowestPos = -1;
    long long lowestVal = -1;

    while(input[0].find(",") != string::npos) {
        int comma = input[0].find(",");
        crabs.push_back(stoi(input[0].substr(0, comma)));
        input[0].erase(0, comma+1);
    }
    crabs.push_back(stoi(input[0]));

    sort(crabs.begin(), crabs.end());

    for(int i = 0; i <= crabs.back(); i++) {
        long long currVal = getFuelCount(crabs, i);

        if(lowestVal < 0) {
            lowestVal = currVal;
            lowestPos = i;
        }
        else if(currVal < lowestVal) {
            lowestVal = currVal;
            lowestPos = i;
        }
    }

    cout << lowestPos << endl;
    cout << lowestVal << endl;
    
    cout << getFuelCount(crabs, 2) << endl;

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

long long getFuelCount(vector<int> crabs, int num) {
    long long fuel = 0;
    for(int i = 0; i < crabs.size(); i++) {
        fuel += (pow(double(crabs[i] - num), 2.0) + abs(crabs[i] - num))/2;
        //cout << "from " << crabs[i] << " to " << num << ": " << (pow(double(crabs[i] - num), 2.0) + abs(crabs[i] - num))/2 << endl;
    }
    return fuel;
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