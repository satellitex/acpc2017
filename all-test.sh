#!/bin/sh
files="./*"
for filepath in $files; do
    if [ -d $filepath ] ; then
        if [ -e $filepath/PROBLEM ]; then
            echo $filepath/PROBLEM
            rime test $filepath
        fi
    fi
done