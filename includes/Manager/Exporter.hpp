//
// Created by sebastien on 10/23/16.
//

#ifndef SKYNET_EXPORTER_HPP
#define SKYNET_EXPORTER_HPP

#include "Data/Exporter.hpp"
#include "AManager.hpp"

namespace   Skynet {
    namespace       Manager {
        class           Exporter : public AManager {
        public:
            Exporter(json11::Json const&, Skynet::Data::DbObject*);

            void            execute(json11::Json const&, json11::Json const&);
        private:
            Data::Exporter  m_export;
        };
    }
}

#endif //SKYNET_EXPORTER_HPP
