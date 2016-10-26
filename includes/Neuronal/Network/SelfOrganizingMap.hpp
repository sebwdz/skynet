//
// Created by sebastien on 10/2/16.
//

#ifndef SKYNET_SELFORGANIZINGMAP_HPP
#define SKYNET_SELFORGANIZINGMAP_HPP

#include <Neuronal/Experiences/UnsupervisedExperience.hpp>
#include "../../../libs/json11/json11.hpp"
#include "../Network.hpp"
#include "../Neuron/SelfOrganizingMapNeuron.hpp"

namespace Skynet {

    namespace Neuronal {

        class SelfOrganizingMap : public Network {
        public:
            void                        setInputs(std::vector<double> const&);
            std::vector<double> const   &getOutputs() const;

            void                        reset(unsigned int);

            void                        exec();
            void                        update(double);
            void                        learn();
            void                        generate(json11::Json const&);
            void                        save(json11::Json &);
            void                        load(json11::Json const&);

            void                        apply(UnsupervisedExperience*);
            void                        makeOutputs();

        private:
            SelfOrganizingMapNeuron     *getWinner();
        private:
            std::vector<Excitable*>                     m_inputs;
            std::vector<SelfOrganizingMapNeuron*>       m_map;
            unsigned int                                m_current;
            unsigned int                                m_iteration;
            std::pair<unsigned int, unsigned int>       m_size;
            std::vector<std::vector<double> >           m_outputs;
            double                                      m_step;
            double                                      m_initialRay;
            SelfOrganizingMapNeuron*                    m_winner;
            std::string                                 m_outtype;
        };
    }

}

#endif //SKYNET_SELFORGANIZINGMAP_HPP
