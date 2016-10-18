//
// Created by sebastien on 8/12/16.
//

#ifndef SKYNET_NEURON_HPP
#define SKYNET_NEURON_HPP

# include       <vector>
# include       <utility>
# include       "Neuronal/Excitable.hpp"

namespace Skynet {

    namespace   Neuronal {
        class           Neuron : public Skynet::Neuronal::Excitable {
        public:

            Neuron();
            virtual ~Neuron();

            void                                                    addInput(Skynet::Neuronal::Excitable *);
            void                                                    addInput(Skynet::Neuronal::Excitable *, double);
            void                                                    setBiais(double);

            std::pair<Skynet::Neuronal::Excitable*, double> const   &getInput(unsigned int) const;
            unsigned                                                getInputNb() const;
            double                                                  getBiais() const;

        protected:
            double                                                              m_biais;
            std::vector<std::pair<Skynet::Neuronal::Excitable*, double> >       m_inputs;
        };
    }
}

#endif //SKYNET_NEURON_HPP
