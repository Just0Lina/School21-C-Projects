#b-----b-------b
Ny=1
N=1
Nfail=0
Nok=0
for file in cat/tests/b_flag_tests/*; do
    cat -b $file > test_cat;
    ./s21_cat -b $file > test_S21_cat;
    cmp test_cat test_S21_cat;
    if [ $? -eq 0 ]; then
        echo "b_flag_tests [$N] OK"
        ((Nok++))
    else
        echo "b_flag_tests [$N] FAIL WITH FILE $file"
        ((Nfail++))
    fi
    ((N++))
    ((Ny++))
   rm test_cat test_S21_cat;
done
echo "b_flag_tests FAIL = [$Nfail] OK = [$Nok]"


for file in cat/tests/e_flag_tests/*; do
    cat -e $file > test_cat;
    ./s21_cat -e $file > test_S21_cat;
    cmp test_cat test_S21_cat;
    if [ $? -eq 0 ]; then
        echo "e_flag_tests [$N] OK"
        ((Nok++))
    else
        echo "e_flag_tests [$N] FAIL WITH FILE $file"
        ((Nfail++))
    fi
    ((N++))
    ((Ny++))
     rm test_cat test_S21_cat;
done
echo "e_flag_tests FAIL = [$Nfail] OK = [$Nok]"

for file in cat/tests/n_flag_tests/*; do
    cat -n $file > test_cat;
    ./s21_cat -n $file > test_S21_cat;
    cmp test_cat test_S21_cat;
    if [ $? -eq 0 ]; then
        echo "n_flag_tests [$N] OK"
        ((Nok++))
    else
        echo "n_flag_tests [$N] FAIL WITH FILE $file"
        ((Nfail++))
    fi
    ((N++))
    ((Ny++))
     rm test_cat test_S21_cat;
done
echo "n_flag_tests FAIL = [$Nfail] OK = [$Nok]"

for file in cat/tests/s_flag_tests/*; do
    cat -s $file > test_cat;
    ./s21_cat -s $file > test_S21_cat;
    cmp test_cat test_S21_cat;
    if [ $? -eq 0 ]; then
        echo "s_flag_tests [$N] OK"
        ((Nok++))
    else
        echo "s_flag_tests [$N] FAIL WITH FILE $file"
        ((Nfail++))
    fi
    ((N++))
    ((Ny++))
     rm test_cat test_S21_cat;
done
echo "t_flag_tests FAIL = [$Nfail] OK = [$Nok]"

for file in cat/tests/t_flag_tests/*; do
    cat -t $file > test_cat;
        ./s21_cat -t $file > test_S21_cat;
    cmp test_cat test_S21_cat;
    if [ $? -eq 0 ]; then
        echo "t_flag_tests [$N] OK"
        ((Nok++))
    else
        echo "t_flag_tests [$N] FAIL WITH FILE $file"
        ((Nfail++))
    fi
    ((N++))
    ((Ny++))
     rm test_cat test_S21_cat;
done
echo "t_flag_tests FAIL = [$Nfail] OK = [$Nok]"

for file in cat/tests/binary_files_tests/*; do
    cat $file > test_cat;
    ./s21_cat $file > test_S21_cat;
    cmp test_cat test_S21_cat;
    if [ $? -eq 0 ]; then
        echo "binary_files_tests [$N] OK"
        ((Nok++))
    else
        echo "binary_files_tests [$N] FAIL WITH FILE $file"
        ((Nfail++))
    fi
    ((N++))
    ((Ny++))
     rm test_cat test_S21_cat;
done
echo "binary_files_tests FAIL = [$Nfail] OK = [$Nok]"
