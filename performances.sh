#!/usr/bin/bash

make

#philosophes
PHILOSOPHES_CSV=philosophes.csv
PHILOSOPHES_EXEC=./philosophes
echo "Threads,try,time" > $PHILOSOPHES_CSV

for i in 2 4 8 16 32
do
    for j in {1..5}
    do
        echo "nbThreads : $i, try : $j"
        TIME_RES=$(/usr/bin/time -f "%e" $PHILOSOPHES_EXEC $i 2>&1)
        echo "$i,$j,$TIME_RES" >> $PHILOSOPHES_CSV
    done
done

#consumer


PROD_CSV=producer.csv
PROD_EXEC=./producer   

echo "Threads,Try,Time" > "$PROD_CSV"

for i in 2 4 8 16 32
do
    for j in {1..5}
    do
        echo "nbThreads : $i, try : $j"
        TIME_RES=$(/usr/bin/time -f "%e" $PROD_EXEC "$i" 2>&1)
        echo "$i,$j,$TIME_RES" >> "$PROD_CSV"
    done
done



#rider writer





make clean

exit 