#pragma once
#include <string>
#include <vector>

using namespace std;

class Loader
{
public:
	// Load words with a given length. File are assumed to be like "data/mots_5.txt"
	vector<string> LoadWords(int K, int N);
};

