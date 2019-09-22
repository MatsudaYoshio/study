# ANOVA�i�ꌳ�z�u���U���́j�{�����r�i�{���t�F���[�j�␳�ɂ��t����j
# �O�Q�ȏ�i��v���j,�Ή�����,�p�����g���b�N
# �v������@�Œ�ʕ]���Ƃ��Ɏg���A�Ⴆ�΁A����=3�ŎO��@

library(openxlsx)
library(stringr)

file.path <- './one_way_anova_bonferroni_sample.xlsx'

all.data <- read.xlsx(file.path, 1)

level <- 3 # �����̐��i��@�̐��j
item.num <- (ncol(all.data)-1)/level # ���ڐ�
participant.num <- nrow(all.data[1]) # �팱�҂̐�
participants <- factor(c(rep(c(t(all.data[1])), level)))

# ���q�x�N�g���̐���
m <- NULL
for(i in 1:level){
	m <- c(m, c(rep(i, participant.num)))
}
methods <- factor(m, as.character(1:level))

item.name <- str_sub(colnames(all.data[seq(from = 2, to = ncol(all.data), by = level)]
), start = 1, end = -4)

for(i in 1:item.num){
	cat(sprintf('-------------- %s --------------\n', item.name[i]))
	
	data <- c(t(all.data[(2+level*(i-1))]))
	for(j in (3+level*(i-1)):(1+level*i)){
		data <- c(data, t(all.data[j]))
	}

	# �e���ڂ̑S���̃f�[�^���g���Đ��K���̌���i�V���s���E�E�B���N����j���s���A�A�������i�W�{���z�����K���z�ɏ]���j�����p����Ȃ����Ƃ��m�F
	# �������p�����̂ł���΁A�m���p�����g���b�N�̎�@����������
	print(shapiro.test(x=data))

	# �e���ڂ̑S���̃f�[�^���g���ē����U���̌���i�o�[�g���b�g����j���s���A�A�������i�e�Q�̕��U���ψ�j�����p����Ȃ����Ƃ��m�F
	# �������p�����̂ł���΁A�����U�������肵�Ȃ�ANOVA���m���p�����g���b�N�̎�@�ɂ���
	print(bartlett.test(formula=data~methods))

	# ANOVA
	# print(oneway.test(data~methods, var.equal=T)) # �����U�łȂ��Ƃ����g�����ivar.equal=F�ɂ���Γ����U�łȂ�ANOVA�j
	print(summary(aov(data~methods+participants))) # �����U�������肵�����

	# �����r�i�{���t�F���[�j�␳�ɂ��t����j
	print(pairwise.t.test(data, methods, p.adjust.method="bonferroni", paired=T))
	cat(sprintf('--------------------------------------------------\n'))
}