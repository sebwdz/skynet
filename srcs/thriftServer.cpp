//
// Created by sebastien on 10/29/16.
//

#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PlatformThreadFactory.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/TToString.h>

#include <boost/make_shared.hpp>

#include <iostream>

#include "../thrift/gen-cpp/Network.h"

#include "Neuronal/Network.hpp"
#include "Neuronal/LearningSession.hpp"
#include "Neuronal/Loader/Loader.hpp"
#include "Neuronal/Loader/SessionLoader.hpp"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::concurrency;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

class NetworkHandler : public network::NetworkIf {
public:
    NetworkHandler() {}

    void getStruct(shared::SharedStruct& _return, const int32_t key) {
        _return = log[key];
    }

    void            learn(network::Data &ret, network::Data const &in) {
        std::string         err;
        json11::Json        j = json11::Json::parse(in.input, err);
        json11::Json        result;

        Skynet::Neuronal::Network *network = Skynet::Neuronal::Loader::getInstance().getNetwork(j["network"]["settings"]["type"].string_value());
        Skynet::Neuronal::LearningSession *session = Skynet::Neuronal::SessionLoader::getInstance().getSession(j["network"]["settings"]["type"].string_value());
        session->setNetwork(network);

        session->loadExperiences(j["exps"]);
        session->load(j["session"]);
        network->generate(j["network"]["settings"]);
        session->exec();
        network->save(result);
        ret.input = result.dump();
    }

    void        evaluate(network::Data &ret, network::Data const &in) {
        std::string         err;
        json11::Json        j = json11::Json::parse(in.input, err);

        Skynet::Neuronal::Network *network = Skynet::Neuronal::Loader::getInstance().getNetwork(j["network"]["network"]["settings"]["type"].string_value());
        Skynet::Neuronal::LearningSession *session = Skynet::Neuronal::SessionLoader::getInstance().getSession(j["network"]["network"]["settings"]["type"].string_value());
        session->setNetwork(network);

        json11::Json::array res;
        network->load(j["network"]);
        for (unsigned int it = 0; it < j["tests"].array_items().size(); it++) {
            session->loadExperiences(json11::Json::array {j["tests"][it]});
            session->evaluate();
            res.push_back(json11::Json::object {{"res", network->getOutputs()}, {"id", j["tests"][it]["api_id"]}});
        }
        ret.input = json11::Json(res).dump();
    }

protected:
    map<int32_t, shared::SharedStruct> log;
};

/*
  CalculatorIfFactory is code generated.
  CalculatorCloneFactory is useful for getting access to the server side of the
  transport.  It is also useful for making per-connection state.  Without this
  CloneFactory, all connections will end up sharing the same handler instance.
*/
class NetworkCloneFactory : virtual public network::NetworkIfFactory {
public:
    virtual ~NetworkCloneFactory() {}
    virtual network::NetworkIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo)
    {
        boost::shared_ptr<TSocket> sock = boost::dynamic_pointer_cast<TSocket>(connInfo.transport);
        return (new NetworkHandler());
    }
    virtual void releaseHandler( ::shared::SharedServiceIf* handler) {
        delete handler;
    }
};

int main() {
    srand(time(NULL));
    TThreadedServer server(
            boost::make_shared<network::NetworkProcessorFactory>(boost::make_shared<NetworkCloneFactory>()),
            boost::make_shared<TServerSocket>(9090),
            boost::make_shared<TBufferedTransportFactory>(),
            boost::make_shared<TBinaryProtocolFactory>());
    server.run();
}