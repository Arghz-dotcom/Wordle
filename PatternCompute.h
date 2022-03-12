#pragma once
#include <string>
#include <vector>

using namespace std;

class PatternCompute
{
public:
	string PatternToStringOfSquares(int pattern, int wordSize);
	int PatternToNumeric(int patternSize, vector<int> pattern);
};

