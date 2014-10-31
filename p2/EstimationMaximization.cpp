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
}

CEstimationMaximization::~CEstimationMaximization()
{
}

void CEstimationMaximization::calculateViterbi()
{
    // Initialize probablitlies for all states at t0    
    for(int i = 0; i < 3; i++)
    {
        delete mViterbi[i];
        mViterbi[i] = new vector<double>();
        mViterbi[i]->push_back(log2(1.0 / 3.0)*(-1));
        pBacktracking[i] = new vector<int>();
    }
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
}

void CEstimationMaximization::getMostProbablePath()
{
    delete path;
    path = new vector<char>();
    int iter;
    string result = "";
    for(int i = 0; i < 3; i++)
    {
        if(i == 0 || mViterbi[i]->back() < mViterbi[iter]->back())
        {
            iter = i;
        }
    }    
    path->push_back(stateIntToChar(iter));
    for(int i = pBacktracking[0]->size() - 1; i >= 0; i--)
    {
        iter = pBacktracking[iter]->at(i);
        path->insert(path->begin(), stateIntToChar(iter));
    }    
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
            pTransition->at(i).at(j) = -log2(value);
        }
    }
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            double numerator = sensoryMatches(i, j) + K;
            double denominator = numValInPath(i) + 2*K;
            double value = numerator / denominator;
            pSensory->at(i).at(j) = -log2(value);
        }
    }
}

void CEstimationMaximization::showResult()
{
    ofstream myfile;
    myfile.open("output.txt");
    int matches = 0;
    for(unsigned i = 0; i < pOriginal->size(); i++)
    {
        if(pOriginal->at(i) == path->at(i+1))
        {
            matches++;
        }
    }
    cout << "\nTransition probabilities learned:\n";
    myfile << "\nTransition probabilities learned:\n";
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            stringstream ss;
            ss << fixed << setprecision(6) << setw(12) << pow(2, -pTransition->at(i).at(j)) << " ";
            cout << ss.str();
            myfile << ss.str();
        }
        myfile << "\n";
        cout << "\n";
    }

    cout << "\nSensory probabilities learned:\n";
    myfile << "\nSensory probabilities learned:\n";
    for(int i = 0; i < 3; i++)
    {
        stringstream ss;
        ss << fixed << setprecision(6) << setw(12) << pow(2, -pSensory->at(i).at(0)) << "\n";
        cout << ss.str();
        myfile << ss.str();
    }
    stringstream ss;
    double result = ((double)matches)/((double)pOriginal->size())*100.0;
    ss << fixed << setprecision(2) << "\nAccuracy:\n" << result << "%\n";
    cout << ss.str() << "\n";
    myfile << ss.str() << "\nSequence of States:\n";
    for(char c : *path)
    {
        myfile << c;
    }
    myfile.close();
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

int CEstimationMaximization::sensoryToInt(char &sensory)
{
    if(sensory == 'H') 
    {
        return 0;
    }
    else if(sensory == 'T')
    {
        return 1;
    }
    return -1;
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
    for(unsigned i = 0; i < path->size() - 1; i++)
    {
        if(path->at(i) == val)
        {
            total++;
        }
    }
    return total;
}

int CEstimationMaximization::sensoryMatches(int &state, int &sensory)
{
    int matches = 0;
    for(unsigned i = 0; i < pObservations->size(); i++)
    {
        if(path->at(i + 1) == stateIntToChar(state) && 
        sensoryToInt(pObservations->at(i)) == sensory)
        {
            matches++;
        }
    }
    return matches;
}

int CEstimationMaximization::numValInObs(int& sensory)
{
    int total = 0;
    for(char c : *pObservations)
    {
        if(sensoryToInt(c) == sensory)
        {
            total++;
        }
    }
    return total;
}