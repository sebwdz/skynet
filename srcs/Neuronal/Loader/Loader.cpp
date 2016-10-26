//
// Created by sebastien on 9/2/16.
//

#include <chanel.hpp>
#include <Neuronal/Network/SelfOrganizingMap.hpp>
#include "Neuronal/Network/MLPerceptron.hpp"
#include "Neuronal/Network/SimplePerceptron.hpp"
#include "Neuronal/Loader/Loader.hpp"

namespace   Skynet {
    namespace       Neuronal {
        Loader::Loader() {
            m_map["mlp"] = &Loader::getPerceptron;
            m_map["sp"] = &Loader::getPerceptron;
            m_map["SelfOrganizingMap"] = &Loader::getSelfOrganizingMap;
        }

        Network* Loader::getNetwork(std::string const &type) {
            Network*    network;
            std::map<std::string, Network *(Loader::*)(std::string const &)>::iterator it;

            if ((it = m_map.find(type)) == m_map.end())
                return (NULL);
            network = (this->*(it->second))(type);
            return (network);
        }

        Network*   Loader::getPerceptron(std::string const& type) {
            Perceptron          *perceptron;

            if (type == "mlp")
                perceptron = new MLPerceptron();
            else
                perceptron = new SimplePerceptron();
            return (perceptron);
        }

        Network* Loader::getSelfOrganizingMap(std::string const &type) {
            SelfOrganizingMap       *map;

            map = new SelfOrganizingMap();
            return (map);
        }

        Loader& Loader::getInstance() {
            static Loader instance;
            return (instance);
        }
    }
}