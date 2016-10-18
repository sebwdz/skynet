//
// Created by sebastien on 8/12/16.
//

#include        <chanel.hpp>
#include        "Neuronal/Neuron/MLP.hpp"
#include        "Neuronal/Network/MLPerceptron.hpp"

namespace   Skynet {
    namespace       Neuronal {

        void MLPerceptron::setExpected(std::vector<double> const &expected) {
            PerceptronLayer         *layer;
            MLPNeuron               *neuron;

            layer = m_layers.back();
            for (unsigned int it = 0; it < layer->getCellsNb(); it++) {
                if ((neuron = dynamic_cast<MLPNeuron*>(layer->getCell(it)))) {
                    neuron->addGradient(expected[it] - neuron->getOutput());
                }
            }
        }

        void MLPerceptron::generate(json11::Json const& json) {
            PerceptronLayer     *layer;
            json11::Json const  &layers = json["layers"];
            Neuron              *neuron;

            Perceptron::generate(json);
            for (unsigned int it = 0; it < layers.array_items().size(); it++) {
                layer = new PerceptronLayer();
                for (unsigned int neuronit = 0; neuronit < (unsigned int)layers[it].int_value();  neuronit++) {
                    neuron = new MLPNeuron();
                    for (unsigned int x = 0; x < m_layers[it]->getCellsNb(); x++) {
                        neuron->addInput(m_layers[it]->getCell(x));
                    }
                    layer->addCell(neuron);
                }
                addLayer(layer);
            }
        }
    }
}