//
// Created by sebastien on 8/12/16.
//

#ifndef SKYNET_FUNCTION_HPP
#define SKYNET_FUNCTION_HPP

#include        <cmath>
#include        <utility>

namespace       Skynet {
    namespace       Tools {
        namespace       Functions {
            double              sigmoide(double, double);
            double              sigmoidedev(double, double);

            double              tanh(double, double);
            double              tanhdev(double, double);

            double              getDistance(std::pair<double, double> const&, std::pair<double, double> const&);

            double              sigma(double, double, double);
            double              gauss(double, double, double, double);
        }
    }
}

#endif //SKYNET_FUNCTION_HPP
