#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

vector<string> readInput();
int getFuelCount(vector<int> crabs, int num);

template <typename T>
void printVector(vector<T> vector);

template <typename T>
void printWrapper(vector<vector<T>> vector);

int main() {
    //write input to vector
    vector<string> input = readInput();
    vector<string> unique;

    int count = 0;

    for(string i : input) {
        string curr;
        string output = i.substr(i.find("|")+2);

        while(output.size() != 0) {
            if(output.find(" ") == string::npos) {
                curr = output.substr(0);
                output.erase(output.begin(), output.end());
            }
            else {
                curr = output.substr(0, output.find(" "));
                output.erase(0, output.find(" ")+1);
            }

            if(curr.size() == 2 || curr.size() == 3 || curr.size() == 4 || curr.size() == 7) {
                count++;
            }
        }
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