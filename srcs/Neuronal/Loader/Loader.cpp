//
// Created by sebastien on 9/2/16.
//

#include <chanel.hpp>
#include "Neuronal/Network/MLPerceptron.hpp"
#include "Neuronal/Network/SimplePerceptron.hpp"
#include "Neuronal/Loader/Loader.hpp"

namespace   Skynet {
    namespace       Neuronal {
        Loader::Loader() {
            m_map["mlp"] = &Loader::loadPerceptron;
            m_map["sp"] = &Loader::loadPerceptron;
        }

        Network* Loader::load(json11::Json const &json) {
            Network*    network;
            std::map<std::string, Network *(Loader::*)(json11::Json const &, std::string const &)>::iterator it;
            std::string type = json["settings"]["type"].string_value();

            if ((it = m_map.find(type)) == m_map.end())
                return (NULL);
            network = (this->*(it->second))(json["settings"], type);
            return (network);
        }

        Network*   Loader::loadPerceptron(json11::Json const &json, std::string const& type) {
            Perceptron          *perceptron;

            if (type == "mlp")
                perceptron = new MLPerceptron();
            else
                perceptron = new SimplePerceptron();
            perceptron->generate(json);
            return (perceptron);
        }

        Loader& Loader::getInstance() {
            static Loader instance;
            return (instance);
        }
    }
}