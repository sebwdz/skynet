//
// Created by sebastien on 8/12/16.
//

#ifndef SKYNET_MLPERCEPTRON_HPP
#define SKYNET_MLPERCEPTRON_HPP

#include        "Perceptron.hpp"

namespace Skynet {
    namespace       Neuronal {
        class           MLPerceptron : public Perceptron {
        public:
            void    setExpected(std::vector<double> const&);
            void    generate(json11::Json const&);
        };
    }
}

#endif //SKYNET_MLPERCEPTRON_HPP
