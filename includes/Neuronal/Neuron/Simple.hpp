//
// Created by sebastien on 8/12/16.
//

#ifndef SKYNET_SIMPLE_HPP
#define SKYNET_SIMPLE_HPP

#include        "Neuronal/Neuron.hpp"

namespace       Skynet {
    namespace       Neuronal {
        class           SimpleNeuron : public Skynet::Neuronal::Neuron {
        public:
            SimpleNeuron();
            virtual ~SimpleNeuron() {}
            virtual void                    exec();
            void                            setCoef(double);
            void                            setActivate(double (*)(double, double));

        protected:
            double              m_potential;
            double              m_coef;
            double              (*m_activate)(double, double);
        };
    }
}

#endif //SKYNET_SIMPLE_HPP
