read -p "ノード数を入力してください：" x
head -n $x kroB150.tsp > testcase.txt
./Ex6-2 < testcase.txt
