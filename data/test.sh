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
    status=$(head -n1 $sol | sed -e 's/\s.*$//')
    
    echo "Test #$cnt: $filename, $n x $m"
    if [[ "$status" == "1" ]]
    then
        echo "opt_sol = $opt"
    elif [[ "$status" == "0" ]]
    then
        echo "Unbounded"
    elif [[ "$status" == "-1" ]]
    then
        echo "Infeasible"
    fi
    
    start=$SECONDS
    ./LinearSolver.exe < $input
    duration=$(( SECONDS - start ))
    echo "Test #$cnt finished in $duration s"
    echo
done