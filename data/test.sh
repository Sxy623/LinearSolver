#! /bin/bash
if [ "$#" -ne 1 ]; then
    echo "Usage: bash test.sh [PATH_TO_SOLVER]"
    exit
fi
echo "$1"
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
    opt=$(sed '2q;d' $sol | awk '{print $1;}' | tr -d "\r")
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
    
    start=$(date +%s%3N | cut -b1-13)
    $1 < $input
    # if [[ "$status" == "1" ]]
    # then
    #     res=$($1 < $input | sed '2q;d' | sed -e 's/\s.*$//' | tr -d "\r")
    #     echo "res = $res"
    #     error=$(echo "scale=4; ($res-$opt)/$opt" | bc)
    #     echo "error = $error"
    # fi
    end=$(date +%s%3N | cut -b1-13)
    duration=$(( end - start ))
    echo "Test #$cnt finished in $duration ms"
    echo "------------"
done