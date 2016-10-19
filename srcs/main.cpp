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

    dbObject.connect("user=sebastien " "host=127.0.0.1 " "password=passpass " "port=5432 " "dbname=pocdata ");
    mainManager = new Skynet::Manager::MainManager(data, &dbObject);
    mainManager->execute(json11::Json());
    exit(0);
}

json11::Json        makeOutMap(std::vector<Skynet::Data::Extract::Values*> const& inputs,
                               std::vector<Skynet::Data::Extract::Values*> const& outputs,
                               json11::Json const &patern, Skynet::Neuronal::SelfOrganizingMap &map) {
    json11::Json::array result;

    if (patern["settings"]["outputs"][0]["type_use"].string_value() != "accu") {
        result.resize((unsigned int) patern["network"]["settings"]["outputs"][0].int_value() *
                      patern["network"]["settings"]["outputs"][1].int_value(),
                      json11::Json::array(patern["settings"]["outputs"].array_items().size(),
                                          json11::Json::array {0, 0}));
    } else {
        result.resize((unsigned int) patern["network"]["settings"]["outputs"][0].int_value() *
                      patern["network"]["settings"]["outputs"][1].int_value(),
                      json11::Json::array(patern["settings"]["outputs"].array_items().size(),
                                          json11::Json::array ()));

    }
    for (unsigned int it = 0; it < inputs.size(); it++) {
        map.setInputs(inputs[it]->_values);
        map.exec();
        json11::Json::array     tmp = result[map.getOutputs()[0] + (map.getOutputs()[1] * patern["network"]["settings"]["outputs"][0].int_value())].array_items();
        for (unsigned int x = 0; x < tmp.size(); x++) {
            if (patern["settings"]["outputs"][0]["type_use"].string_value() != "accu")
                tmp[x] = json11::Json::array {tmp[x][0].number_value() + outputs[it]->_values[x],
                                              tmp[x][1].int_value() + 1};
            else {
                json11::Json::array tmparr(tmp[x].array_items());
                tmparr.push_back(outputs[it]->_values);
                tmp[x] = tmparr;
            }
        }
        result[map.getOutputs()[0] + (map.getOutputs()[1] * patern["network"]["settings"]["outputs"][0].int_value())] = tmp;
    }
    return (result);
}

void                test(char *filename, char *req) {
    std::ifstream                                   file(filename);
    std::string                                     content;
    std::string                                     err;
    json11::Json                                    data;

    Skynet::Data::DbObject      dbObject;
    Skynet::Data::DbReader      reader;
    Skynet::Data::Extract       extract;
    Skynet::Data::Exporter      exporter;



    exporter.setDb(&dbObject);
    reader.setDb(&dbObject);

    srand(time(NULL));

    dbObject.connect("user=sebastien " "host=127.0.0.1 " "password=passpass " "port=5432 " "dbname=pocdata ");

    dbObject.execute(req);
    json11::Json    all = dbObject.getResult();


    content = std::string((std::istreambuf_iterator<char>(file)),
                          std::istreambuf_iterator<char>());

    data = json11::Json::parse(content, err);

    for (unsigned int x = 0; x < all.array_items().size(); x++) {

        dbObject.execute("DELETE FROM networks WHERE type = '" + data["export"][0]["fields"]["type"].string_value() + "' AND fk_id = " + all[x].object_items().begin()->second.string_value());

        Skynet::Neuronal::UnsupervisedSession   session;
        Skynet::Neuronal::SelfOrganizingMap     map;

        session.setNetwork(&map);
        std::cout << all[x].object_items().begin()->first << " => " << all[x].object_items().begin()->second.string_value() << std::endl;
        json11::Json::object var = json11::Json::object {{all[x].object_items().begin()->first, all[x].object_items().begin()->second.string_value()}};
        reader.setVariables(var);
        reader.execute(data["request"]);

        json11::Json const &j = dbObject.getResult();

        extract.extract(j, data["settings"]["inputs"]);
        std::vector<Skynet::Data::Extract::Values *> inputs = extract.getValues();

        std::cout << inputs.size() << std::endl;
        extract.extract(j, data["settings"]["outputs"]);
        std::vector<Skynet::Data::Extract::Values *> outputs = extract.getValues();

        map.generate(data["network"]["settings"]);

        session.load(data["network"]["session"]);
        session.setInputs(inputs);

        session.exec();

        json11::Json nsave;
        map.save(nsave);

        json11::Json outmap = makeOutMap(inputs, outputs, data, map);

        json11::Json::object vars{{"network",     nsave},
                                  {"outputs",     outmap},
                                  {"fk_id",   all[x].object_items().begin()->second.string_value()},
                                  {"req.id",      1}};
        exporter.export_data(vars, data["export"][0]);

    }
    dbObject.commit();
}

int                 main(int, char** av) {
    managertest();
    if (std::string(av[1]) == "generate") {
        test(av[2], av[3]);
    } else if (std::string(av[1]) == "exploit") {

    } else if (std::string(av[1]) == "evaluate") {

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
            std::vector<Skynet::Data::Extract::Values *> inputs = extract.getValues();

            extract.extract(j, data["settings"]["outputs"]);
            std::vector<Skynet::Data::Extract::Values *> outputs = extract.getValues();

            for (unsigned int it = 0; it < inputs.size(); it++) {
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
            }
        }
        std::ofstream out("result.json");
        out << json11::Json(result).dump() << std::endl;
    }
    return (0);
}