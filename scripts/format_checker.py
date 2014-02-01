#! /usr/bin/env python
import argparse

parser = argparse.ArgumentParser()
#parser.add_argument("to_square", help="number to square", type=int)
parser.add_argument("--verbose", help="verbosity etc", action="store_true")
args = parser.parse_args()

if __name__ == "__main__":
    print(args.verbose)
