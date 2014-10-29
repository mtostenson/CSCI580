#include "StdAfx.h"
#include "EstimationMaximization.h"


CEstimationMaximization::CEstimationMaximization(vector<char>* observations, vector<vector<double> >* transition, vector<vector<double> >* sensory, vector<char>* original, int iterations)
    : pObservations(observations)
    , pTransition(transition)
    , pSensory(sensory)
    , pOriginal(original)
    , mIterations(iterations)
{
    // Initialize probablitlies for all states at t0
    for(int i = 0; i < 3; i++)
    {
        mState[i] = log2(1.0 / 3.0)*(-1);
    }
}


CEstimationMaximization::~CEstimationMaximization()
{
}

void CEstimationMaximization::process()
{
    for(char observation : *pObservations)
    {
        for(int i = 0; i < 3; i++)
        {
            double sensory;
            if(observation == 'H')
            {
                sensory = pSensory->at(i).at(0);
            }
            else if(observation == 'T')
            {
                sensory = 1 - pSensory->at(i).at(1);
            }
            mState[i] = min(i) + sensory;
        }
    }
}

double CEstimationMaximization::min(int current)
{
    double smallest;
    int from;
    double candidates[3];
    for(int i = 0; i < 3; i++)
    {
        candidates[i] = mState[current] + (pTransition->at(current)).at(i);
        if(i == 0) {
            smallest = candidates[0];
            from = 0;
        }
        else if(candidates[i] < smallest) {
            smallest = candidates[i];
            from = i;
        }
    }
    mBacktrack[current].push_back(from);
    return smallest;
}