echo "どの構築法で初期解を与えるか入力してください"
read -p "最近傍法:nn 最近追加法:na ランダム法:r インデックス法:i >" x
case $x in
    nn)
	echo "<NearestNeighbor>"
	read -p "巡回路を開始する都市番号(1~150)を入力してください：" n
	./Ex5-1_nn 150 $n < kroB150.tsp
	echo "<2-opt>"
	./Ex5-2 150 < ./Ex5-1_nn_ans.txt
	;;
    na)
	echo "<NearestAddition>"
	read -p "巡回路を開始する都市番号(1~150)を入力してください：" n
	./Ex5-1_na 150 $n < kroB150.tsp
	echo "<2-opt>"
	./Ex5-2 150 < ./Ex5-1_na_ans.txt
	;;
    r)
	echo "<Random>"
	./Ex5-1_random 150 < kroB150.tsp
	echo "<2-opt>"
	./Ex5-2 150 < ./Ex5-1_random_ans.txt
	;;
    i)
	echo "<Index>"
	./Ex5-1_index 150 < kroB150.tsp
	echo "<2-opt>"
	./Ex5-2 150 < ./Ex5-1_index_ans.txt
	;;
esac

