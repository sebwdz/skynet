//
// Created by sebastien on 10/13/16.
//

#ifndef SKYNET_EXPORTER_HPP
#define SKYNET_EXPORTER_HPP

#include    "json11/json11.hpp"
#include    "Data/DbObject.hpp"

namespace Skynet {
    namespace Data {
        class           Exporter {
        public:
            void                setDb(DbObject*);
            json11::Json const  &getValue(json11::Json const&, json11::Json const&);
            void                export_data(json11::Json const&, json11::Json const&);

        private:
            json11::Json        m_tmp;
            DbObject            *m_db;
        };
    }
}

#endif //SKYNET_EXPORTER_HPP
