#include <algorithm>
#include <fstream>
#include <iostream>

#include "Loader.h"

// Load words with a given length. File are assumed to be like "data/mots_5.txt"
vector<string> Loader::LoadWords(int wordSize, int numberOfWords) {
    // Read file dictionnary of words
    vector<string> words;
    const string filename = "data/mots_" + to_string(wordSize) + ".txt";
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Failed to open file: " << filename << endl;
        // A bit extreme, but if we are here the program won't work and will crash soon emough.
        abort();
    }

    string line;

    while (getline(file, line) && words.size() < numberOfWords)
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