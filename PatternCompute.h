#pragma once
#include <string>
#include <vector>

using namespace std;

class PatternCompute
{
private:
	const int GREY = 0;
	const int YELLOW = 1;
	const int GREEN = 2;
public:
	string PatternToStringOfSquares(int pattern, int wordSize);
	int PatternToNumeric(int patternSize, vector<int> pattern);
	int Compute(const string& tentative, string truth);
};

