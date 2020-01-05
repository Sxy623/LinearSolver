#! /bin/bash

inputDir="./input/"
outputDir="./output/"
cnt=0
for file in $(ls $inputDir)
do
    let cnt++
    filename="${file%.*}"
    input="$inputDir$file"
    output="$outputDir$filename.out"
    
    n=$(head -n1 $input | awk '{print $1;}')
    m=$(head -n1 $input | awk '{print $2;}')
    echo "Starting Test #$cnt: $filename, $n x $m"
    
    start=$SECONDS
    ./LinearSolver.exe < $input
    duration=$(( SECONDS - start ))
    echo "Test #$cnt: time elapsed = $duration s"
    echo
done