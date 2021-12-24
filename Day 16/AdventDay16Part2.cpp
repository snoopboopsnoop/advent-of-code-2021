#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <bitset>
#include <cstdint>

using namespace std;

//https://en.wikipedia.org/wiki/Brainfuck

string readInput();
string hex_to_bin(char c);
string parse(string& packet);

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

    cout << stoll(parse(binInput), nullptr, 2) << endl;

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

string parse(string& packet) {
    uint64_t count = 0;
    string value;
    int version = stoll(packet.substr(0, 3), nullptr, 2);
    //cout << "packet version: " << version << endl;
    packet.erase(0, 3);
    int typeID = stoll(packet.substr(0, 3), nullptr, 2);
    cout << "packet type ID: " << typeID << endl;
    packet.erase(0, 3);
    if(typeID == 4) {
        cout << "4" << endl;
        int bit = int(packet[0]) - 48;
        while(bit != 0) {
            value.append(packet.substr(1, 4));
            packet.erase(0, 5);
            bit = int(packet[0]) - 48;
        }
        value.append(packet.substr(1, 4));
        packet.erase(0, 5);
        cout << "packet literal value: " << value << endl;
        cout << "new packet: " << packet << endl;
        return value;
    }
    else {
        cout << "sub-packet found" << endl;
        cout << "length typeID: " << int(packet[0])-48 << endl;
        if(packet[0] == '0') {
            int length = stoll(packet.substr(1, 15), nullptr, 2);
            cout << "subpacket length (bits): " << length << endl;
            packet.erase(0, 16);
            int currLength = packet.length();
            cout << "current length: " << currLength << endl;
            cout << "objective length: " << currLength - length << endl;
            switch(typeID) {
                case 0:
                {
                    cout << "0" << endl;
                    while(packet.size() != currLength-length) {
                        count += stoll(parse(packet), nullptr, 2);
                    }
                    break;
                }
                case 1:
                {  
                    cout << "1" << endl;
                    uint64_t temp = 1;
                    while(packet.size() != currLength-length) {
                        temp *= stoll(parse(packet), nullptr, 2);
                    }
                    count += temp;
                    break;
                }
                case 2:
                {
                    cout << "2" << endl;
                    vector<uint64_t> values;
                    while(packet.size() != currLength-length) {
                        values.push_back(stoll(parse(packet), nullptr, 2));
                    }
                    count += *min_element(values.begin(), values.end());
                    break;
                }
                case 3:
                {
                    cout << "3" << endl;
                    vector<uint64_t> values;
                    while(packet.size() != currLength-length) {
                        values.push_back(stoll(parse(packet), nullptr, 2));
                    }
                    count += *max_element(values.begin(), values.end());
                    break;
                }
                case 5:
                {
                    cout << "5" << endl;
                    uint64_t first = stoll(parse(packet), nullptr, 2);
                    uint64_t second = stoll(parse(packet), nullptr, 2);
                    if(first > second) count += 1;
                    break;
                }
                case 6:
                {
                    cout << "6" << endl;
                    uint64_t first = stoll(parse(packet), nullptr, 2);
                    uint64_t second = stoll(parse(packet), nullptr, 2);
                    cout << "is " << first << " < " << second << endl;
                    if(first < second) count += 1;
                    break;
                }
                case 7:
                {
                    cout << "7" << endl;
                    uint64_t first = stoll(parse(packet), nullptr, 2);
                    uint64_t second = stoll(parse(packet), nullptr, 2);
                    cout << "is " << first << " = " << second << endl;
                    if(first == second) count += 1;
                    break;
                }
            }
        }
        else if(packet[0] == '1') {
            int numSub_Packets = stoll(packet.substr(1, 11), nullptr, 2);
            cout << "sub packets: " << numSub_Packets << endl;
            
            packet.erase(0, 12);
            switch(typeID) {
                case 0:
                {
                    cout << "0" << endl;
                    for(int i = 0; i < numSub_Packets; i++) {
                        count += stoll(parse(packet), nullptr, 2);
                    }
                    break;
                }
                case 1:
                {  
                    cout << "1" << endl;
                    uint64_t temp = 1;
                    for(int i = 0; i < numSub_Packets; i++) {
                        temp *= stoll(parse(packet), nullptr, 2);
                    }
                    count += temp;
                    break;
                }
                case 2:
                {
                    cout << "2" << endl;
                    vector<uint64_t> values;
                    for(int i = 0; i < numSub_Packets; i++) {
                        values.push_back(stoll(parse(packet), nullptr, 2));
                    }
                    count += *min_element(values.begin(), values.end());
                    break;
                }
                case 3:
                {
                    cout << "3" << endl;
                    vector<uint64_t> values;
                    for(int i = 0; i < numSub_Packets; i++) {
                        values.push_back(stoll(parse(packet), nullptr, 2));
                    }
                    count += *max_element(values.begin(), values.end());
                    break;
                }
                case 5:
                {
                    cout << "5" << endl;
                    uint64_t first = stoll(parse(packet), nullptr, 2);
                    uint64_t second = stoll(parse(packet), nullptr, 2);
                    if(first > second) count += 1;
                    break;
                }
                case 6:
                {
                    cout << "6" << endl;
                    uint64_t first = stoll(parse(packet), nullptr, 2);
                    uint64_t second = stoll(parse(packet), nullptr, 2);
                    cout << "is " << first << " < " << second << endl;
                    if(first < second) count += 1;
                    break;
                }
                case 7:
                {
                    cout << "7" << endl;
                    uint64_t first = stoll(parse(packet), nullptr, 2);
                    uint64_t second = stoll(parse(packet), nullptr, 2);
                    cout << "is " << first << " = " << second << endl;
                    if(first == second) count += 1;
                    break;
                }
            }
        }
    }
    cout << count << endl;
    string binaryCount = bitset<64>(count).to_string();
    return binaryCount;
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