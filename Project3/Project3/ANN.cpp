#include "ANN.h"

void ANN::run()
{    
    prepareNN();

    // Main loop
    for(int i = 0; i < train_input->size(); i++)
    {
        setInputLayer(i, train_input);
        for(int i = 1; i < structure->size(); i++)
        {
            for(int j = 0; j < neural_network[i].size(); j++)
            {
                neural_network[i][j] = activation(i, j);
            }
        }
    }
}

// Sets size of all vectors in neural network based on inputs
void ANN::prepareNN()
{
    neural_network.resize(structure->size());
    for(int i = 0; i < neural_network.size(); i++)
    {
        neural_network[i].resize(structure->at(i));
    }
}

void ANN::setInputLayer(int pIndex, vector<vector<double> >* pSource)
{
    neural_network[0] = pSource->at(pIndex);
}

double ANN::activation(int& pLayer, int& pNeuron)
{
    int indexBuffer = 0;
    for(int i = 0; i < pLayer-1; i++)
    {
        indexBuffer += structure->at(i);
    }
    double sum = 0.0;
    for(int i = 0; i < structure->at(pLayer-1); i++)
    {
        sum += neural_network[pLayer-1].at(i) * 
            weights->at(indexBuffer + i).at(pNeuron);
    }
    return 1 / (1 + exp(-sum));
}