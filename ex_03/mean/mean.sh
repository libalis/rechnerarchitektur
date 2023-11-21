make
for i in "" "_2" "_3" "_4" "_8"; do
    ./mean ../ex_00/scripts/result"$i".csv ../ex_00/scripts/result"$i"_mean.csv 0
done
for i in "" "_2" "_4"; do
    ./mean ../ex_01/scripts/result"$i".csv ../ex_01/scripts/result"$i"_mean.csv 1
done
make clean
