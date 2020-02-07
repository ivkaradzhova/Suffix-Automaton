#include <iostream>
#include <vector>
#include <string>
#include "State.h"
#include "Cubes.h"
using namespace std;


void initializeAutomaton(vector<State>& states, int& last, int& size) {
    states.emplace_back(State(0, -1));
    last = 0;
    size = 1;
}

void readLetter(char letter, vector<State>& states, int& last, int& size) {
    int newState = size;
    size++;
    states.push_back(State(states[last].length + 1, -1));
    int current = last;
    while(current != -1 && states[current].transition[letter - 'a'] == 0) {
        states[current].transition[letter - 'a'] = newState;
        current = states[current].slink;
    }
    if(current == -1) {
        states[newState].slink = 0;
    } else {
        int q = states[current].transition[letter - 'a'];
        if(states[current].length + 1 == states[q].length) {
            states[newState].slink = q;
        } else {
            int qClone = size;
            size++;
            int cloneLength = states[current].length + 1;
            int cloneSLink = states[q].slink;
            states.emplace_back(State(cloneLength, cloneSLink));
            for(int i = 0; i < ALPHABET_LENGTH; i++) {
                states[qClone].transition[i] = states[q].transition[i];
            }
            while(current != -1 && states[current].transition[letter - 'a'] == q) {
                states[current].transition[letter - 'a'] = qClone;
                current = states[current].slink;
            }
            states[newState].slink = qClone;
            states[q].slink = qClone;
        }
    }
    last = newState;
}

int countTransitions(vector<State>& states) {
    int transitions = 0;
    for(int i = 0; i < states.size(); i++) {
        for(int j = 0; j < ALPHABET_LENGTH; j++) {
            if(states[i].transition[j] != 0) {
                transitions++;
            }
        }
    }
    return transitions;
}

int countFinalStates(vector<State>& states, int last) {
    int finalStates = 0;
    int current = last;
    while(current != 0) {
        finalStates++;
        current = states[current].slink;
    }
    return finalStates;
}

bool hasTransitions(State state) {
    int i = 0;
    while(i <= ALPHABET_LENGTH && state.transition[i] == 0) {
        i++;
    }
    return i != ALPHABET_LENGTH;
}

void print(vector<State> states, int current, vector<bool>& visited) {
    for(int i = 0; i < states.size(); i++) {
        cout << "=======================" << endl;
        cout << "id: " << i << " slink:" << states[i].slink << " length: " << states[i].length << endl;
        for(int j = 0; j < ALPHABET_LENGTH; j++) {
            if(states[i].transition[j] != 0)
                cout << (char)(j + 'a') << " " << states[i].transition[j] << endl;
        }
    }
}

int main() {
    vector<State> states;
    int size, last;

    initializeAutomaton(states, last, size);

    string word;
    //cin >> word;
    for(int i = 0; i < 100000; i++) {
        word += (char)('a' + (rand() % ALPHABET_LENGTH));
    }
    for (int i = 0; i < word.size(); i++) {
        readLetter(word[i], states, last, size);
    }

    vector<bool> visited(size, 0);
   // print(states, 0, visited);
    vector<int> halfs(size, -1);
    getHalfLength(states, halfs);
    /*for(int i = 0; i < halfs.size(); i++) {
        cout << i << " " << halfs[i] << endl;
    }*/


    cout << size << " " << countTransitions(states) << " " << countFinalStates(states, last) << " " << findCubes(states) << endl;
    return 0;
}