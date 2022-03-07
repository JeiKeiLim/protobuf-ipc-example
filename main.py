import os
import sys
sys.path.append(os.path.join("protobuf", "python"))

import grpc
import argparse

from protobuf.python.msg_pb2 import Person
from protobuf.python.msg_pb2_grpc import WhoIsItStub

def get_args() -> argparse.Namespace:
    """Get argument parser."""
    parser = argparse.ArgumentParser(
        formatter_class=argparse.ArgumentDefaultsHelpFormatter
    )
    parser.add_argument("--name", type=str, default="Jongkuk Lim", help="Request name")

    return parser.parse_args()

if __name__ == "__main__":
    args = get_args()

    with grpc.insecure_channel('localhost:50051') as channel:
        stub = WhoIsItStub(channel)
        response = stub.SendMe(Person(name=args.name))

    print(response)
