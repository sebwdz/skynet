//
// Created by sebastien on 8/12/16.
//

#include            <iostream>
#include            "Neuronal/Neuron.hpp"
#include            "Tools/Utils.hpp"

namespace       Skynet {
    namespace       Neuronal {

        Neuron::Neuron() {
            m_biais = Skynet::Tools::rand();
        }

        Neuron::~Neuron() {
            for (unsigned int it = 0; it < m_inputs.size(); it++)
                delete m_inputs[it].first;
            m_inputs.clear();
        }

        void            Neuron::addInput(Skynet::Neuronal::Excitable *input) {
            addInput(input, Skynet::Tools::rand());
        }

        void            Neuron::addInput(Skynet::Neuronal::Excitable *input, double value) {
            m_inputs.push_back(std::make_pair(input, value));
        }

        void            Neuron::setBiais(double biais) {
            m_biais = biais;
        }

        std::pair<Skynet::Neuronal::Excitable*, double> const       &Neuron::getInput(unsigned int key) const {
            return (m_inputs.at(key));
        }

        unsigned int                        Neuron::getInputNb() const {
            return (m_inputs.size());
        }

        double                              Neuron::getBiais() const {
            return (m_biais);
        }
    }
}