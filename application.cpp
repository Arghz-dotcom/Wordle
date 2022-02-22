#include <iostream>
#include <vector>
#include <io.h>
#include <fcntl.h>

using namespace std;


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

string PatternToStringOfSquares(int pattern, int K)
{
    string res;

    int current = pattern;
    for(int k=0; k<K;k++)
    {
        int a = current%3;
        res += a==2 ? "V" : (a==1 ? "J" : "G");
        current = current/3;
    }
    return res;
}

void PrintTest(const string &truth, const string &word)
{
    cout << "(" << truth << ")" << " " << word << " " << PatternToStringOfSquares(ComputePattern(word,truth),word.size()) << endl;
}

void BasicRuleTest()
{
    PrintTest("ABCDE","AXXXX");     // 🟩⬛⬛⬛⬛ one good
    PrintTest("ABCDE","XAXXX");     // ⬛🟨⬛⬛⬛ one misplaced
    PrintTest("ABCDE","AEXXX");     // 🟩🟨⬛⬛⬛ one good one misplaced

    PrintTest("ABCDE","AAXXX");     // 🟩⬛⬛⬛⬛ one good once
    PrintTest("ABCDE","XAAXX");     // ⬛🟨⬛⬛⬛ double misplacement of the same letter

    PrintTest("AABCD","AXAXX");     // 🟩⬛🟨⬛⬛ same letter twice one good, a second copy misplaced
    PrintTest("AABCD","AAXXX");     // 🟩🟩⬛⬛⬛
    PrintTest("AABCD","AAXXA");     // 🟩🟩⬛⬛⬛
    PrintTest("AAACD","AAXXA");     // 🟩🟩⬛⬛🟨 there is a third copy somewhere
}


int main()
{
    BasicRuleTest();
}