//
// Created by sebastien on 9/1/16.
//

#ifndef SKYNET_LOADER_HPP
#define SKYNET_LOADER_HPP

#include    <json11/json11.hpp>
#include    "Neuronal/Network.hpp"

namespace       Skynet {
    namespace       Neuronal {
        class           Loader {
        public:
            ~Loader() {}

            Network             *getNetwork(std::string const &);
            Network             *getPerceptron(std::string const&);
            Network             *getSelfOrganizingMap(std::string const&);
            static Loader       &getInstance();

        private:
            Loader();
            std::map<std::string, Network *(Loader::*)(std::string const&)>  m_map;
        };
    }
}

#endif //SKYNET_LOADER_HPP
