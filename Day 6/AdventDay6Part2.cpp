#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

vector<string> readInput();
void nextDay(map<int, long long> &population);
long long getSum(map<int, long long> population);

void printMap(map<int, long long> map);

template <typename T>
void printVector(vector<T> vector);

template <typename T>
void printWrapper(vector<vector<T>> vector);

//shit's the same as day 1 i just wrote it too good first try
int main() {
    //write input to vector
    vector<string> input = readInput();
    //map of days 0-8 that point to number of fish
    map<int, long long> population;
    //initialize
    population.insert(pair<int, long long>(0, 0));
    population.insert(pair<int, long long>(1, 0));
    population.insert(pair<int, long long>(2, 0));
    population.insert(pair<int, long long>(3, 0));
    population.insert(pair<int, long long>(4, 0));
    population.insert(pair<int, long long>(5, 0));
    population.insert(pair<int, long long>(6, 0));
    population.insert(pair<int, long long>(7, 0));
    population.insert(pair<int, long long>(8, 0));

    //parse input and put them into the population map
    while(input[0].find(",") != string::npos) {
        population.at(stoi(input[0].substr(0,1)))++;
        input[0].erase(0,2);
    }
    population.at(stoi(input[0].substr(0,1)))++;
    
    //256 days
    for(int i = 0; i < 256; i++) {
        nextDay(population);
    }

    //answer
    cout << getSum(population) << endl;

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

void printMap(map<int, long long> map) {
    //print every element
    for(auto elem : map) {
        cout << elem.first << ": "  << elem.second << endl;
    }
    cout << endl;   
}

void nextDay(map<int, long long> &population) {
    //birthed fish
    long long births = population.at(0);
    population.at(0) = 0;
    //move all the values down 1 day
    for(int i = 1; i < 9; i++) {
        population.at(i-1) = population.at(i);
    }
    //mama fish go day 6
    population.at(6) += births;
    //babies go day 8
    population.at(8) = births;
}

long long getSum(map<int, long long> population) {
    long long count = 0;
    //every element's fish count
    for(auto elem : population) {
        count += elem.second;
    }
    return count;
}

template <typename T>
void printVector(vector<T> vector) {
    for(int i = 0; i < vector.size(); i++) {
        cout << vector[i] << " ";
    }
    cout << endl;
}

template <typename T>
void printWrapper(vector<vector<T>> vector) {
    for(int i = 0; i < vector.size(); i++) {
        printVector(vector.at(i));
    }
}