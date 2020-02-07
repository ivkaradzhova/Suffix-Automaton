//
// Created by pon on 04.02.20.
//
#include "State.h"
#include <iostream>
#include <map>
#include <stack>
#include <vector>
using namespace std;

void buildTree(vector<State>& states, vector<vector<int>>& tree) {
    for(int i = 1; i < states.size(); i++) {
        tree[states[i].slink].push_back(i);
    }
}

void getHalfLength(vector<State> &states, vector<int> &halfLengths) {
    vector<vector<int>> tree(states.size());
    buildTree(states, tree);
    vector<int> lengths(states.size(), -1);
    stack<pair<int,bool>> st;

    st.push(make_pair(0, 0));
    while(!st.empty()) {
        pair<int, bool> top = st.top();
        st.pop();
        if(top.second == 0) { //that means that we are still traversing down

            int topLength = states[top.first].length;
            lengths[topLength] = top.first;

            if(topLength % 2 == 0 && lengths[topLength / 2] != -1) {
                halfLengths[top.first] = lengths[topLength / 2];
            } else {
                if (top.first != -1)
                    halfLengths[top.first] = -1;
            }
            st.push(make_pair(top.first, 1));
            for (int i = 0; i < tree[top.first].size(); i++) {
                st.push(make_pair(tree[top.first][i], 0));
            }

        } else { //traversing up => we have to clean up length for the next path
            lengths[states[top.first].length] = -1;
        }
    }
}

int findCubes(vector<State>& states) {
    vector<int> halfLengths(states.size(), -1);
    getHalfLength(states, halfLengths);

    vector<bool> visited(states.size(), 0);
    vector<bool> cubes(states.size(), 0);
    stack<pair<int, bool>> st;

    st.push(make_pair(0, 0));
    visited[0] = 1;

    while(!st.empty()) {
        pair<int, bool> top = st.top();
        st.pop();
        if(top.second == 0) {
            visited[top.first] = 1;
            if (halfLengths[top.first] != -1 && visited[halfLengths[top.first]] == 1) {
                //cout << top.first << " " << halfLengths[top.first] << endl;
                cubes[top.first] = 1;
            }
            st.push(make_pair(top.first, 1));
            for (int i = 0; i < ALPHABET_LENGTH; i++) {
                if (states[top.first].transition[i] != 0) {
                    st.push(make_pair(states[top.first].transition[i], 0));
                }
            }
        }
        else {
            visited[top.first] = 0;
        }
    }

    int cubeCount = 0;
    for(int i = 0; i < cubes.size(); i++) {
        cubeCount += cubes[i];
    }
    return cubeCount;
}