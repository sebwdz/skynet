//
// Created by sebastien on 10/13/16.
//

#ifndef SKYNET_EXPORTER_DATA_HPP
#define SKYNET_EXPORTER_DATA_HPP

#include    "json11/json11.hpp"
#include    "Data/DbObject.hpp"

namespace Skynet {
    namespace Data {
        class           Exporter {
        public:
            void                setDb(DbObject*);
            json11::Json        getValue(json11::Json const&, json11::Json const&, json11::Json const&);
            //void                remove(json11::Json const &vars, json11::Json const& save, json11::Json const &pattern);
            void                export_data(json11::Json const&, json11::Json const&, json11::Json const&);

        private:
            DbObject            *m_db;
        };
    }
}

#endif //SKYNET_EXPORTER_HPP
