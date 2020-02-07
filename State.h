//
// Created by pon on 04.02.20.
//

#ifndef SUFFIX_AUTOMATON_STATE_H
#define SUFFIX_AUTOMATON_STATE_H

const int ALPHABET_LENGTH = 26;

struct State {
    int length, slink;
    int transition[ALPHABET_LENGTH] = {0};
    State(int _length, int _slink): length(_length), slink(_slink){}
};

#endif //SUFFIX_AUTOMATON_STATE_H
