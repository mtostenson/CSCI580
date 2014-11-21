#include "ANN.h"

void ANN::run()
{    
    prepareNN();

    // h: total # of iterations
    for(int h = 0; h < iterations; h++)
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
            for(int j = neural_network.size() - 2; j >= 0; j--)
            {
                // k: number of nodes in layer
                for(int k = 0; k < neural_network[j].size(); k++)
                {
                    double sum = 0;
                    double left = 0;
                    double right = 0;

                    // l: number of nodes in next layer
                    for(int l = 0; l < structure->at(j+1); l++)
                    {
                        int buf = errorBuffer(j);
                        left = error[j+1][l];
                        right = weights->at(buf + k)[l]; // J WAS INDEXBUFFER
                        sum += left*right;
                    }
                    double ai = neural_network[j][k];
                    error[j][k] = ai*(1-ai)*sum;
                }
            }

            // Calculate dummies
            for(int j = 0; j < dummy.size(); j++)
            {
                for(int k = 0; k < dummy[j].size(); k++)
                {
                    dummy[j][k] = dummy[j][k] + (ALPHA * error[j][k]);
                }
            }

            // j: number of rows in weights
            for(int j = 0; j < weights->size(); j++)
            {
                // k: number of elements in current weight table row
                for(int k = 0; k < weights->at(j).size(); k++)
                {
                    int layer = layerFromWeightRow(j);
                    double wPrev = weights->at(j)[k];
                    double ai = neural_network[layerFromWeightRow(j)][k];
                    double dj = error[layer][k];
                    weights->at(j)[k] = wPrev + (ALPHA * ai * dj);
                }
            }
        }   
    }
}

void ANN::test()
{
    results = new vector<int>();
    for(int i = 0; i < (int)test_input->size(); i++)
    {
        setInputLayer(i, test_input);

        // j: number of layers
        for(int j = 1; j < (int)structure->size(); j++)
        {
            // k: number of nodes in layer
            for(int k = 0; k < (int)neural_network[j].size(); k++)
            {
                neural_network[j][k] = activation(j, k);
            }
        }

        // Euclidean
        double ED;
        double eSum, left, right;                        
        vector<double> distances;
        for(int j = 0; j < structure->at(structure->size() - 1); j++)
        {
            eSum = left = right = 0;
            for(int k = 0; k < structure->at(structure->size() - 1); k++)
            {
                left = output_encoding[j][k];
                right = neural_network[neural_network.size() - 1][k];
                double base = left - right;
                eSum += pow(base, 2.0);
            }            
            ED = sqrt(eSum);
            distances.push_back(ED);
        }
        
        int min = 0;
        for(int j = 0; j < distances.size(); j++)
        {
            if(distances[j] < distances[min] || j ==0)
            {
                min = j;
            }
        }
        results->push_back(min);
    }

    double total_correct = 0;
    for(int i = 0; i < test_output->size(); i++)
    {
        if(results->at(i) == test_output->at(i))
        {
            total_correct += 1;
        }
    }
    
    int lastHiddenLayer = structure->size() - 2;
    for(int i = 0; i < structure->at(lastHiddenLayer + 1); i++)
    {
        printf("%f\n", weights->at(errorBuffer(lastHiddenLayer))[i]);
    }

    printf("\n%f%%\n", (total_correct / test_output->size())*100);
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

    for(int i = 0; i < neural_network.size(); i++)
    {
        vector<double> row;
        for(int j = 0; j < neural_network[i].size(); j++)
        {
            row.push_back(DUMMY);
        }
        dummy.push_back(row);
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
    int indexBuffer = activationBuffer(pLayer);
    double sum = dummy[pLayer][pNeuron];
    for(int i = 0; i < structure->at(pLayer-1); i++)
    {
        sum += neural_network[pLayer-1].at(i) * 
            weights->at(indexBuffer + i).at(pNeuron);
    }
    return 1 / (1 + exp(-sum));
}

// Calculates offset value for weights values
int ANN::activationBuffer(int pLayer)
{
    int indexBuffer = 0;
    for(int i = 0; i < pLayer-1; i++)
    {
        indexBuffer += structure->at(i);
    }
    return indexBuffer;
}

int ANN::errorBuffer(int pLayer)
{
    int offset = 0;
    for(int i = 0; i < pLayer; i++)
    {
        offset += structure->at(i);
    }
    return offset;
}

int ANN::layerFromWeightRow(int& pRow)
{
    int sum = 0;
    int index = 0;
    for(; pRow < sum; index++, sum += structure->at(index));
    return index;
}