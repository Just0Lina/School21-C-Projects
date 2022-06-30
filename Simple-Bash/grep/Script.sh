#b-----b-------b
Ny=1
N=1
Nfail=0
Nok=0
for file in grep/tests/e_flag_tests/*; do
    grep -e consequat $file > test_grep;
    ./s21_grep -e consequat $file > test_S21_grep;
    cmp test_grep test_S21_grep;
    if [ $? -eq 0 ]; then
        echo "e_flag_tests [$N] OK"
        ((Nok++))
    else
        echo "e_flag_tests [$N] FAIL WITH FILE $file"
        ((Nfail++))
    fi
    ((N++))
    ((Ny++))
   rm test_grep test_S21_grep;
done
echo "e_flag_tests FAIL = [$Nfail] OK = [$Nok]"

for file in grep/tests/i_flag_tests/*; do
    grep -i lacinia $file > test_grep;
    ./s21_grep -i lacinia $file > test_S21_grep;
    cmp test_grep test_S21_grep;
    if [ $? -eq 0 ]; then
        echo "i_flag_tests [$N] OK"
        ((Nok++))
    else
        echo "i_flag_tests [$N] FAIL WITH FILE $file"
        ((Nfail++))
    fi
    ((N++))
    ((Ny++))
   rm test_grep test_S21_grep;
done
echo "i_flag_tests FAIL = [$Nfail] OK = [$Nok]"

for file in grep/tests/v_flag_tests/*; do
    grep -v lacinia $file > test_grep;
    ./s21_grep -v lacinia $file > test_S21_grep;
    cmp test_grep test_S21_grep;
    if [ $? -eq 0 ]; then
        echo "v_flag_tests [$N] OK"
        ((Nok++))
    else
        echo "v_flag_tests [$N] FAIL WITH FILE $file"
        ((Nfail++))
    fi
    ((N++))
    ((Ny++))
   rm test_grep test_S21_grep;
done
echo "v_flag_tests FAIL = [$Nfail] OK = [$Nok]"

for file in grep/tests/c_flag_tests/*; do
    grep -c lacinia $file > test_grep;
    ./s21_grep -c lacinia $file > test_S21_grep;
    cmp test_grep test_S21_grep;
    if [ $? -eq 0 ]; then
        echo "c_flag_tests [$N] OK"
        ((Nok++))
    else
        echo "c_flag_tests [$N] FAIL WITH FILE $file"
        ((Nfail++))
    fi
    ((N++))
    ((Ny++))
   rm test_grep test_S21_grep;
done
echo "c _flag_tests FAIL = [$Nfail] OK = [$Nok]"

for file in grep/tests/l_flag_tests/*; do
    grep -l lacinia $file > test_grep;
    ./s21_grep -l lacinia $file > test_S21_grep;
    cmp test_grep test_S21_grep;
    if [ $? -eq 0 ]; then
        echo "l_flag_tests [$N] OK"
        ((Nok++))
    else
        echo "l_flag_tests [$N] FAIL WITH FILE $file"
        ((Nfail++))
    fi
    ((N++))
    ((Ny++))
   rm test_grep test_S21_grep;
done
echo "l _flag_tests FAIL = [$Nfail] OK = [$Nok]"

for file in grep/tests/n_flag_tests/*; do
    grep -n lacinia $file > test_grep;
    ./s21_grep -n lacinia $file > test_S21_grep;
    cmp test_grep test_S21_grep;
    if [ $? -eq 0 ]; then
        echo "n_flag_tests [$N] OK"
        ((Nok++))
    else
        echo "n_flag_tests [$N] FAIL WITH FILE $file"
        ((Nfail++))
    fi
    ((N++))
    ((Ny++))
   rm test_grep test_S21_grep;
done
echo "n _flag_tests FAIL = [$Nfail] OK = [$Nok]"




