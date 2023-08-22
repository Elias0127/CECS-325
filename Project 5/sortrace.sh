echo "My machine has this many processors" | tee -a sortrace.log
sysctl -n hw.ncpu | tee -a sortrace.log
echo "Generating 1000000 random numbers" | tee -a sortrace.log
sleep 1
./generate 1000000 100000 999999
sleep 1
echo "Starting system sort" | tee -a sortrace.log
sleep 1
(time sort numbers.dat > systemsort.out) 2>&1 | tee -a sortrace.log
sleep 1
echo "Starting my sort" | tee -a sortrace.log
sleep 1
(time ./mysort numbers.dat > mysort.out) 2>&1 | tee -a sortrace.log
sleep 1
sort -c mysort.out 2>> sortrace.log
echo "All done" | tee -a sortrace.log
