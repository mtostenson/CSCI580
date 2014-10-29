#include "StdAfx.h"
#include "EstimationMaximization.h"


CEstimationMaximization::CEstimationMaximization(
    vector<char>* observations,
    vector<vector<double> >* transition,
    vector<vector<double> >* sensory,
    vector<char>* original,
    int iterations)
    : pObservations(observations)
    , pTransition(transition)
    , pSensory(sensory)
    , pOriginal(original)
    , mIterations(iterations)
{
    // Initialize probablitlies for all states at t0    
    for(int i = 0; i < 3; i++)
    {
        mState[i] = new vector<double>();
        mState[i]->push_back(log2(1.0 / 3.0)*(-1));
    }
}


CEstimationMaximization::~CEstimationMaximization()
{
}

void CEstimationMaximization::calculateSequenceOfStates()
{
    for(unsigned i = 0; i < pOriginal->size(); i++)
    {
        int curStateValue = charToStateInt(pOriginal->at(i));
        for(int j = 0; j < 3; j++)
        {
            double minimum;
            for(int k = 0; k < 3; k++)
            {
                double temp = mState[k]->at(i) + pTransition->at(curStateValue)[k];
                if(k == 0 || temp < minimum)
                {
                    minimum = temp;
                }
            }
            if(pObservations->at(i) == 'H')
            {
                minimum += pSensory->at(curStateValue)[0];
            } else if(pObservations->at(i) == 'T')
            {
                minimum += pSensory->at(curStateValue)[1];
            }
            mState[j]->push_back(minimum);
        }
    }
}

int CEstimationMaximization::charToStateInt(char& c)
{
    switch(c)
    {
    case 'B':
        return 0;
    case 'L':
        return 1;
    case 'M':
        return 2;
    default:
        fprintf(stderr, "Invalid char: %c\n", c);
        return -1;
    }
}
