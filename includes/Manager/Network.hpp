//
// Created by sebastien on 10/20/16.
//

#ifndef SKYNET_NETWORK_H
#define SKYNET_NETWORK_H

#include "Neuronal/LearningSession.hpp"
#include "AManager.hpp"

namespace Skynet {
    namespace   Manager {
        class           Network : public AManager {
        public:
            Network(json11::Json const&);

            void        execute(json11::Json const&, json11::Json const&);
        private:
            Neuronal::Network           *m_network;
            Neuronal::LearningSession   *m_session;
        };
    }
}

#endif //SKYNET_NETWORK_H
