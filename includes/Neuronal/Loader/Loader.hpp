//
// Created by sebastien on 9/1/16.
//

#ifndef SKYNET_LOADER_HPP
#define SKYNET_LOADER_HPP

#include <json11/json11.hpp>
#include    "Neuronal/Network.hpp"

namespace       Skynet {
    namespace       Neuronal {
        class           Loader {
        public:
            ~Loader() {}

            Network     *load(json11::Json const &);
            Network     *loadPerceptron(json11::Json const &, std::string const&);
            static Loader      &getInstance();

        private:
            Loader();
            std::map<std::string, Network *(Loader::*)(json11::Json const &, std::string const&)>  m_map;
        };
    }
}

#endif //SKYNET_LOADER_HPP
