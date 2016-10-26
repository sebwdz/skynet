//
// Created by sebastien on 8/12/16.
//

#ifndef SKYNET_PERCEPTRON_HPP
#define SKYNET_PERCEPTRON_HPP

#include <vector>
#include <json11/json11.hpp>
#include "Neuronal/Network/PerceptronLayer.hpp"
#include "SupervisedNetwork.hpp"

namespace Skynet {
    namespace   Neuronal {
        class           Perceptron : public SupervisedNetwork {
        public:
            Perceptron();

            virtual void        exec();
            virtual void        learn();
            virtual void        update(double = 0);
            virtual void        generate(json11::Json const&);
            virtual void        save(json11::Json&) {}
            virtual void        load(json11::Json&) {}
            virtual void        reset(unsigned int) {}

            virtual void        setInputs(std::vector<double> const&);

            void                                addLayer(PerceptronLayer*);

            PerceptronLayer                     *getLayer(unsigned int) const;
            unsigned int                        getLayerNb() const;

            double                              getCoef() const;

        protected:
            std::vector<PerceptronLayer*>       m_layers;
            double                              m_prevEqm;
            double                              m_coef;
        };
    }
}

#endif //SKYNET_PERCEPTRON_HPP
