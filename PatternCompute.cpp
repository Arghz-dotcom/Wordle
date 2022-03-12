#include "PatternCompute.h"
#include <string>
#include <vector>

string PatternCompute::PatternToStringOfSquares(int pattern, int wordSize)
{
    string res;

    int current = pattern;
    for (int k = 0; k < wordSize;k++)
    {
        int a = current % 3;
        res += a == GREEN ? "V" : (a == YELLOW ? "J" : "G");
        current = current / 3;
    }
    return res;
}

int PatternCompute::PatternToNumeric(int patternSize, vector<int> pattern)
{
    int res = 0;

    for (int k = 0; k < patternSize; k++)
    {
        res += pattern[k] * (int)pow(3, k);
    }

    return res;
}

int PatternCompute::Compute(const string& tentative, string truth)
{
    vector<int> result(tentative.size(), GREY); // Grey coded by 0, default value

    for (int k = 0; k < tentative.size(); k++)
    {
        if (tentative[k] == truth[k])
        {
            result[k] = GREEN;        // Green coded by 2
            truth[k] = '-';
        }
    }

    for (int k = 0; k < tentative.size(); k++)
    {
        if (result[k] != 0) continue;

        bool found = false;
        for (int k2 = 0; k2 < tentative.size(); k2++)
        {
            // If found elsewhere and that elsewhere is not already green
            if (tentative[k] == truth[k2])
            {
                found = true;
                truth[k2] = '-';
                break;
            }
        }
        if (found)
            result[k] = YELLOW;    // Yellow coded by 1

    }

    int patternNumeric = PatternToNumeric((int)tentative.size(), result);
    return patternNumeric;
}