//
// application.h
//

#pragma once

#include <iostream>
#include <vector>
#include <io.h>
#include <fcntl.h>

using namespace std;

int ComputePattern(const string& tentative, string truth);

int PatternToNumeric(size_t patternSize, vector<int> pattern);