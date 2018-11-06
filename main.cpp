#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>

// input layer -> hidden layer 

using namespace std;


struct Connection 
{
    double weight;
    double delta;

};
class Neuron;


typedef vector<Neuron> Layer;

class Neuron {

private:

    static double randomWeight(); 
    double m_output;
    vector<Connection> m_outputWeight;
    // member index
    unsigned m_index;


public:
    Neuron();
    Neuron(unsigned nOutputs, unsigned index);
    void feedForward(const Layer &prevLayer);
    //getters
    double getOutputVal(void) const { return m_output; };
    //setters
    void setOutputVal(double val){ m_output = val; }


};
Neuron::Neuron(unsigned nOutputs, unsigned index){
    for (unsigned conn = 0 ; conn < nOutputs; ++conn){
        m_outputWeight.push_back(Connection());
        m_outputWeight.back().weight = randomWeight();
    }
    m_index = index;
}

void Neuron::feedForward(const Layer &prevLayer){
    // sum of the previous layer's outputs + bias node -> new input
    double sum = 0.0;

    for(unsigned n = 0; n <prevLayer.size(); ++n){
        sum += prevLayer[n].getOutputVal() *
               prevLayer[n].m_outputWeight[m_index].weight;

    }


}
double Neuron::randomWeight(){
    return rand() / double(RAND_MAX);
}

/////////////////////////////////////////////////////

class Net {

private:
    vector<Layer> m_layers; // layerNumber , neuronNumber

public:
    Net(const vector<unsigned> &topo);
    void feedForward(const vector<double> &inputVal) {};
    void backProp(const vector<double> &targetVal) {};
    void getResults(const vector<double> &resultVal) const {};




};
void Net::feedForward(const vector<double> &inputVal){
    //test if input vals is the same as the number of input neurons ( m_laters[0] )
    // m_layers[0] - 1 to remove the bias neuron
    assert(inputVal.size() == m_layers[0].size() - 1);

    // adds input values into the input neurons
    for (unsigned i = 0; i < inputVal.size(); ++i){
        m_layers[0][i].setOutputVal(inputVal[i]);
    }
    // forward propagate

    for (unsigned layerNumber = 1; layerNumber < m_layers.size(); ++layerNumber){
        Layer &prevLayer = m_layers[layerNumber - 1];
        for(unsigned n = 0; n < m_layers[layerNumber].size() - 1; ++n){
            m_layers[layerNumber][n].feedForward();
        }

    }


}
Net::Net(const vector<unsigned> &topo){
    for (unsigned layerNumber = 0; layerNumber < topo.size(); ++layerNumber)
    {
        // append new Layer
        m_layers.push_back(Layer());
        unsigned nOutputs = layerNumber == topo.size() - 1 ? 0 : topo[layerNumber + 1];

        
        // needed for one more biased neuron ( <= )
        for( unsigned neuronNumber = 0; neuronNumber <= topo[layerNumber]; ++neuronNumber)
        {
            m_layers.back().push_back(Neuron(nOutputs, neuronNumber));
            cout << "New neuron created" << endl;
        }
        
        
    }
}

int main(){

    vector<unsigned> topo;
    topo.push_back(3);
    topo.push_back(3);
    topo.push_back(1);
    Net net(topo);

    vector<double> inputVal;
    vector<double> targetVal;
    vector<double> resultVal;
    net.feedForward(inputVal);
    // testing outputs
    net.backProp(targetVal);
    net.getResults(resultVal);

}