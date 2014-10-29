#include "StdAfx.h"
#include "EstimationMaximization.h"


CEstimationMaximization::CEstimationMaximization(vector<char>* observations, vector<vector<double> >* transtion, vector<double>* sensory, vector<char>* original)
	: pObservations(observations)
	, pTransition(transtion)
	, pSensory(sensory)
	, pOriginal(original)
{	
}


CEstimationMaximization::~CEstimationMaximization()
{
}
	
