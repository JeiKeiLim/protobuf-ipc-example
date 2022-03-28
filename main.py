import os
import sys
sys.path.append(os.path.join("protobuf", "python"))
import time

from concurrent import futures

import grpc
import argparse

from protobuf.python.msg_pb2 import Person, PersonRequest
from protobuf.python.msg_pb2_grpc import WhoIsItStub, WhoIsItServicer
from protobuf.python import msg_pb2_grpc

class WhoIsItServer(WhoIsItServicer):
    def __init__(self) -> None:
        self.id = 0

    def SendMe(self, person_req: PersonRequest, context) -> Person:
        person = Person(id=self.id,
                        name=person_req.name,
                        email="lim.jeikei@gmail.com"
                        )
        print("[Python] Request from another process!")
        print(f"  >> Request name: {person_req.name}")
        print(f"  >> Response ID: {self.id}")
        self.id += 1
        return person

def get_args() -> argparse.Namespace:
    """Get argument parser."""
    parser = argparse.ArgumentParser(
        formatter_class=argparse.ArgumentDefaultsHelpFormatter
    )
    parser.add_argument("--name", type=str, default="Jongkuk Lim", help="Request name")
    parser.add_argument("--server", default=False, action="store_true", help="Run as RPC server.")

    return parser.parse_args()

if __name__ == "__main__":
    args = get_args()

    if args.server:  # Run as server (Python -> C++)
        grpc_server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
        msg_pb2_grpc.add_WhoIsItServicer_to_server(
            WhoIsItServer(),
            grpc_server
        )
        grpc_server.add_insecure_port("[::]:50051")
        grpc_server.start()
        print("Server has started")

        grpc_server.wait_for_termination()
    else:  # Run as client (C++ -> Python)
        with grpc.insecure_channel('localhost:50051') as channel:
            stub = WhoIsItStub(channel)
            response = stub.SendMe(Person(name=args.name))

        print(response)
