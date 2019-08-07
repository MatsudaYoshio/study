# ウィルコクソンの符号順位検定
# 二群（二手法）,対応あり,ノンパラメトリック
# 二つの手法でリッカート尺度のアンケートとかに使う

library(openxlsx)
library(stringr)
library(exactRankTests)

item.num <- 7 # 項目数
file.path <- './wilcoxon_signed_rank_test_sample.xlsx'

all.data <- read.xlsx(file.path, 1)

item.name <- str_sub(colnames(all.data[2:(2+item.num-1)]), start = 1, end = -4)

data1 <- all.data[2:(2+item.num-1)]
data2 <- all.data[(2+item.num):(2*item.num+1)]

for (i in 1:item.num){
	cat(sprintf('-------------- %s --------------\n', item.name[i]))
	print(wilcox.exact(x=t(data1[i]), y=t(data2[i]), paired=T))
	cat(sprintf('--------------------------------------------------\n', item.name[i]))
}