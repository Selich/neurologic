#ifndef NET_HPP
#define NET_HPP
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>

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
            m_layers.back().push_back(Neuron(nOutputs));
            cout << "New neuron created" << endl;
        }
        
        
    }
}


#endif