#! /bin/bash

inputDir="./input/"
outputDir="./output/"
solDir="./solution/"
cnt=0
for file in $(ls $inputDir)
do
    let cnt++
    filename="${file%.*}"
    input="$inputDir$file"
    output="$outputDir$filename.out"
    sol="$solDir$filename.out"
    
    n=$(head -n1 $input | awk '{print $1;}')
    m=$(head -n1 $input | awk '{print $2;}')
    opt=$(sed '2q;d' $sol | awk '{print $1;}')
    echo "Test #$cnt: $filename, $n x $m"
    echo "opt_sol = $opt"
    
    start=$SECONDS
    ./LinearSolver.exe < $input
    duration=$(( SECONDS - start ))
    echo "Test #$cnt finished in $duration s"
    echo
done