//
// Created by sebastien on 8/12/16.
//

#ifndef SKYNET_NEURON_PERCEPTRON_HPP
#define SKYNET_NEURON_PERCEPTRON_HPP

#include            "Simple.hpp"

namespace       Skynet {
    namespace       Neuronal {
        class           PerceptronNeuron : public Skynet::Neuronal::SimpleNeuron {
        public:
            PerceptronNeuron();

            void                setError(double);
            void                learn();

        private:
            double              m_error;
        };
    }
}

#endif //SKYNET_PERCEPTRON_HPP
