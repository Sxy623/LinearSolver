#! /bin/bash
if [ "$#" -ne 1 ]; then
    echo "Usage: bash dual_test.sh [PATH_TO_DUAL_SOLVER]"
    exit
fi
echo "$1"
inputDir="./input-dual/"
outputDir="./output-dual/"
solDir="./solution-dual/"
log="log.txt"
cnt=0
printf "%-10s%-10s%-10s%-20s%-20s%-10s%-10s\n" "Name" '#Vars' '#Cstrs' 'Optimal' 'Result' 'Error' 'Time' > $log

for file in $(ls $inputDir)
do
    let cnt++
    filename="${file%.*}"
    input="$inputDir$file"
    output="$outputDir$filename.out"
    sol="$solDir$filename.out"
    
    n=$(head -n1 $input | awk '{print $1;}' | tr -d "\r")
    m=$(head -n1 $input | awk '{print $2;}' | tr -d "\r")
    opt=$(sed '2q;d' $sol | awk '{print $1;}' | tr -d "\r")
    status=$(head -n1 $sol | sed -e 's/\s.*$//')
    
    echo "Test #$cnt: $filename, $n x $m"
    if [[ "$status" == "1" ]]
    then
        echo "opt_sol = $opt"
    elif [[ "$status" == "0" ]]
    then
        echo "Unbounded"
        opt="Unbounded"
    elif [[ "$status" == "-1" ]]
    then
        echo "Infeasible"
        opt="Infeasible"
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
    optsol=$($1 < $input | sed '2q;d' | tr -d "\r")
    if [[ "$status" == "1" ]]
    then
        error=$(echo "$optsol $opt" | awk '{printf "%.6f\n", ($2-$1)/$2}')
    else
        error="NaN"
    fi
    echo "Test #$cnt finished in $duration ms"
    echo "------------"
    printf "%-10s%-10s%-10s%-20s%-20s%-10s%-10s\n" "$filename" "$n" "$m" "$opt" "$optsol" "$error" "$duration" >> $log
done