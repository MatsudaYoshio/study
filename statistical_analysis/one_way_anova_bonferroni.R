# ANOVA（一元配置分散分析）＋事後比較（ボンフェローニ補正によるt検定）
# 三群以上（一要因）,対応あり,パラメトリック
# 要因＝手法で定量評価とかに使う、例えば、水準=3で三手法

library(openxlsx)
library(stringr)

file.path <- './one_way_anova_bonferroni_sample.xlsx'

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

	# 各項目の全部のデータを使って等分散性の検定（バートレット検定）を行い、帰無仮説（各群の分散が均一）が棄却されないことを確認
	# もし棄却されるのならば、等分散性を仮定しないANOVAかノンパラメトリックの手法にする
	print(bartlett.test(formula=data~methods))

	# ANOVA
	# print(oneway.test(data~methods, var.equal=T)) # 等分散でないときも使えるやつ（var.equal=Fにすれば等分散でないANOVA）
	print(summary(aov(data~methods))) # 等分散性を仮定したやつ

	# 事後比較（ボンフェローニ補正によるt検定）
	print(pairwise.t.test(data, methods, p.adjust.method="bonferroni"))
	cat(sprintf('--------------------------------------------------\n', item.name[i]))
}