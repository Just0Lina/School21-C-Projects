while !(grep -l 'Run' Result.txt)
do
make -s SharpTests > Result.txt

done