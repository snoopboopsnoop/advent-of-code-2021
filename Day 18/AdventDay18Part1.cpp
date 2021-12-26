#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

//https://en.wikipedia.org/wiki/Brainfuck

vector<string> readInput();
void addition(string& snailfish);
int checkExplode(string& snailfish);
int checkSplit(string& snailfish);
void split(string& snailfish, int pos);
void explode(string& snailfish, int pos);
int nearestLeft(string snailfish, int pos);
int nearestRight(string snailfish, int pos);
int leftMostPair(string snailfish, int pos);
int getMagnitude(string snailfish);

//debug functions
template <typename T>
void printVector(vector<T> vector);

template <typename T>
void printWrapper(vector<vector<T>> vector);

//i decided to do string operations for this because i'm a dumbass and can't think of a more efficient way
//using actual pairs would be more of a pain in the ass
int main() {
    //write input to vector
    vector<string> input = readInput();
    string snailfish;

    //printVector(input);

    //initialize first addition
    for(int i = 0; i < 2; i++) {
        if(snailfish.size() == 0) {
            snailfish.append(input[i]);
            snailfish.append(",");
        }
        else {
            snailfish.insert(0, "[");
            snailfish.append(input[i]);
            snailfish.append("],");
        }
    }
    //cout << snailfish << endl;

    addition(snailfish);

    //cout << snailfish << endl;
    //cout << endl;

    for(int i = 2; i < input.size(); i++) {
        snailfish.insert(0, "[");
        snailfish.append(input[i]);
        snailfish.append("],");
        //cout << snailfish << endl;
        addition(snailfish);
        //cout << snailfish << endl;
        //cout << endl;
    }
    if(snailfish.back() == ',') {
        snailfish.erase(snailfish.end()-1);
    }

    cout << snailfish << endl;

    cout << getMagnitude(snailfish) << endl;

    return 0;
}

void addition(string& snailfish) {
    while(true) {
        //int exploded = checkExplode(snailfish);
        if(checkExplode(snailfish) == 0) {
            //int didSplit = checkSplit(snailfish);
            if(checkSplit(snailfish) == 0) {
                break;
            }
        }
    }
}

int checkExplode(string& snailfish) {
    int nestCount = 0;
    for(int i = 0; i < snailfish.size(); i++) {
        if(i == snailfish.size()-1) {
            cout << "ended" << endl;
            return 0;
        }
        //cout << "char: " << snailfish[i] << endl;

        if(snailfish[i] == '[') nestCount++;
        else if(snailfish[i] == ']') nestCount--;

        //cout << "nested " << nestCount << endl;

        if(nestCount == 5) {
            //cout << leftMostPair(snailfish, i) << endl;
            i = leftMostPair(snailfish, i);
            cout << "exploding ";
            cout << snailfish[i] << endl;
            explode(snailfish, i);
            cout << "snailfish: " << snailfish << endl;
            //cout << "break" << endl;
            return 1;
        }
    }
}

int checkSplit(string& snailfish) {
    for(int i = 0; i < snailfish.size(); i++) {
        if(i == snailfish.size()-1) {
            cout << "ended" << endl;
            return 0;
        }
        //cout << "char: " << snailfish[i] << endl;
        string currInt;

        while(isdigit(snailfish[i])) {
            //cout << snailfish[i] << endl;
            currInt.append(1, snailfish[i]);
            i++;
        }
        if(currInt.size() != 0) {
            //cout << "found int: " << stoi(currInt) << endl;
            if(currInt.size() > 1) {
                cout << "splitting" << endl;
                split(snailfish, i-currInt.size());
                cout << "snailfish: " << snailfish << endl;
                return 1;
            }
            i--;
        }
    }
}

void split(string& snailfish, int pos) {
    int splitInt = stoi(snailfish.substr(pos, snailfish.find_first_of("[],", pos)-pos));
    //cout << splitInt << endl;
    string splitString = "[";

    splitString.append(to_string(int(floor(double(splitInt)/2.0))));
    splitString.append(",");
    splitString.append(to_string(int(ceil(double((splitInt/2.0))))));
    splitString.append("]");

    //cout << splitString << endl;

    //cout << pos << endl;
    //cout << snailfish.find_first_of("[],", pos) << endl;

    snailfish.erase(pos, snailfish.find_first_of("[],", pos)-pos);
    snailfish.insert(pos, splitString);
}

