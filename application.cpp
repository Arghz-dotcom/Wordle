#include <algorithm>
#include <fstream>
#include <string>

#include "application.h"
#include "GameState.h"
#include "Loader.h"


float ComputeEntropy(const GameState& initial_state, const string& word, const vector<string>& possible_solutions)
{
    float entropy = 0;
    int K = (int)initial_state.GetWordSize();

    // For each pattern we could get, compute expected entropy
    for (int pattern = 0; pattern < pow(3, K); pattern++)
    {
        // If we got that pattern from that word, in which state would we be
        GameState state(initial_state);
        state.Update(word, pattern);

        // In that case, count how many would be compatible as being the ground truth
        int cnt = 0;
        for (int jw = 0; jw < possible_solutions.size();jw++)
        {
            string candidate_word = possible_solutions[jw];
            cnt += state.isCompatible(candidate_word, true);     // we are checking previously possible solutions, so we look only at last step
        }
        float p = (float)cnt / (float)possible_solutions.size();
        if (p > 0)
        {
            entropy += -p * log2(p);
        }
    }

    return entropy;
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
        {
            possible_solutions.push_back(word);
        }
    }

    // If only one, we are done
    if (possible_solutions.size() == 1) return possible_solutions[0];

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

    // If less than 3, we limit our choice to the possible solutions, so we try to "shoot to kill"
    if (possible_solutions.size() < 4)
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

string PatternToStringOfSquares(int pattern, int K)
{
    string res;

    int current = pattern;
    for (int k = 0; k < K;k++)
    {
        int a = current % 3;
        res += a == 2 ? "V" : (a == 1 ? "J" : "G");
        current = current / 3;
    }
    return res;
}

int ComputePattern(const string &tentative, string truth)
{
    vector<int> result(tentative.size(), 0); // Grey coded by 0, default value

    for(int k = 0; k < tentative.size(); k++)
    {
        if(tentative[k]==truth[k])
        {
            result[k] = 2;        // Green coded by 2
            truth[k] = '-';
        }
    }

    for(int k = 0; k < tentative.size(); k++)
    {
        if (result[k] != 0) continue;

        bool fnd = false;
        for(int k2 = 0; k2 < tentative.size(); k2++)
        {
            // If found elsewhere and that elsewhere is not already green
            if(tentative[k] == truth[k2])
            {
                fnd = true;
                truth[k2] = '-';
                break;
            }
        }
        if(fnd) result[k] = 1;    // Yellow coded by 1

    }

    int res = PatternToNumeric(tentative.size(), result);
    return res;
}

int PatternToNumeric(size_t patternSize, vector<int> pattern)
{
    int res = 0;

    for (int k = 0; k < patternSize; k++)
    {
        res += pattern[k] * (int)pow(3, k);
    }

    return res;
}


int AutomaticPlay(const vector<string>& words, const string& ground_truth, const string& initial_mask)
{
    cout << "\n*** NEW GAME Truth=" << ground_truth << endl;

    size_t K = words[0].size();
    GameState state(K, initial_mask);
    int nb_compat = state.NbOfCompatibleWords(words);
    cout << "Nb of compatible words : " << nb_compat << " Entropy=" << log2(nb_compat);

    const int MAX_STEPS = 6;
    for (int s = 0; s < MAX_STEPS; s++)
    {
        string proposal;

        // If first steps Use known best words for opening
        if (s == 0)
        {
            if (initial_mask == ".....") proposal = "TARIE";
            if (initial_mask == "......") proposal = "SORTIE";
        }

        if (proposal.empty()) proposal = ComputeBestChoice(state, words);
        cout << '\n' << proposal;

        int pattern = ComputePattern(proposal, ground_truth);
        cout << " " << PatternToStringOfSquares(pattern, (int)state.GetWordSize()) << " ";

        if (proposal == ground_truth)
        {
            cout << "SOLVED IN " << (s + 1) << " STEPS" << endl;
            return s + 1;
        }

        double old_entropy = log2(state.NbOfCompatibleWords(words));
        state.Update(proposal, pattern);
        double new_entropy = log2(state.NbOfCompatibleWords(words));

        cout << "Entropy gain = " << (old_entropy - new_entropy);
        cout << " Nb of compatible words : " << state.NbOfCompatibleWords(words) << " New entropy=" << log2(state.NbOfCompatibleWords(words)) << " ";
    }
    return MAX_STEPS;
}

int AutoWordle(const string& ground_truth)
{
    int K = (int)ground_truth.size();

    Loader loader;
    vector<string> words = loader.LoadWords(K, 4096);

    string initial_mask;
    for (int k = 0;k < K;k++) initial_mask += '.';

    int score = AutomaticPlay(words, ground_truth, initial_mask);

    return score;
}



int main()
{
    AutoWordle("REPAS");
    
}


