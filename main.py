import os
import sys
sys.path.append(os.path.join("protobuf", "python"))

import grpc

from protobuf.python.msg_pb2 import Person
from protobuf.python.msg_pb2_grpc import WhoIsItStub

if __name__ == "__main__":
    with grpc.insecure_channel('localhost:50051') as channel:
        stub = WhoIsItStub(channel)
        response = stub.SendMe(Person(name="Jongkuk Lim"))

    print(response)
