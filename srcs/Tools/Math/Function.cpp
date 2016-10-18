//
// Created by sebastien on 8/12/16.
//

#include            <cmath>
#include            <iostream>

namespace               Skynet {
    namespace               Tools {
        namespace               Functions {
            double                  sigmoide(double input, double coef) {
                return (1 / (1 + std::exp(-input * coef)));
            }

            double                  sigmoidedev(double input, double coef) {
                double              tmp;

                tmp = sigmoide(input, coef);
                return (tmp * (1 - tmp));
            }

            double                  tanh(double input, double) {
                return (std::tanh(input));
            }

            double                  tanhdev(double input, double) {
                return (1 - (std::pow(std::tanh(input), 2)));
            }

            double              getDistance(std::pair<double, double> const& p1, std::pair<double, double> const& p2)
            {
                double          dist;

                dist = std::pow(p1.first - p2.first, 2);
                dist += std::pow(p1.second - p2.second, 2);
                return (sqrt(dist));
            }

            double              sigma(double ray, double current, double it) {
                double          l = it / std::log(ray);

                return (ray * std::exp(- 1 * current / l));
            }

            double              gauss(double ray, double rmax, double current, double it) {
                double          r = sigma(rmax, current, it);

                r = (ray * ray) / (r * r * 2);
                return (std::exp(-1 * r));
            }
        }
    }
}