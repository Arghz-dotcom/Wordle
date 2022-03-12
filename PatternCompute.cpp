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
        res += a == 2 ? "V" : (a == 1 ? "J" : "G");
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