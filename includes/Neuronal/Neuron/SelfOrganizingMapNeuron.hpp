//
// Created by sebastien on 10/2/16.
//

#ifndef SKYNET_SELFORGANIZINGMAPNEURON_HPP
#define SKYNET_SELFORGANIZINGMAPNEURON_HPP

#include            "../Neuron.hpp"

namespace   Skynet {
    namespace   Neuronal {
        class           SelfOrganizingMapNeuron : public Neuron {
        public:
            void                            setPos(std::pair<double, double> const&);
            void                            exec();
            void                            learn(double);
            std::pair<double, double> const &getPos() const;

        private:
            std::pair<double, double>       m_pos;
        };

    }
}

#endif //SKYNET_SELFORGANIZINGMAPNEURON_HPP
