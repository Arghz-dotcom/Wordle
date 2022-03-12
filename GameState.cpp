#include "application.h"
#include "GameState.h"
#include "PatternCompute.h"

/* A class to contain the current state of the game : words that have been played, and patterns obtained */

// Base constructor
GameState::GameState(int K_) //explicit ?
{
    wordSize = K_;
    for (int k = 0;k < wordSize;k++)
        green_mask.push_back(NO_LETTER);
}

// Constructor with mask
GameState::GameState(int K_, const string& mask)
{
    wordSize = K_;
    for (int k = 0;k < wordSize;k++)
    {
        char c_mask = mask[k];
        if (c_mask >= ASCII_A && c_mask < ASCII_A + 26)  // if the mask specifies a letter
            green_mask.push_back(c_mask - ASCII_A);
        else 
            green_mask.push_back(NO_LETTER);
    }
}

// Copy constructor
GameState::GameState(const GameState& that) = default;


// Update the state by giving a word and its associated obtained pattern (we don't check size, warning)        
void GameState::Update(const string& word, int pattern)
{
    steps.emplace_back(word, pattern);

    // Decode pattern to register green letters
    int current = pattern;
    for (int k = 0;k < wordSize;k++)
    {
        int a = current % 3;
        if (a == 2)    // if the letter was good and well placed
        {
            char c = word[k];
            green_mask[k] = (c - ASCII_A);   // 0 for letter A
        }
        current /= 3;
    }
}


// Whether a word is compatible with current state of the game
// Compatible : it could be the solution ie, it could have produced that sequence.

bool GameState::isCompatible(const string& candidate_truth, bool check_only_last_step) const
{
    // First check the green mask to save time
    for (int k = 0; k < wordSize; k++)
    {
        if (green_mask[k] != NO_LETTER)
        {
            char c = candidate_truth[k];
            if (c - ASCII_A != green_mask[k])
                return false;
        }
    }

    // Then check each of the previous steps of the game, to see whether that candidate truth word could have produced that series of patterns
    // We check in reverse assuming the later patterns carry more constraints (with option to check only that one if we know other are satisied)
    for (int i = (int)steps.size() - 1; i >= 0; i--)
    {
        const string& word = steps[i].played_word;
        int pattern = steps[i].pattern;
        PatternCompute patternCompute;
        if (patternCompute.Compute(word, candidate_truth) != pattern)
            return false;   // not compatible == That candidate_truth would not have produced that observed pattern

        if (i == steps.size() - 1 && check_only_last_step)
            return true;
    }
    return true;
}


int GameState::NbOfCompatibleWords(const vector<string>& words)
{
    int count = 0;
    for (int wordIndex = 0; wordIndex < words.size(); wordIndex++)
    {
        string word = words[wordIndex];
        if (isCompatible(word, false))
            count++;
    }
    return count;
}

size_t GameState::GetWordSize() const { return wordSize; }


