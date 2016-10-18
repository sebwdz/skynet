//
// Created by sebastien on 8/12/16.
//

#ifndef SKYNET_PMC_HPP
#define SKYNET_PMC_HPP

#include        "Simple.hpp"

namespace       Skynet {
    namespace       Neuronal {
        class           MLPNeuron : public Skynet::Neuronal::SimpleNeuron {
        public:

            MLPNeuron();

            void                addGradient(double);
            void                setDerived(double (*)(double, double));

            void                learn();

        private:
            double              m_gradient;
            std::vector<double> m_momentum;
            double              (*m_derived)(double, double);
        };
    }
}

#endif //SKYNET_PMC_HPP
