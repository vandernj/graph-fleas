#!/bin/bash
for i in {3..55}; do
    echo -n "$i,"
    ./main $i
done
