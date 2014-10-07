#!/bin/bash

times=10
echo "Execute the sort program for ${times} times."

for((i=0; i<$times; i++)); do
	echo "${i} execution:"
	./LxAlgorithms

done
