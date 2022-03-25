#include "Settings.h"

string Settings::InitialProposal(int step, const string& initial_mask)
{
    string proposal;

    // If first steps Use known best words for opening
    if (step == 1)
    {
        if (initial_mask == ".....")
            proposal = "TARIE";
        if (initial_mask == "......")
            proposal = "SORTIE";
    }
    return proposal;
}