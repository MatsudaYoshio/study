# �E�B���R�N�\���̕������ʌ���
# ��Q�i���@�j,�Ή�����,�m���p�����g���b�N
# ��̎�@�Ń��b�J�[�g�ړx�̃A���P�[�g�Ƃ��Ɏg��

library(openxlsx)
library(stringr)
library(exactRankTests)

item.num <- 7 # ���ڐ�
file.path <- './wilcoxon_signed_rank_test_sample.xlsx'

all.data <- read.xlsx(file.path, 1)

item.name <- str_sub(colnames(all.data[2:(2+item.num-1)]), start = 1, end = -4)

data1 <- all.data[2:(2+item.num-1)] 
data2 <- all.data[(2+item.num):(2*item.num+1)]

# ���K���̌���i�V���s���E�E�B���N����j���s���A�A�������i�W�{���z�����K���z�ɏ]���j�����p����邱�Ƃ��m�F����
all.vector <- append(as.vector(t(data1)), as.vector(t(data2)))
shapiro.test(x=all.vector)

# �e���ڂŃE�B���R�N�\���̕������ʌ�����s��
for (i in 1:item.num){
	cat(sprintf('-------------- %s --------------\n', item.name[i]))
	print(wilcox.exact(x=t(data1[i]), y=t(data2[i]), paired=T))
	cat(sprintf('--------------------------------------------------\n', item.name[i]))
}