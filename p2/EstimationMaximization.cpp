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
        mViterbi[i] = new vector<double>();
        mViterbi[i]->push_back(log2(1.0 / 3.0)*(-1));
        pBacktracking[i] = new vector<int>();
    }    
}

CEstimationMaximization::~CEstimationMaximization()
{
}

void CEstimationMaximization::calculateViterbi()
{
    for(unsigned i = 0; i < pOriginal->size(); i++)
    {
        for(int j = 0; j < 3; j++)
        {
            double minimum;
            int btValue;
            for(int k = 0; k < 3; k++)
            {
                double temp = mViterbi[k]->at(i) + pTransition->at(j)[k];
                if(k == 0 || temp < minimum)
                {
                    minimum = temp;
                    btValue = k;
                }
            }
            if(pObservations->at(i) == 'H')
            {
                minimum += pSensory->at(j)[0];
            } else if(pObservations->at(i) == 'T')
            {
                minimum += pSensory->at(j)[1];
            }
            mViterbi[j]->push_back(minimum);
            pBacktracking[j]->push_back(btValue);
        }
    }
    for(vector<int>* v : pBacktracking)
    {
        for(int i : *v)
        {
            fprintf(stdout, "%c ", stateIntToChar(i));
        }
        fprintf(stdout, "\n");
    }
}

void CEstimationMaximization::getMostProbablePath()
{
    path = new vector<char>();
    int iter;
    string result = "";
    for(int i = 0; i < 3; i++)
    {
        if(i == 0 || mViterbi[i]->back() < mViterbi[iter]->back())
        {
            iter = i;
            path->push_back(stateIntToChar(iter));
        }
    }    
    for(int i = pBacktracking[0]->size() - 1; i >= 0; i--)
    {
        iter = pBacktracking[iter]->at(i);
        path->insert(path->begin(), stateIntToChar(iter));
    }    
    for(char c : *path)
    {
        cout << c;
    }
    cout << endl;
}

void CEstimationMaximization::calculateTransAndSens()
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            double numerator = getNumTrans(j, i) + K;
            double denominator = numValInPath(j) + 3*K;
            double value = numerator / denominator;
            //cout << value << " ";
            pTransition->at(i).at(j) = -log2(value);
        }
    }
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            cout << pTransition->at(i).at(j) << " ";
        }
        cout << endl;
    }
}

char CEstimationMaximization::stateIntToChar(int& i) {
    switch(i)
    {
    case 0:
        return 'B';
    case 1:
        return 'L';
    case 2:
        return 'M';
    default:
        fprintf(stderr, "Invalid int: %d\n", i);
        return 'X';
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

int CEstimationMaximization::getNumTrans(int &a, int &b)
{
    int total = 0;
    for(unsigned i = 0; i < path->size()-1; i++)
    {
        if(charToStateInt(path->at(i)) == a && charToStateInt(path->at(i + 1)) == b)
        {
            total++;
        }
    }
    return total;
}

int CEstimationMaximization::numValInPath(int& x)
{
    int total = 0;
    char val = stateIntToChar(x);
    for(int i = 0; i < path->size() - 1; i++)
    {
        if(path->at(i) == val)
        {
            total++;
        }
    }
    return total;
}