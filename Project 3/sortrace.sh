############################################################
# this file should be called sortrace.sh Please rename it 
# it must have execute privilege set to run
# run it as a background task like this: 
#		$ rm sortrace.log		# start with fresh log file
#		$ sortrace.sh >> sortrace.log &
###########################################################
echo Generating 100000 random numbers
sleep 1
./generate 5 10 20  # you have to write generate.cpp
sleep 1
echo Starting system sort
sleep 1
{ time sort numbers.dat > systemsort.out; } 2>&1>> sortrace.log     # modification for Mac computers
sleep 1
echo Starting my sort
sleep 1
{ time ./mysort numbers.dat mysort.out; } 2>&1>> sortrace.log     # you have to write mysort.cpp
sleep 1
rm sortrace.log                                            # modification for Mac computers
sort -c mysort.out 2>> sortrace.log  		            # verify file is sorted
