//
// Created by sebastien on 8/12/16.
//

#include                <chanel.hpp>
#include                "Neuronal/Neuron/Perceptron.hpp"
#include                "Neuronal/Network/SimplePerceptron.hpp"

namespace           Skynet {
    namespace           Neuronal {
        void            SimplePerceptron::setExpected(std::vector<double> const &expected) {
            PerceptronLayer     *layer;
            PerceptronNeuron    *neuron;

            layer = m_layers.back();
            for (unsigned int it = 0; it < expected.size(); it++) {
                if ((neuron = dynamic_cast<PerceptronNeuron*>(layer->getCell(it))))
                    neuron->setError(expected[it] - neuron->getOutput());
            }
        }

        void            SimplePerceptron::generate(json11::Json const& json) {
            PerceptronLayer     *layer;
            unsigned int        nbOutputs = (unsigned int)json["outputs"].int_value();
            Neuron              *neuron;

            Perceptron::generate(json);

            layer = new PerceptronLayer();
            for (unsigned int neuronit = 0; neuronit < nbOutputs; neuronit++) {
                neuron = new SimpleNeuron();
                for (unsigned int x = 0; x < m_layers[0]->getCellsNb(); x++) {
                    neuron->addInput(m_layers[0]->getCell(x));
                }
                layer->addCell(neuron);
            }
            addLayer(layer);
        }
    }
}