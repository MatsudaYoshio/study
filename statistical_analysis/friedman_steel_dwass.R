# �t���[�h�}������{�����r�i�X�e�B�[���h�D���X����j
# �O�Q�ȏ�i��v���j,�Ή�����,�m���p�����g���b�N
# �v������@�Ń��b�J�[�g�ړx�̃A���P�[�g�Ƃ��Ɏg���A�Ⴆ�΁A����=3�ŎO��@

library(openxlsx)
library(stringr)
library(NSM3)

file.path <- './friedman_steel_dwass_sample.xlsx'

all.data <- read.xlsx(file.path, 1)

level <- 3 # �����̐��i��@�̐��j
item.num <- (ncol(all.data)-1)/level # ���ڐ�
participant.num <- nrow(all.data[1]) # �팱�҂̐�

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

	# �e���ڂ̑S���̃f�[�^���g���Đ��K���̌���i�V���s���E�E�B���N����j���s���A�A�������i�W�{���z�����K���z�ɏ]���j�����p����邱�Ƃ��m�F
	print(shapiro.test(x=data))
	
	# �t���[�h�}������
	print(friedman.test(y=matrix(data, ncol=level)))

	# �����r�i�X�e�B�[���h�D���X����j
	# method��"Exact", "Monte Carlo", "Asymptotic"��������
	# �W�{�T�C�Y��10�ȉ����炢�Ȃ�"Exact"�ŁA����ȊO��"Asymptotic"�ł���
	# �S�̓I�ɏ������d��
	print(pSDCFlig(x=data, g=methods, method="Asymptotic"))

	cat(sprintf('--------------------------------------------------\n'))
}