#include "ANN.h"

void ANN::run()
{    
    prepareNN();

    // h: total # of iterations
    for(int h = 0; h < k; h++)
    {
        // i: number of input lines
        for(int i = 0; i < (int)train_input->size(); i++)
        {
            setInputLayer(i, train_input);

            // j: number of layers
            for(int j = 1; j < (int)structure->size(); j++)
            {
                // k: number of nodes in layer
                for(int k = 0; k < (int)neural_network[j].size(); k++)
                {
                    neural_network[j][k] = activation(j, k);
                }
            }

            // Output layer error
            // j: number of layers
            for(int j = 0; j < neural_network.back().size(); j++)
            {
                double aj = neural_network.back()[j];
                double yj = output_encoding[train_output->at(i)][j];
                error.back()[j] = aj*(1 - aj)*(yj - aj);
            }

            // Inner layer errors
            // j: number of layers
            for(int j = neural_network.size() - 2; j > 0; j--)
            {
                // k: number of nodes in layer
                for(int k = 0; k < neural_network[j].size(); k++)
                {
                    double sum = 0;

                    // l: number of nodes in next layer
                    for(int l = 0; l < structure->at(j+1); l++)
                    {
                        int indexBuffer = getIndexBuffer(j);
                        sum += error[j][k]*weights->at(indexBuffer + k)[l];
                    }
                    double ai = neural_network[j][k];
                    error[j][k] = ai*(1-ai)*sum;
                }
            }

            // j: number of rows in weights
            for(int j = 0; j < weights->size(); j++)
            {
                // k: number of elements in current weight table row
                for(int k = 0; k < weights->at(j).size(); k++)
                {
                    weights->at(j)[k] = weights->at(j)[k] + (ALPHA*neural_network[j][k]*error[j][k]);
                }
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

// Sets neural network input layer to vector from input file
void ANN::setInputLayer(int pIndex, vector<vector<double> >* pSource)
{
    neural_network[0] = pSource->at(pIndex);
}

// Runs activation algorithm on a neuron
double ANN::activation(int& pLayer, int& pNeuron)
{
    int indexBuffer = getIndexBuffer(pLayer);
    double sum = 0.0;
    for(int i = 0; i < structure->at(pLayer-1); i++)
    {
        sum += neural_network[pLayer-1].at(i) * 
            weights->at(indexBuffer + i).at(pNeuron);
    }
    return 1 / (1 + exp(-sum));
}

// Calculates offset value for weights values
int ANN::getIndexBuffer(int& pLayer)
{
    int indexBuffer = 0;
    for(int i = 0; i < pLayer-1; i++)
    {
        indexBuffer += structure->at(i);
    }
    return indexBuffer;
}