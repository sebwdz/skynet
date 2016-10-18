//
// Created by sebastien on 8/12/16.
//

#include            <cstdlib>
#include            "Tools/Utils.hpp"

namespace   Skynet {
    namespace   Tools {
        double          rand() {
            return (((std::rand() % 1000) - 500) / 1000.0);
        }
    }
}