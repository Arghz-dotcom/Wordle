#include <algorithm>
#include <fstream>
#include <string>

#include "application.h"
#include "GameState.h"
#include "Loader.h"
#include "PatternCompute.h"
#include "Settings.h"


float ComputeEntropy(const GameState& initial_state, const string& word, const vector<string>& possible_solutions)
{
    float entropy = 0;
    int wordSize = (int)initial_state.GetWordSize();

    // For each pattern we could get, compute expected entropy
    for (int pattern = 0; pattern < pow(3, wordSize); pattern++)
    {
        // If we got that pattern from that word, in which state would we be
        GameState state(initial_state);
        state.Update(word, pattern);

        // In that case, count how many would be compatible as being the ground truth
        int count = 0;
        for (int jw = 0; jw < possible_solutions.size();jw++)
        {
            string candidate_word = possible_solutions[jw];
            count += state.isCompatible(candidate_word, true);     // we are checking previously possible solutions, so we look only at last step
        }
        float p = count / (float)possible_solutions.size();
        if (p > 0)
            entropy += -p * log2(p);
    }

    return entropy;
}

void DisplayBestChoices10(vector<string> possible_solutions)
{
    // If less than 10 : display
    cout << "Number of possible solutions " << possible_solutions.size() << " :";
    if (possible_solutions.size() < 10)
    {
        for (int iw = 0;iw < possible_solutions.size();iw++)
        {
            cout << possible_solutions[iw] << ",";
        }
    }
    cout << endl;
}

string ComputeBestChoice(GameState initial_state, const vector<string>& words)
{
    vector<string> candidate_pool = words;

    // Build the list of remaining possible solutions at this stage
    vector<string> possible_solutions;
    for (int iw = 0; iw < words.size(); iw++)
    {
        string word = words[iw];
        if (initial_state.isCompatible(word, false))
            possible_solutions.push_back(word);
    }

    // If only one, we are done
    if (possible_solutions.size() == 1) 
        return possible_solutions[0];

    DisplayBestChoices10(possible_solutions);

    // If less than 3, we limit our choice to the possible solutions, so we try to "shoot to kill"
    if (possible_solutions.size() <= 3)
    {
        candidate_pool = possible_solutions;
    }

    // Now find the word with the maximum entropy    
    string best_choice;
    float best_entropy = -1;
    for (int iw = 0; iw < candidate_pool.size(); iw++)
    {
        // if(iw%100==0) cout << "N°"<<iw<<endl;     // verbose
        string word = candidate_pool[iw];

        float entropy = ComputeEntropy(initial_state, word, possible_solutions);
        if (entropy > best_entropy)
        {
            best_entropy = entropy;
            best_choice = word;
            cout << "New best option (n°" << iw << ") : " << best_choice << " : " << best_entropy << " bits" << endl;
        }

    }
    return best_choice;
}

int AutomaticPlay(const vector<string>& words, const string& ground_truth, const string& initial_mask)
{
    cout << "\n*** NEW GAME Truth=" << ground_truth << endl;

    int wordSize = (int)words[0].size();
    GameState state(wordSize, initial_mask);
    int nb_compat = state.NbOfCompatibleWords(words);
    cout << "Nb of compatible words : " << nb_compat << " Entropy=" << log2(nb_compat);
    Settings settings;

    const int MAX_STEPS = 6;
    for (int step = 1; step <= MAX_STEPS; step++)
    {
        string proposal = settings.InitialProposal(step, initial_mask);
        if (proposal.empty())
            proposal = ComputeBestChoice(state, words);
        cout << '\n' << proposal;

        PatternCompute patternCompute;
        int pattern = patternCompute.Compute(proposal, ground_truth);
        cout << " " << patternCompute.PatternToStringOfSquares(pattern, (int)state.GetWordSize()) << " ";

        if (proposal == ground_truth)
        {
            cout << "SOLVED IN " << step << " STEPS" << endl;
            return step;
        }

        double old_entropy = log2(state.NbOfCompatibleWords(words));
        state.Update(proposal, pattern);
        int new_nbcompatiblewords = state.NbOfCompatibleWords(words);
        double new_entropy = log2(new_nbcompatiblewords);

        cout << "Entropy gain = " << (old_entropy - new_entropy);
        cout << " Nb of compatible words : " << new_nbcompatiblewords << " New entropy=" << new_entropy << " ";
    }
    return MAX_STEPS;
}

int AutoWordle(const string& ground_truth)
{
    int wordSize = (int)ground_truth.size();

    Loader loader;
    vector<string> words = loader.LoadWords(wordSize, 4096);

    string initial_mask;
    for (int k = 0;k < wordSize;k++)
        initial_mask += '.';

    int score = AutomaticPlay(words, ground_truth, initial_mask);

    return score;
}



int main()
{
    AutoWordle("REPAS");
    
}


