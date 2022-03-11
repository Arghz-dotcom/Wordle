#pragma once

#include <string>
#include <vector>

using namespace std;

/* A class to contain the current state of the game : words that have been played, and patterns obtained */
class GameState
{
private:
    static constexpr char ASCII_A = 65;
    size_t wordSize;
    struct Step
    {
        Step(const string &word, int p) :
            played_word(word),
            pattern(p)
        {}
        string played_word;
        int pattern;
    };
    vector<Step> steps;
    vector<int> green_mask;             // Redundant information for speed : the list of green letters (-1 if not known, 0 for A, 1 for B etc)

public:
    explicit GameState(int K_);
    GameState(size_t K_, const string& mask);
    GameState(const GameState& that);
    size_t GetWordSize() const;
    void Update(const string& word, int pattern);
    bool isCompatible(const string& candidate_truth, bool check_only_last_step) const;
    int NbOfCompatibleWords(const vector<string>& words);
};

