#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

vector<string> readInput();
int getFuelCount(vector<int> crabs, int num);

//debug functions
template <typename T>
void printVector(vector<T> vector);

template <typename T>
void printWrapper(vector<vector<T>> vector);

int main() {
    //write input to vector
    vector<string> input = readInput();
    //crab positions
    vector<int> crabs;
    //most efficient fuel count
    int lowestVal;
    //position of most efficient fuel count
    int median;

    //put crab values into crabs
    while(input[0].find(",") != string::npos) {
        int comma = input[0].find(",");
        crabs.push_back(stoi(input[0].substr(0, comma)));
        input[0].erase(0, comma+1);
    }
    crabs.push_back(stoi(input[0]));
    sort(crabs.begin(), crabs.end());

    //median of crabs
    median = crabs[crabs.size()/2];

    //if even number choose the lowest fuel count of the two "medians"
    if(crabs.size()%2 == 0) {
        int otherMed = crabs[(crabs.size()/2)-1];
        if(getFuelCount(crabs, median) < getFuelCount(crabs, otherMed)) {
            lowestVal = getFuelCount(crabs, median);
        }
        else {
            lowestVal = getFuelCount(crabs, otherMed);
        }
    }
    else lowestVal = getFuelCount(crabs, median);

    //answer
    cout << lowestVal << endl;
    
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

int getFuelCount(vector<int> crabs, int num) {
    int fuel = 0;
    for(int i = 0; i < crabs.size(); i++) {
        //add distance away
        fuel += abs(crabs[i] - num);
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