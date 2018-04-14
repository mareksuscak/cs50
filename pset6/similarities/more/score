#!/usr/bin/env python3

import sys

from argparse import ArgumentParser
from helpers import distances


def main():

    # Parse command-line arguments
    parser = ArgumentParser()
    parser.add_argument("FILE1", help="file to compare")
    parser.add_argument("FILE2", help="file to compare")
    args = vars(parser.parse_args())

    # Read files
    try:
        with open(args["FILE1"], "r") as file:
            file1 = file.read()
    except IOError:
        sys.exit(f"Could not read {args['FILE1']}")
    try:
        with open(args["FILE2"], "r") as file:
            file2 = file.read()
    except IOError:
        sys.exit(f"Could not read {args['FILE2']}")

    # Compare files
    d = distances(file1, file2)
    print(d[len(file1)][len(file2)][0])


if __name__ == "__main__":
    main()
