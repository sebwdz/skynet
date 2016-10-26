//
// Created by sebastien on 8/12/16.
//

#include            <iostream>
#include            <fstream>
#include            <cmath>
#include            "Neuronal/LearningSession/UnsupervisedSession.hpp"
#include            "Neuronal/Network/SelfOrganizingMap.hpp"
#include            "Data/DbObject.hpp"
#include            "Data/DbReader.hpp"
#include            "Data/Exporter.hpp"
#include            "Manager/MainManager.hpp"

void                managertest() {
    Skynet::Manager::MainManager        *mainManager;
    std::ifstream                                   file("exp/manmovies");
    std::string                                     content;
    std::string                                     err;
    json11::Json                                    data;
    Skynet::Data::DbObject                          dbObject;

    content = std::string((std::istreambuf_iterator<char>(file)),
                          std::istreambuf_iterator<char>());

    data = json11::Json::parse(content, err);

    srand(time(NULL));

    dbObject.connect("user=sebastien " "host=127.0.0.1 " "password=passpass " "port=5432 " "dbname=pocdata ");
    mainManager = new Skynet::Manager::MainManager(data, &dbObject);
    mainManager->execute(json11::Json(), json11::Json());
    std::cout << mainManager->getResults().dump() << std::endl;
    dbObject.commit();
    exit(0);
}

int                 main(int, char** av) {
    managertest();
    if (std::string(av[1]) == "evaluate") {

        std::ifstream                                   file(av[2]);
        std::string                                     content;
        std::string                                     err;
        json11::Json                                    data;

        content = std::string((std::istreambuf_iterator<char>(file)),
                              std::istreambuf_iterator<char>());

        data = json11::Json::parse(content, err);

        file.close();
        file.open("result.json");
        json11::Json::object    result;
        if (file.is_open()) {
            content = std::string((std::istreambuf_iterator<char>(file)),
                                  std::istreambuf_iterator<char>());
            result = json11::Json::parse(content, err).object_items();
        }

        std::cout << err << std::endl;
        Skynet::Data::DbObject      dbObject;
        Skynet::Data::DbReader      reader;
        Skynet::Data::Extract       extract;

        dbObject.connect("user=sebastien " "host=127.0.0.1 " "password=passpass " "port=5432 " "dbname=pocdata ");
        dbObject.execute(av[3]);

        reader.setDb(&dbObject);

        json11::Json        all = dbObject.getResult();

        double      goodt = 0, errort = 0, showt = 0, tno = 0, allt = 0, ss = 0;
        for (unsigned int x = 0; x < all.array_items().size(); x++) {

            json11::Json exp = data["export"];
            dbObject.execute("SELECT * FROM networks WHERE type = '" + exp[0]["fields"]["type"].string_value() + "' AND fk_id = " + all[x].object_items().begin()->second.string_value());

            json11::Json    dataNetwork = dbObject.getResult();
            Skynet::Neuronal::SelfOrganizingMap     map;

            json11::Json network = json11::Json::parse(dataNetwork[0]["map"].string_value(), err);
            map.load(network["network"]);

            json11::Json::object var = json11::Json::object {{"fk_id", all[x]["fk_id"].string_value()}};
            reader.setVariables(var);
            reader.execute(data["request"]);

            json11::Json j = dbObject.getResult();

            extract.extract(j, data["settings"]["inputs"]);
            //std::vector<Skynet::Data::Extract::Values *> inputs = extract.getResult();

            extract.extract(j, data["settings"]["outputs"]);
            //std::vector<Skynet::Data::Extract::Values *> outputs = extract.getResult();

            /*for (unsigned int it = 0; it < inputs.size(); it++) {
                double      rate = 0;
                std::cout << it << " " << inputs.size() << std::endl;
                std::string id = j[it]["opinions.id"].string_value();
                map.setInputs(inputs[it]->_values);
                map.exec();
                unsigned int x = map.getOutputs()[0] + map.getOutputs()[1] * network["network"]["outputs"][0].int_value();
                json11::Json const &tmp = network["outputs"][x];
                if (tmp[0][1].number_value())
                    rate = tmp[0][0].int_value() / tmp[0][1].number_value();
                json11::Json::array arr = result[id].array_items();
                arr.push_back(json11::Json::array {outputs[it]->_values[0], rate});
                result[id] = arr;
            }*/
        }
        std::ofstream out("result.json");
        out << json11::Json(result).dump() << std::endl;
    }
    return (0);
}