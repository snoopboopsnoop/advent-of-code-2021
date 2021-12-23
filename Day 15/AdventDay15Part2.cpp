#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <utility>

using namespace std;

//https://en.wikipedia.org/wiki/Brainfuck

struct Node;

vector<string> readInput();

//algorithm functions
int aStar(vector<vector<int>> map);
bool isValid(pair<int, int> coords, pair<int, int> goal);
int getHeuristic(pair<int, int> position, pair<int, int> goal);
void expand(Node currNode, pair<int, int> position, vector<Node> visited, vector<Node>& unvisited, vector<vector<int>> map);
int exists(pair<int, int> position, vector<Node> nodes);
void getPath(Node endNode, vector<Node> visited);

//debug functions
template <typename T>
void printVector(vector<T> vector);

template <typename T>
void printWrapper(vector<vector<T>> vector);

struct Node {
    static pair<int, int> goal;
    pair<int, int> position;
    pair<int, int> parentCoords;
    int cost;
    int distance;
    int heuristic;
    int combined_heuristic;
};

//intialize goal
pair<int, int> Node::goal = pair<int, int> (0, 0);

int main() {
    //write input to vector
    vector<string> input = readInput();
    //2d array of input
    vector<vector<int>> map;

    //input -> map
    for(string i : input) {
        vector<int> line;
        vector<int> temp;
            while(i.size() != 0) {
                temp.push_back(stoi(i.substr(0,1)));
                i.erase(i.begin());
            }
            line.insert(line.begin(), temp.begin(), temp.end());
            for(int j = 0; j < 4; j++) {
                vector<int> increment(temp.size());
                transform(temp.begin(), temp.end(), increment.begin(), [](int x) -> int {
                    if(x == 9) {
                        return 1;
                    }
                    else return ++x;
                });
                temp.clear();
                temp.insert(temp.begin(), increment.begin(), increment.end());
                line.insert(line.end(), temp.begin(), temp.end());
            }
        map.push_back(line);
    }
    vector<vector<int>> tempMap (map);
    for(int i = 0; i < 4; i++) {
        for(vector<int>& line : tempMap) {
            vector<int> temp(line.size());
            transform(line.begin(), line.end(), temp.begin(), [](int x) -> int {
                if(x == 9) {
                    return 1;
                }
                else return ++x;
            });
            transform(line.begin(), line.end(), line.begin(), [](int x) -> int {
                if(x == 9) {
                    return 1;
                }
                else return ++x;
            });
            map.push_back(temp);
        }
    }
    //set goal
    Node::goal = pair<int, int> (map[0].size()-1, map.size()-1);

    cout << aStar(map) << endl;

    //printWrapper(map);

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

int aStar(vector<vector<int>> map) {
    vector<Node> unvisited;
    vector<Node> visited;
    
    Node first = Node();
    first.cost = 0;
    //first node has no distance
    first.distance = 0;
    //start in top left
    first.position = pair<int, int> (0, 0);
    first.heuristic = getHeuristic(pair<int, int> (0, 0), first.goal);
    first.combined_heuristic = first.heuristic + first.distance;
    unvisited.push_back(first);

   while (true) {
        //pull expand off top node
        Node currNode = unvisited[0];
        //cout << "Expanding from " << currNode.position.first << ", " << currNode.position.second << endl;

        //check if at goal
        if(currNode.position == currNode.goal) {
            //cout << "end node at " << currNode.position.first << ", " << currNode.position.second << " points from " << currNode.parentCoords.first << ", " << currNode.parentCoords.second << " with combined heuristic " << currNode.combined_heuristic << endl;
            //getPath(currNode, visited);
            return currNode.distance;
        }

        //left
        expand(currNode, pair<int, int> (currNode.position.first-1, currNode.position.second), visited, unvisited, map);
        //right
        expand(currNode, pair<int, int> (currNode.position.first+1, currNode.position.second), visited, unvisited, map);
        //up
        expand(currNode, pair<int, int> (currNode.position.first, currNode.position.second-1), visited, unvisited, map);
        //down
        expand(currNode, pair<int, int> (currNode.position.first, currNode.position.second+1), visited, unvisited, map);

        //move expanded node to visited
        visited.push_back(currNode);
        unvisited.erase(unvisited.begin());
        
        //sort by combined heuristic
        sort(unvisited.begin(), unvisited.end(), [](const Node& a, const Node& b) -> bool {
            return a.combined_heuristic < b.combined_heuristic;
        });
    }

    return 0;
}

void expand(Node currNode, pair<int, int> position, vector<Node> visited, vector<Node>& unvisited, vector<vector<int>> map) {
    //cout << "expanding to " << position.first << ", " << position.second << endl;
    if(isValid(position, currNode.goal)) {
        //already visited
        if(exists(position, visited) != -1 ) {
            return;
        }
        //exists in unvisited
        else if(exists(position, unvisited) != -1) {
            int matchPos = exists(position, unvisited);
            //cout << matchPos << endl;
            Node tempNode = unvisited[matchPos];
            //check if distance through current path is more efficient
            if(tempNode.distance > currNode.distance + tempNode.cost) {
                //cout << "current distance of " << tempNode.distance << " is less efficient than " << currNode.distance + tempNode.cost << endl;
                unvisited[matchPos].distance = currNode.distance + tempNode.cost;
                unvisited[matchPos].combined_heuristic = unvisited[matchPos].heuristic + unvisited[matchPos].distance;
                unvisited[matchPos].parentCoords = currNode.position;
                //cout << tempNode.position.first << ", " << tempNode.position.second << " now points from " << unvisited[matchPos].parentCoords.first << ", " << unvisited[matchPos].parentCoords.second << endl;
            }
        }
        //doesn't exist
        else {
            Node tempNode = Node();
            tempNode.cost = map[position.second][position.first];
            tempNode.position = position;
            //new distance = previous Node distance + cost
            tempNode.distance = currNode.distance + tempNode.cost;
            //cout << "distance: " << tempNode.distance << endl;
            tempNode.heuristic = getHeuristic(position, currNode.goal);
            tempNode.combined_heuristic = tempNode.heuristic + tempNode.distance;
            tempNode.parentCoords = currNode.position;
            unvisited.push_back(tempNode);
            //cout << "new node at " << tempNode.position.first << ", " << tempNode.position.second << endl;
        }
    }
    return;
}

bool isValid(pair<int, int> coords, pair<int, int> goal) {
    if(!(coords.first >= 0 && coords.first <= goal.first)) {
        return false;
    }
    else if(!(coords.second >= 0 && coords.second <= goal.second)) {
        return false;
    }
    return true;
}

int exists(pair<int, int> position, vector<Node> nodes) {
    //cout << "looking for " << position.first << ", " << position.second << endl;
    for(int i = 0; i < nodes.size(); i++) {
        if(nodes[i].position.first == position.first && nodes[i].position.second == position.second) {
            //cout << "found " << nodes[i].position.first << ", " << nodes[i].position.second << endl;
            //cout << "at " << i << endl;
            return i;
        }
    }
    return -1;
}

int getHeuristic(pair<int, int> position, pair<int, int> goal) {
    return (goal.first - position.first) + (goal.second - position.second);
}

void getPath(Node endNode, vector<Node> visited) {
    Node currNode = endNode;
    //cout << currNode.position.first << ", " << currNode.position.second;
    while(currNode.position != pair<int, int>(0, 0)) {
        cout << " <- " << currNode.position.first << ", " << currNode.position.second;
        currNode = visited[exists(currNode.parentCoords, visited)];
    }
    cout << " <- " << currNode.position.first << ", " << currNode.position.second << endl; 
}

template <typename T>
void printVector(vector<T> vector) {
    for(int i = 0; i < vector.size(); i++) {
        cout << vector[i];
    }
    cout << endl;
}

template <typename T>
void printWrapper(vector<vector<T>> vector) {
    for(int i = 0; i < vector.size(); i++) {
        printVector(vector.at(i));
    }
}