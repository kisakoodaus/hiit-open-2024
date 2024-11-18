#!/usr/bin/env bash

src="$(git rev-parse --show-toplevel)/tehtävät/"
target="$(git rev-parse --show-toplevel)/printout/gen/"


tasks=(adventure budgetting-bridges conspiracies-everywhere dominoes equilateral-numbers forgotten-measurements gerbils-run hiitism inheritance just-do-it key-cutting light-rail-connections)
names=("Adventure" "Budgetting bridges" "Conspiracies everywhere" "Dominoes" "Equilateral numbers" "Forgotten measurements" "Gerbil's run" "Hiitism" "Inheritance" "Just do it" "Key cutting" "Light rail connections")

mkdir -p "$target"

pushd "$src" > /dev/null
echo "% This file has been automatically generated" > "$target/generated.gen.tex"

for i in "${!tasks[@]}"; do
    task="${tasks[$i]}"
    name="${names[$i]}"
    pushd "$task" > /dev/null
    pandoc -f markdown -t latex --shift-heading-level-by=1 \
        --extract-media="$target/files/$task" \
        "statement.md" -o "$target/tmp.gen.tex"
    popd > /dev/null
    echo "\section{$name}" | cat - "$target/tmp.gen.tex" > "$target/$task.gen.tex"
    echo "\input{gen/$task.gen.tex}" >> "$target/generated.gen.tex"
done

# Compile LaTeX
pushd "$(git rev-parse --show-toplevel)/printout" > /dev/null
latexmk -pdf template.tex -f
popd > /dev/null
popd > /dev/null
