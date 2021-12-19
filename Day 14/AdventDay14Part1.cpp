#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

//https://en.wikipedia.org/wiki/Brainfuck

vector<string> readInput();
string step(string polymer, map<string, string> rules);

//debug functions
template <typename T>
void printVector(vector<T> vector);

template <typename T>
void printWrapper(vector<vector<T>> vector);

int main() {
    //write input to vector
    vector<string> input = readInput();
    map<string, string> rules;
    map<char, long long> quantity;
    string polymer = input[0];
    input.erase(input.begin(), input.begin()+2);

    for(string line : input) {
        rules.insert(pair<string, string>(line.substr(0, 2), line.substr(line.find(">")+2)));
    }

    // for(auto i : rules) {
    //     cout << i.first << " -> " << i.second << endl;
    // }

    for(int i = 0; i < 10; i++) {
        polymer = step(polymer, rules);
    }

    for(char i : polymer) {
        if(quantity.find(i) == quantity.end()) {
            quantity.insert(pair<char, long long>(i, 1));
        }
        else quantity[i]++;
    }

    //have to do this shit because lambda for sort won't work for some dogshit reason fuck c++
    char mostCommon;
    char leastCommon;

    long long biggest = -1;
    long long smallest = -1;

    for(auto i : quantity) {
        if(biggest == -1 && smallest == -1) {
            biggest, smallest = i.second;
            mostCommon, leastCommon = i.first;
        }
        if(i.second > biggest) {
            biggest = i.second;
            mostCommon = i.first;
        }
        else if (i.second < smallest) {
            smallest = i.second;
            leastCommon = i.first;
        }
    }
    
    cout << biggest - smallest << endl;


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

string step(string polymer, map<string, string> rules) {
    for(int i = 0; i < polymer.size()-1; i++) {
        string currPair = polymer.substr(i, 2);
        string insert = rules[currPair];
        //cout << "inserting " << insert << " between " << currPair << endl;
        polymer.insert(i+1, insert);
        i++;
    }
    return polymer;
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