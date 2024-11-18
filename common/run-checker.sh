#!/usr/bin/env bash
set -e
echo "$1 < $2"
checker_output="$($1 < $2)"
code=$?
{ read -r result; read -r groups; } <<< "$checker_output" || true
if [ $code -ne 0 ]; then
    echo Checker crashed with return code $code
    exit 2
fi
if [ "$result" != "1" ]; then
    echo Checker returned $result
    exit 3
fi
if [ -z "$groups" ]; then
    echo Checker ok, no groups
else
    echo -n "Checker ok with groups "
    python3 -c 'print(*(
        i for i, bit in enumerate(bin(int(input()))[:1:-1])
        if bit == "1"
    ))' <<< "$groups"
fi
