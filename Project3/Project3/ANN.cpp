#include "ANN.h"

void ANN::run()
{
    setInputLayer(0, train_input);
}

void ANN::setInputLayer(int pIndex, vector<vector<double>* >* pSource)
{
    neural_network->insert(neural_network->begin, pSource->at(pIndex));
}