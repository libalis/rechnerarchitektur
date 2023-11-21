#!/bin/bash -l
while true; do
    clear
    echo $(printf %.2f $(echo "$(cat $1 | wc -l)/641*100" | bc -l))%
    sleep 1
done
