//
// Created by sebastien on 8/12/16.
//

#ifndef SKYNET_SIMPLEP_ERCEPTRON_HPP
#define SKYNET_SIMPLEPERCEPTRON_HPP

#include    "Perceptron.hpp"

namespace   Skynet {
    namespace   Neuronal {
        class       SimplePerceptron : public Perceptron {
        public:
            void    setExpected(std::vector<double> const&);
            void    generate(json11::Json const&);
        private:
        };
    }
}

#endif //SKYNET_SIMPLEPERCEPTRON_HPP
