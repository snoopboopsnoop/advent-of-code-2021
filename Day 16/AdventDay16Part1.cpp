#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

//https://en.wikipedia.org/wiki/Brainfuck

string readInput();
string hex_to_bin(char c);
int parse(string& packet);

//debug functions
template <typename T>
void printVector(vector<T> vector);

template <typename T>
void printWrapper(vector<vector<T>> vector);

int main() {
    //hexademical input
    string input = readInput();
    string binInput;

    for(int i = 0; i < input.size(); i++) {
        binInput.append(hex_to_bin(input[i]));
    }

    cout << input << endl;
    cout << binInput << endl;

    cout << parse(binInput) << endl;

    return 0;
}

string readInput() {
    string line;
    ifstream input("input.txt");

    //first line of input file
    if(input.is_open()) {
        getline(input, line);
        return line;
    }
    //if closed return empty string
    return line;
}

string hex_to_bin(char c) {
    switch(c) {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
    }
}

int parse(string& packet) {
    int count = 0;
    int version = stoi(packet.substr(0, 3), nullptr, 2);
    cout << "packet version: " << version << endl;
    packet.erase(0, 3);
    int typeID = stoi(packet.substr(0, 3), nullptr, 2);
    cout << "packet type ID: " << typeID << endl;
    count += version;
    packet.erase(0, 3);
    if(typeID == 4) {
        int bit = int(packet[0]) - 48;
        while(bit != 0) {
            cout << bit << endl;
            packet.erase(0, 5);
            bit = int(packet[0]) - 48;
        }
        packet.erase(0, 5);
        cout << "new packet: " << packet << endl;
        return count;
    }
    else {
        cout << "sub-packet found" << endl;
        if(packet[0] == '0') {
            int length = stoi(packet.substr(1, 15), nullptr, 2);
            cout << "subpacket length (bits): " << length << endl;
            packet.erase(0, 16);
            int currLength = packet.length();
            cout << "current length: " << currLength << endl;
            cout << "objective length: " << currLength - length << endl;
            while(packet.size() != currLength-length) {
                count += parse(packet);
            }
        }
        else if(packet[0] == '1') {
            int numSub_Packets = stoi(packet.substr(1, 11), nullptr, 2);
            packet.erase(0, 12);
            for(int i = 0; i < numSub_Packets; i++) {
                count += parse(packet);
            }
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