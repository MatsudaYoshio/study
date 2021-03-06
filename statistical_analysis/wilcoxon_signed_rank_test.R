# ウィルコクソンの符号順位検定
# 二群（二手法）,対応あり,ノンパラメトリック
# 二つの手法でリッカート尺度のアンケートとかに使う

library(openxlsx)
library(stringr)
library(exactRankTests)

file.path <- './wilcoxon_signed_rank_test_sample.xlsx'

all.data <- read.xlsx(file.path, 1)

item.num <- (ncol(all.data)-1)/2 # 項目数

item.name <- str_sub(colnames(all.data[2:(2+item.num-1)]), start = 1, end = -4)

data1 <- all.data[2:(2+item.num-1)] 
data2 <- all.data[(2+item.num):(2*item.num+1)]

for (i in 1:item.num){
	cat(sprintf('-------------- %s --------------\n', item.name[i]))

	# 各項目の全部のデータを使って正規性の検定（シャピロ・ウィルク検定）を行い、帰無仮説（標本分布が正規分布に従う）が棄却されることを確認する
	all.vector <- append(as.vector(t(data1[i])), as.vector(t(data2[i])))
	print(shapiro.test(x=all.vector))
	
	# 各項目でウィルコクソンの符号順位検定を行う	
	print(wilcox.exact(x=t(data1[i]), y=t(data2[i]), paired=T))
	
	cat(sprintf('--------------------------------------------------\n'))
}