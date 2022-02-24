
#include <algorithm>
#include <fstream>
#include <string>
#include "application.h"
#include "GameState.h"





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

// Load words with a given length. File are assumed to be like "data/mots_5.txt"
vector<string> LoadWords(int K, int N)
{
    // Read file dictionnary of words
    vector<string> words;
    const string filename = "data/mots_" + to_string(K) + ".txt";
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Failed to open file: " << filename << endl;
        // A bit extreme, but if we are here the program won't work and will crash soon emough.
        abort();
    }

    string line;

    while (getline(file, line) && words.size() < N)
    {
        // Convert to CAPS : after we assume there is nothing elese than A-Z
        for_each(line.begin(), line.end(), [](char& c)
            {
                c = ::toupper(c);
            });

        if (find(words.begin(), words.end(), line) == words.end())
        {
            words.push_back(line);
        }
    }
    return words;
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

    vector<string> words = LoadWords(K, 4096);

    string initial_mask;
    for (int k = 0;k < K;k++) initial_mask += '.';

    int score = AutomaticPlay(words, ground_truth, initial_mask);

    return score;
}



int main()
{
    AutoWordle("REPAS");
    
}


