#include "StdAfx.h"
#include "EstimationMaximization.h"


CEstimationMaximization::CEstimationMaximization(vector<char>* observations, vector<vector<double> >* transition, vector<vector<double> >* sensory, vector<char>* original)
	: pObservations(observations)
	, pTransition(transition)
	, pSensory(sensory)
	, pOriginal(original)
{
	// Initialize probablitlies for all states at t0
	for(int i = 0; i < 3; i++)
	{
		state[i] = log2(1.0 / 3.0)*(-1);
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
			state[i] = min(i) + sensory;
		}
	}
}

double CEstimationMaximization::min(int current)
{
	double smallest;
	double candidates[3];
	for(int i = 0; i < 3; i++)
	{
		candidates[i] = state[current] + pTransition->at(current).at(i);
		if(i == 0) {
			smallest = candidates[0];
		}
		else if(candidates[i] < smallest) {
			smallest = candidates[i];
		}
	}
	return smallest;
}