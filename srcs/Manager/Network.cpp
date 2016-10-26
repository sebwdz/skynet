//
// Created by sebastien on 10/20/16.
//

#include <iostream>
#include "Manager/Network.hpp"
#include "Neuronal/Loader/Loader.hpp"
#include "Neuronal/Loader/SessionLoader.hpp"

namespace   Skynet {
    namespace   Manager {
        Network::Network(json11::Json const &pattern) : AManager(pattern) {
        }

        void Network::execute(json11::Json const &vars, json11::Json const&) {
            m_network = Neuronal::Loader::getInstance().getNetwork(m_pattern["network"]["settings"]["type"].string_value());
            m_session = Neuronal::SessionLoader::getInstance().getSession(m_pattern["network"]["settings"]["type"].string_value());
            m_session->setNetwork(m_network);

            m_results = json11::Json();
            m_session->loadExperiences(vars);
            if (m_pattern["session_type"].string_value() == "learn") {
                m_session->load(m_pattern["network"]["session"]);
                m_network->generate(m_pattern["network"]["settings"]);
                m_session->exec();
                m_network->save(m_results);
                m_results = json11::Json::object {{"network", m_results}};
            } else {
                //m_network->load();
            }
        }
    }
}