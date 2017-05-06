#/bin/bash

REPL=$1
CPU=$2

EXE=./test/unit/math/rev/mat/functor/integrate_ode_perf_test

run_case() {
    echo Running case $2 out of $CPU, replication $1 ...
    $EXE > run_$1_$2_$CPU.log 2>&1
}

for i in `seq 1 $REPL`;
do
    for j in `seq 1 $CPU`;
    do
        run_case $i $j &
    done
    sleep 1
    echo "Waiting until childs finish from replication $i of $REPL..."
    wait
done


echo "Done!"

#watch tail -n 4 run_*.log
