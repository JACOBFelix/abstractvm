#!/usr/bin/env python3

import sys

if len(sys.argv) < 2:
    print("Usage : " + sys.argv[0] + " <string>...")
    exit(1)

for i, string in enumerate(sys.argv):
    if i == 0:
        continue
    string += '\n';
    for c in string:
        print("push int8(" + str(ord(c)) + ")")
        print("print")
        print("pop")

print("exit");
print(";;");
exit(0)
