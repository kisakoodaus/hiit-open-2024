#!/usr/bin/env bash
set -e
mkdir -p tests
i=1
while IFS= read -r test
do

    if [[ $test = \#* ]]; then
        continue
    fi
    test=${test%\#*}

    echo "$test" > tests/$i.gen.tmp
    if ! cmp -s tests/$i.gen.tmp tests/$i.gen; then
        cp tests/$i.gen.tmp tests/$i.gen
    fi
    rm tests/$i.gen.tmp
    echo $i
    ((i++))
done < "$1"
