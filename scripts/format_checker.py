#! /usr/bin/env python
import argparse
import re

class FormatCheckerError:
    NO_ERROR = 0
    EMPTY_FILE = 1
    BAD_HEADER = 2
    BAD_LINE = 3
    BAD_LABEL = 4
    MISSING_LABEL = 5

class FormatCheckerType:
    SSV = 0
    CSV = 1

ssv_header_pattern = r"^\s*(\d+)\s+(\d+)\s*$"
csv_header_pattern = r"^\s*(\d+)\s*,\s*(\d+)\s*$"
float_pattern = r"(?:[+-]?(?:(?:[0-9]+\.?[0-9]*)|(?:\.[0-9]+))(?:[Ee][+-]?[0-9]+)?)"

# Traverse file object f until a non-empty line is
# reached. If not such line exists, returns the empty string
line_number = 0
def next_non_empty_line(f):
    global line_number
    line_number += 1
    for line in f:
        line = line.strip()
        if line: return line
        line_number += 1
    return ""

def ssv_line_pattern(d):
    return r"^\s*(?:\s*%s\s*){%i}\s*(?:(\d+)\s*)?$" % (float_pattern, d)

def csv_line_pattern(d):
    return r"^(?:\s*%s\s*,){%d}\s*%s\s*(?:\s*,\s*(\d+))?\s*$" % (float_pattern, d-1, float_pattern)

# Check that the file from
# file handler f has the
# proper format.
def check_format (f, format_type):
    # Correct header
    header = next_non_empty_line(f)
    if not header:
        return (FormatCheckerError.EMPTY_FILE, line_number)
    if format_type == FormatCheckerType.CSV:
        match = re.match(csv_header_pattern, header)
    elif format_type == FormatCheckerType.SSV:
        match = re.match(ssv_header_pattern, header)
    if not match:
        return (FormatCheckerError.BAD_HEADER, line_number)
    dimension = int(match.group(1))
    no_classes = int(match.group(2))
    if not (dimension >= 1 and no_classes >= 2):
        return (FormatCheckerError.BAD_HEADER, line_number)
    
    # Correct features
    # First line, see if the set is labeled or not
    any_labeled = False
    any_unlabeled = False

    line = next_non_empty_line(f)
    while line:
        if format_type == FormatCheckerType.SSV:
            match = re.match(ssv_line_pattern(dimension), line)
        elif format_type == FormatCheckerType.CSV:
            match = re.match(csv_line_pattern(dimension), line)
        if not match:
            return (FormatCheckerError.BAD_LINE, line_number)
        assert(len(match.groups()) == 1)
        label = match.groups()[0]
        if label:
            any_labeled = True
            if any_unlabeled:
                return (FormatCheckerError.MISSING_LABEL, line_number)
            label = int(label)
            if label < 0 or label >= no_classes:
                return (FormatCheckerError.BAD_LABEL, line_number)
        else:
            any_unlabeled = True
            if any_labeled:
                return (FormatCheckerError.MISSING_LABEL, line_number)
        line = next_non_empty_line(f)

    return (FormatCheckerError.NO_ERROR, None)
            
f = open("or.csv", 'r')
print(check_format(f, FormatCheckerType.CSV))
f.close()
