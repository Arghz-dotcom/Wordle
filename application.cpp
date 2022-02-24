#include <algorithm>
#include <fstream>
#include <string>

#include "application.h"
#include "GameState.h"
#include "Loader.h"





int ComputePattern(const string &tentative, string truth)
{
    vector<int> result(tentative.size(), 0);

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

    int res = 0;

    for(int k = 0; k < tentative.size(); k++)
    {
        res += result[k] * pow(3,k);
    }

    return res;
}


int AutomaticPlay(const vector<string>& words, const string& ground_truth, const string& initial_mask)
{
    cout << "\n*** NEW GAME Truth=" << ground_truth << endl;

    int K = words[0].size();
    GameState state(K, initial_mask);

    return 0;
}

int AutoWordle(const string& ground_truth)
{
    int K = ground_truth.size();

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


