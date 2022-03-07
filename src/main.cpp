/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2021 J.Marple
/// @brief Main source code.

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include <iostream>
#include <memory>
#include <string>

#include "msg.grpc.pb.h"  // NOLINT

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using protobuf_example::Person;
using protobuf_example::PersonRequest;
using protobuf_example::WhoIsIt;

/// Person Service implementation.
class PersonServiceImpl final : public WhoIsIt::Service {
  /// Receieve PersonRequest message via IPC.
  ///
  /// @param context: Server context.
  /// @param request: request message.
  /// @param person: response message.
  ///
  /// @return: Status
  // cppcheck-suppress unusedFunction
  Status SendMe(ServerContext* context, const PersonRequest* request,
                Person* person) override {
    std::cout << "Request from another process!" << std::endl;
    std::cout << "  >> Request name: " << request->name() << std::endl;
    std::cout << "  >>  Response ID: " << this->_id << std::endl;
    std::cout << std::endl;

    person->set_name(request->name());
    person->set_email("lim.jeikei@gmail.com");
    person->set_id(this->_id++);

    return Status::OK;
  }

 private:
  /// Message id (Incremental order)
  int _id = 0;
};

/// Run template program
///
/// @param argc: Number of arguments.
/// @param argv: Arguments
///
/// @return: 0
int main(int argc, char** argv) {
  std::string server_address("0.0.0.0:50051");
  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();

  PersonServiceImpl service;

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  server->Wait();

  return 0;
}
