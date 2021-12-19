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
map<string, long long> step(map<string, long long> polymers, map<string, string> rules, map<char, long long>& quantity);

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
    map<string, long long> polymers;
    input.erase(input.begin(), input.begin()+2);

    for(string line : input) {
        rules.insert(pair<string, string>(line.substr(0, 2), line.substr(line.find(">")+2)));
    }

    for(char c : polymer) {
        if(quantity.find(c) == quantity.end()) {
            quantity.insert(pair<char, long long>(c, 1));
        }
        else quantity[c]++;
    }

    for(int i = 0; i < polymer.size()-1; i++) {
        string currPair = polymer.substr(i, 2);
        if(polymers.find(currPair) == polymers.end()) {
            polymers.insert(pair<string, long long>(currPair, 1));
        }
        else polymers[currPair]++;
    }

    for(auto i : polymers) {
            cout << i.first << ": " << i.second << endl;
        }
        cout << endl;

    for(int i = 0; i < 40; i++) {
        int count = 0;
        polymers = step(polymers, rules, quantity);
        for(auto it = polymers.begin(); it != polymers.end();) {
            if(it->second == 0) it = polymers.erase(it);
            else it++;
        }
        for(auto i : polymers) {
            count += i.second;
            cout << i.first << ": " << i.second << endl;
        }
        cout << "length: " << count+1 << endl;
        cout << endl;
    }

    for(auto i : quantity) {
        cout << i.first << ": " << i.second << endl;
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

map<string, long long> step(map<string, long long> polymers, map<string, string> rules, map<char, long long>& quantity) {
    map<string, long long> temp;
    for(auto i : polymers) {
        string currPair = i.first;
        string insert = rules[i.first];

        cout << i.second << " " << currPair << " -> " << i.second << " " << currPair[0]+insert << " and " << i.second << " " << insert + currPair[1] << endl;

        if(temp.find(currPair[0]+insert) == temp.end()) {
            temp.insert(pair<string, long long>(currPair[0]+insert, i.second));
        }
        else temp[currPair[0]+insert] += i.second;

        if(temp.find(insert + currPair[1]) == temp.end()) {
            temp.insert(pair<string, long long>(insert + currPair[1], i.second));
        }
        else temp[insert + currPair[1]] += i.second;

        if(quantity.find(insert[0]) == quantity.end()) {
            quantity.insert(pair<char, long long>(insert[0], i.second));
        }
        else quantity[insert[0]] += i.second;
    }
    return temp;
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