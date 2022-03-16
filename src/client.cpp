/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2021 J.Marple
/// @brief gRPC client side source code.

#include <grpcpp/grpcpp.h>

#include <iostream>
#include <memory>

#include "msg.grpc.pb.h"  // NOLINT

using protobuf_example::Person;
using protobuf_example::PersonRequest;
using protobuf_example::WhoIsIt;

/// Run client side gRPC example
///
/// @param argc: Number of arguments.
/// @param argv: Arguments
///
/// @return: 0
int main(int argc, char** argv) {
  std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(
      "localhost:50051", grpc::InsecureChannelCredentials());
  std::unique_ptr<WhoIsIt::Stub> stub = WhoIsIt::NewStub(channel);

  PersonRequest person_req;

  if (argc > 1) {
    person_req.set_name(argv[1]);
  } else {
    person_req.set_name("Jongkuk");
  }

  Person person;

  grpc::ClientContext context;
  grpc::Status status = stub->SendMe(&context, person_req, &person);

  if (status.ok()) {
    std::cout << "id: " << person.id() << std::endl;
    std::cout << "name: " << person.name() << std::endl;
    std::cout << "email: " << person.email() << std::endl;
  } else {
    std::cout << "gRPC has failed!" << std::endl;
  }

  return 0;
}
