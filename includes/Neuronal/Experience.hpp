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

            std::vector<double> const   &getExpected() const;

            virtual void    apply(Network &, bool = false) = 0;
        protected:
            std::vector<double>     m_inputs;
            std::vector<double>     m_expected;
        };
    }
}

#endif //SKYNET_EXPERIENCE_HPP
