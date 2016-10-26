//
// Created by sebastien on 10/23/16.
//

#include    "Manager/Exporter.hpp"

namespace   Skynet {
    namespace   Manager {

        Exporter::Exporter(json11::Json const &pattern, Data::DbObject *db) : AManager(pattern) {
            m_export.setDb(db);
        }

        void Exporter::execute(json11::Json const &vars, json11::Json const& save) {
            m_export.export_data(vars, save, m_pattern);
        }

    }
}