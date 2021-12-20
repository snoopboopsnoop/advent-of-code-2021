#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

//https://en.wikipedia.org/wiki/Brainfuck

struct Node;

vector<string> readInput();
int getHeuristic(pair<int, int> position, pair<int, int> goal);
int algorithm(vector<vector<int>> map);
vector<Node>::iterator nodeExists(pair<int, int> position, vector<Node> unvisited);
void getAdjacent(vector<vector<int>> map, vector<Node>& unvisited);
void expandTo(pair<int, int> currPos, Node currNode, vector<Node>& unvisited, int cost);

//debug functions
template <typename T>
void printVector(vector<T> vector);

template <typename T>
void printWrapper(vector<vector<T>> vector);

struct Node {
    static pair<int, int> goal;
    pair<int, int> position;
    //total distance to node
    int distance;
    //cost to travel to this node
    int cost;
    //heuristic + distance
    int combined_heuristic;
    //distance from bottom right
    int heuristic;
    struct Node* previous;
    struct Node* next;

    Node(pair<int, int> position, Node* previous) {
        this->position = position;
        this->previous = previous;
        this->distance = 0;
        //goal must be initialized in main before constructing a node
        this->heuristic = getHeuristic(this->position, goal);
    };
};

pair<int, int> Node::goal = pair<int, int> (0, 0);

int main() {
    //write input to vector
    vector<string> input = readInput();
    //2d array of input
    vector<vector<int>> map;

    //input -> map
    for(string i : input) {
        vector<int> temp;
        while(i.size() != 0) {
            temp.push_back(stoi(i.substr(0,1)));
            i.erase(i.begin());
        }
        map.push_back(temp);
    }

    Node::goal = pair<int, int> (map[0].size()-1, map.size()-1);

    cout << algorithm(map) << endl;

    printWrapper(map);

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

int getHeuristic(pair<int, int> position, pair<int, int> goal) {
    return (goal.first-position.first) + (goal.second-position.second);
}

int algorithm(vector<vector<int>> map) {
    vector<Node> unvisited;
    //starting node has 0 distance and no previous
    Node* current = new Node(pair<int, int>(0, 0), nullptr);
    current->cost = 0;
    //put it on the array to check
    unvisited.push_back(*current);

    getAdjacent(map, unvisited);

    cout << unvisited[1].previous->position.first << ", " << unvisited[1].previous->position.second << endl;
    cout << unvisited[2].previous->position.first << ", " << unvisited[2].previous->position.second << endl;
    for(auto i : unvisited) {
        if(i.previous != nullptr) {
            cout << "node at " << i.position.first << ", " << i.position.second << " points from " << i.previous->position.first << ", " << i.previous->position.first << endl;
        }
        else cout << "node at " << i.position.first << ", " << i.position.second << endl;
    }

    return 0;
}

void getAdjacent(vector<vector<int>> map, vector<Node>& unvisited) {
    Node currNode = unvisited[0];
    cout << currNode.position.first << ", " << currNode.position.second << endl;
    int cost;

    //left
    if(currNode.position.first-1 >= 0) {
        cost = map[currNode.position.first-1][currNode.position.second];
        pair<int, int> currPos (currNode.position.first-1, currNode.position.second);
        expandTo(currPos, currNode, unvisited, cost);
    }
    //right
    if(currNode.position.first+1 < map[0].size()) {
        cost = map[currNode.position.first+1][currNode.position.second];
        pair<int, int> currPos (currNode.position.first+1, currNode.position.second);
        expandTo(currPos, currNode, unvisited, cost);
        cout << unvisited[1].previous->position.first << ", " << unvisited[1].previous->position.second << endl;
    }
    //up
    if(currNode.position.second-1 >= 0) {
        cost = map[currNode.position.first][currNode.position.second-1];
        pair<int, int> currPos (currNode.position.first, currNode.position.second-1);
        expandTo(currPos, currNode, unvisited, cost);
    }
    //down
    if(currNode.position.second+1 < map.size()) {
        cost = map[currNode.position.first][currNode.position.second+1];
        pair<int, int> currPos (currNode.position.first, currNode.position.second+1);
        expandTo(currPos, currNode, unvisited, cost);
        cout << unvisited[2].previous->position.first << ", " << unvisited[2].previous->position.second << endl;
    }
}

void expandTo(pair<int, int> currPos, Node currNode, vector<Node>& unvisited, int cost) {
    auto tempNode = nodeExists(currPos, unvisited);
    //check if node exists
    //also check if the distance in the currNode path is shorter than the tempNode's current distance
    if(tempNode != unvisited.end() && tempNode->distance > currNode.distance + tempNode->cost) {
        tempNode->distance = currNode.distance+tempNode->cost;
    }
    //doesn't exist, make a new one
    Node* newNode = new Node(currPos, &currNode);

    newNode->cost = cost;
    newNode->distance = currNode.distance + cost;
    newNode->combined_heuristic = newNode->distance + newNode->heuristic;

    unvisited.push_back(*newNode);
}

vector<Node>::iterator nodeExists(pair<int, int> position, vector<Node> unvisited) {
    for(auto it = unvisited.begin(); it != unvisited.end();) {
        if(it->position.first == position.first && it->position.second == position.second) {
            return it;
        }
        it++;
    }
    return unvisited.end();
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