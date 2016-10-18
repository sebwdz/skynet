//
// Created by sebastien on 8/12/16.
//

#ifndef SKYNET_EXPERIENCE_HPP
#define SKYNET_EXPERIENCE_HPP

#include <vector>
#include "Neuronal/Network.hpp"

namespace   Skynet {

    namespace Neuronal {

        class           Experience {
        public:
            void        setInputs(std::vector<double> const &);
            void        setExpected(std::vector<double> const &);

            virtual void    apply(Network &, bool = false);
            void            calEqm();

            std::vector<double> const       &getErrors() const;
            double                          getEqm() const;

        protected:
            std::vector<double>     m_inputs;
            std::vector<double>     m_expected;
            std::vector<double>     m_errors;
            double m_eqm;
        };
    }
}

#endif //SKYNET_EXPERIENCE_HPP
