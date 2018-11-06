#include <iostream>
#include <vector>

// input layer -> hidden layer 

using namespace std;

class Neuron {};


typedef vector<Neuron> Layer;

class Net {

private:
    vector<Layer> m_layers; // layerNumber , neuronNumber

public:
    Net(const vector<unsigned> &topo);
    void feedForward(const vector<double> &inputVal) {};
    void backProp(const vector<double> &targetVal) {};
    void getResults(const vector<double> &resultVal) const {};




};
Net::Net(const vector<unsigned> &topo){
    for (unsigned layerNumber = 0; layerNumber < topo.size(); ++layerNumber)
    {
        // append new Layer
        m_layers.push_back(Layer());

        
        // needed for one more biased neuron ( <= )
        for( unsigned neuronNumber = 0; neuronNumber <= topo[layerNumber]; ++neuronNumber)
        {
            m_layers.back().push_back(Neuron());
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