//don't even ask about how the substr and erase values work they just do
void explode(string& snailfish, int pos) {
    int first = stoi(snailfish.substr(pos+1, snailfish.find(",", pos)-pos-1));
    int second = stoi(snailfish.substr(snailfish.find(",", pos)+1, snailfish.find("]", pos)-snailfish.find(",", pos)-1));
    //cout << "pair: " << first << ", " << second << endl;

    int leftPos = nearestLeft(snailfish, pos);

    if(leftPos != -1) {
        int change = 0;
        //cout << snailfish.substr(leftPos, snailfish.find_first_of("[],", leftPos)-leftPos) << endl;
        int left = stoi(snailfish.substr(leftPos, snailfish.find_first_of("[],", leftPos)-leftPos));
        //cout << left << endl;
        change -= snailfish.size();
        left += first;
        snailfish.erase(leftPos, snailfish.find_first_of("[],", leftPos)-leftPos);
        snailfish.insert(leftPos, to_string(left));
        change += snailfish.size();
        pos += change;
        //cout << left << endl;
        //cout << snailfish << endl;
    }

    //cout << "after left pos: " << snailfish[pos] << endl;

    int rightPos = nearestRight(snailfish, snailfish.find("]", pos));

    if(rightPos != -1) {
        // cout << endl;
        // cout << rightPos << endl;
        // cout << snailfish[rightPos] << endl;
        // cout << snailfish.find_first_of("[],", rightPos) << endl;
        // cout << snailfish.substr(rightPos, snailfish.find_first_of("[],", rightPos)-rightPos) << endl;
        int right = stoi(snailfish.substr(rightPos, snailfish.find_first_of("[],", rightPos)-rightPos));
        //cout << "right " << right << endl;
        right += second;
        // cout << endl;
        // cout << rightPos << endl;
        // cout << snailfish.find_first_of("[],", rightPos) << endl;
        // cout << snailfish.substr(rightPos, snailfish.find_first_of("[],", rightPos)-rightPos) << endl;
        snailfish.erase(rightPos, snailfish.find_first_of("[],", rightPos)-rightPos);
        snailfish.insert(rightPos, to_string(right));

        //cout << right << endl;
        //cout << snailfish << endl;
    }
    
    //cout << "after right pos: " << snailfish[pos] << endl;
    snailfish.erase(pos, snailfish.find("]", pos)-pos+1);
    snailfish.insert(pos, "0");

    //cout << snailfish << endl;

    //cout << "exploding " << first << ", " << second << endl;
}

int nearestLeft(string snailfish, int pos) {
    for(int i = pos-1; i >= 0; i--) {
        if(isdigit(snailfish[i])) {
            while(isdigit(snailfish[i])) {
                i--;
            }
            return i+1;
        }
    }
    return -1;
}

int nearestRight(string snailfish, int pos) {
    for(int i = pos+1; i < snailfish.size(); i++) {
        if(isdigit(snailfish[i])) {
            return i;
        }
    }
    return -1;
}

int leftMostPair(string snailfish, int pos) {
    for(int i = pos; i < snailfish.size(); i++) {
        //cout << "position: " << i << endl;
        if(snailfish[i] == '[') {
            //cout << "nearest [: " << snailfish.find("[", i+1) << endl;
            //cout << "nearest ]: " << snailfish.find("]", i) << endl;
            if(snailfish.find("[", i+1) < snailfish.find("]", i)) {
                i = snailfish.find("[", i);
            }
            else return i;
        }
    }
    return -1;
}

int getMagnitude(string snailfish) {
    int magnitude = 0;
    while(true) {
        int pairPos = leftMostPair(snailfish, 0);
        //cout << "pair begins at " << pairPos << endl;
        if(pairPos == -1) {
            return magnitude;
        }
        string currPair = snailfish.substr(pairPos, snailfish.find("]", pairPos)-pairPos+1);
        magnitude = 3 * stoi(currPair.substr(1, currPair.find(",")-1)) + 2 * stoi(currPair.substr(currPair.find(",")+1, currPair.size()-2));
        snailfish.erase(pairPos, snailfish.find("]", pairPos)-pairPos+1);
        snailfish.insert(pairPos, to_string(magnitude));
        //cout << "magnitude: " << magnitude << endl;
        //cout << "current pair: " << currPair << endl;
        //cout << "snailfish: " << snailfish << endl;
    }
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