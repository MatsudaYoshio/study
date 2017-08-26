clear all; close all;                           % ������

N = 256;                                        % �摜�T�C�Y

%%%�@���g���@%%%
f_x1 = 1/32;
f_x2 = 1/16;
f_y1 = 1/64;
f_y2 = 1/8;

%%%�@�p���g���@%%%
omega_x1 = 2*pi*f_x1;
omega_x2 = 2*pi*f_x2;
omega_y1 = 2*pi*f_y1;
omega_y2 = 2*pi*f_y2;

%%%�@�p���g����N�Ŕ͈͂𒲐��@%%%
[x1,y1] = meshgrid(omega_x1:omega_x1:omega_x1*N,omega_y1:omega_y1:omega_y1*N);
[x2,y2] = meshgrid(omega_x2:omega_x2:omega_x2*N,omega_y2:omega_y2:omega_y2*N);

I_h = sin(x1);                                  % ���ȉ摜(���g��f_x1)
I_v = sin(y1);                                  % �c�ȉ摜(���g��f_y1)
I_hv = I_h+I_v+sin(x2)+sin(y2);                 % �c�Ɖ��̎Ȃ����킹���摜

%%%�@���ȉ摜�̕\���@%%%
figure; imshow(I_h,[]);                         % �摜�̕\��   
ftI = fft2(I_h);                                % �t�[���G�ϊ�
ftI = fftshift(ftI);                            % ����g�����𒆐S�Ɉړ�
ps = abs(ftI).^2;                               % �p���[�X�y�N�g��
figure; imshow(ps,[]); axis on;                 % �p���[�X�y�N�g���̕\��

%%%�@�c�ȉ摜�̕\���@%%%
figure; imshow(I_v,[]);                         % �摜�̕\��   
ftI = fft2(I_v);                                % �t�[���G�ϊ�
ftI = fftshift(ftI);                            % ����g�����𒆐S�Ɉړ�
ps = abs(ftI).^2;                               % �p���[�X�y�N�g��
figure; imshow(ps,[]); axis on;                 % �p���[�X�y�N�g���̕\��

%%%�@�c�Ɖ��̎Ȃ����킹���摜�̕\���@%%%
figure; imshow(I_hv,[]);                        % �摜�̕\��   
ftI = fft2(I_hv);                               % �t�[���G�ϊ�
ftI = fftshift(ftI);                            % ����g�����𒆐S�Ɉړ�
ps = abs(ftI).^2;                               % �p���[�X�y�N�g��
figure; imshow(ps,[]); axis on;                 % �p���[�X�y�N�g���̕\��

%%%�@�������̎��g��f_x1�݂̂�ʂ��o���h�p�X�t�B���^�̍쐬�@%%%
[p,q] = meshgrid(-N/2:N/2-1,-N/2:N/2-1);        % ���̍쐬
filt = zeros(N,N);                              % �z��̏�����
filt(p == -f_x1*N | p == f_x1*N) = 1;           % ���̓���̎��g���ɂ����l����
figure; imshow(filt,[]); axis on;               % �t�B���^�̕\��

%%%�@�t�B���^�����O�@%%%
ftI = ftI .* filt;                              % �t�B���^��������
ps = abs(ftI).^2;                               % �t�B���^�����O��̃p���[�X�y�N�g��
figure; imshow(ps,[]); axis on;                 % �p���[�X�y�N�g���̕\��
ftI = ifftshift(ftI);                           % �tfftshift
I_filt = ifft2(ftI);                            % �t�t�[���G�ϊ�
figure; imshow(I_filt, []);                     % �t�B���^�����O��̉摜�̕\��
