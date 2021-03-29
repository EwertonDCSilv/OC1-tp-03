import difflib
import sys

with open('./test/output/01.out', 'r') as hosts0:
    with open('result.txt', 'r') as hosts1:
        diff = difflib.unified_diff(
            hosts0.readlines(),
            hosts1.readlines(),
            fromfile='01.out',
            tofile='result.txt',
        )
        for line in diff:
            sys.stdout.write(line)