echo "<NearestNeighbor>"
read -p "巡回路を開始する都市番号(1~150)を入力してください：" x
./Ex5-1_nn 150 $x < kroB150.tsp
