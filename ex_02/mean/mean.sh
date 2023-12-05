make
for i in "" "_2" "_3" "_4" "_8"; do
    ./mean ../vec_sum/scripts/result"$i".csv ../vec_sum/scripts/result"$i"_mean.csv 0
done
for i in "" "_2" "_4"; do
    ./mean ../jacobi/scripts/result"$i".csv ../jacobi/scripts/result"$i"_mean.csv 1
done
make clean
