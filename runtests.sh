#/bin/bash

## number of runs per concurrency situation => 3 for 8 cpus; 6 for 4;
## 24 for 1
REPL=24

for i in 1 4 8 12 12 24;
do
    ./kickoff.sh $(( $REPL / $i)) $i
done
