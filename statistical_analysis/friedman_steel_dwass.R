# フリードマン検定＋事後比較（スティールドゥワス検定）
# 三群以上（一要因）,対応あり,ノンパラメトリック
# 要因＝手法でリッカート尺度のアンケートとかに使う、例えば、水準=3で三手法

library(openxlsx)
library(stringr)
library(NSM3)

file.path <- './friedman_steel_dwass_sample.xlsx'

all.data <- read.xlsx(file.path, 1)

level <- 3 # 水準の数（手法の数）
item.num <- (ncol(all.data)-1)/level # 項目数
participant.num <- nrow(all.data[1]) # 被験者の数

methods <- factor(c(rep('1', participant.num), rep('2', participant.num), rep('3', participant.num)))

item.name <- str_sub(colnames(all.data[seq(from = 2, to = ncol(all.data), by = level)]
), start = 1, end = -4)

for(i in 1:item.num){
	cat(sprintf('-------------- %s --------------\n', item.name[i]))
	
	data <- c(t(all.data[(2+level*(i-1))]))
	for(j in (3+level*(i-1)):(1+level*i)){
		data <- c(data, t(all.data[j]))
	}

	# 各項目の全部のデータを使って正規性の検定（シャピロ・ウィルク検定）を行い、帰無仮説（標本分布が正規分布に従う）が棄却されることを確認
	print(shapiro.test(x=data))
	
	# フリードマン検定
	print(friedman.test(y=matrix(data, ncol=level)))

	# 事後比較（スティールドゥワス検定）
	# methodは"Exact", "Monte Carlo", "Asymptotic"があって
	# 標本サイズが10以下ぐらいなら"Exact"で、それ以外は"Asymptotic"でいい
	# 全体的に処理が重い
	print(pSDCFlig(x=data, g=methods, method="Asymptotic"))

	cat(sprintf('--------------------------------------------------\n'))
}