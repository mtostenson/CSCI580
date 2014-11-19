#include "ANN.h"

void ANN::run()
{    
    prepareNN();

    // Main loop
    for(int h = 0; h < k; h++)
    {
        for(int i = 0; i < (int)train_input->size(); i++)
        {
            setInputLayer(i, train_input);
            for(int i = 1; i < (int)structure->size(); i++)
            {
                for(int j = 0; j < (int)neural_network[i].size(); j++)
                {
                    neural_network[i][j] = activation(i, j);
                }
            }

            for(int j = 0; j < neural_network.back().size(); j++)
            {
                double aj = neural_network.back()[j];
                double yj = output_encoding[train_output->at(i)][j];
                error.back()[j] = aj*(1 - aj)*(yj - aj);
            }

        }   
    }
}

// Sets size of all vectors in neural network based on inputs
void ANN::prepareNN()
{
    neural_network.resize(structure->size());
    error.resize(structure->size());
    for(unsigned i = 0; i < neural_network.size(); i++)
    {
        neural_network[i].resize(structure->at(i));
        error[i].resize(structure->at(i));
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