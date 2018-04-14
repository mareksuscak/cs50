#!/usr/bin/env python3

import argparse
import re
import sys

from helpers import lines, sentences, substrings


def main():

    # Parse command-line arguments
    parser = argparse.ArgumentParser()
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument("--lines", action="store_true", help="compare lines")
    group.add_argument("--sentences", action="store_true", help="compare sentences")
    group.add_argument("--substrings", metavar="N", type=positive,
                       help="compare substrings of length N")
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
    if args["lines"]:
        matches = lines(file1, file2)
    elif args["sentences"]:
        matches = sentences(file1, file2)
    elif args["substrings"]:
        matches = substrings(file1, file2, args["substrings"])

    # Output matches, sorted from longest to shortest, with line endings escaped
    for match in sorted(matches, key=len, reverse=True):
        print(match.replace("\n", "\\n").replace("\r", "\\r"))


def positive(string):
    """Convert string to a positive integer."""
    value = int(string)
    if value <= 0:
        raise argparse.ArgumentTypeError("invalid length")
    return value


if __name__ == "__main__":
    main()
