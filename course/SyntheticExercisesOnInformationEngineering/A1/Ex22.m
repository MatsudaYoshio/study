clear all; close all;                         % ������

%%%�@���ϒl�t�B���^�̍쐬�@%%%
N = 3;                                        % �t�B���^�W���̃T�C�Y
filt_ave = ones(N,N) / N^2;                   % ���ϒl�t�B���^

%%%�@���ϒl�t�B���^�̎��g���X�y�N�g���@%%%
M = 512;                                      % �t�B���^�����O����摜�̃T�C�Y
ave = filt_ave;
ave(M,M) = 0;                                 % �[����t������M�sM��ɂ���
ft_ave = fft2(ave);                           % �t�[���G�ϊ�
ft_ave = fftshift(ft_ave);                    % ����g�����𒆐S�Ɉړ�
ps = abs(ft_ave).^2;                          % �p���[�X�y�N�g��
figure; imshow(ps,[]); axis on;               % �p���[�X�y�N�g���̕\��


% %%%�@�l���̃O���[�X�P�[���摜�@%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% I = imread('person.jpg');                     % �摜�̓ǂݍ���
% I_size = size(I);                             % �摜�T�C�Y�̎擾
% Ig = zeros(I_size(1),I_size(2));              % �O���[�X�P�[���摜�̂��߂̔z��̏�����
% 
% %%%�@�O���[�X�P�[���摜�ւ̕ϊ��@%%%
% for i = 1 : I_size(1)
%     for j = 1 : I_size(2)
%         Ig(i,j) =  0.229 * I(i,j,1) + 0.587 * I(i,j,2) + 0.114 * I(i,j,3);
%     end
% end
% 
% Ig_f = convn(Ig,filt_ave,'same');             % ��ݍ��݂ɂ��t�B���^�����O
% figure; imshow(Ig,[]);                        % ���摜�̕\��            
% figure; imshow(Ig_f,[]);                      % �t�B���^�����O��̉摜�̕\��
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 
% 
% %%%�@������2�l�摜�@%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% I = imread('character.jpg');                  % �摜�̓ǂݍ���
% I_size = size(I);                             % �摜�T�C�Y�̎擾
% Ig = zeros(I_size(1),I_size(2));              % �O���[�X�P�[���摜�̂��߂̔z��̏�����
% 
% %%%�@�O���[�X�P�[���摜�ւ̕ϊ��@%%%
% for i = 1 : I_size(1)
%     for j = 1 : I_size(2)
%         Ig(i,j) =  0.229 * I(i,j,1) + 0.587 * I(i,j,2) + 0.114 * I(i,j,3);
%     end
% end
% 
% %%%�@�摜��2�l���@%%%
% Ib = zeros(I_size(1),I_size(2));              % 2�l���摜�̂��߂̔z��̏�����
% theta = 220;                                  % 臒l
% for i = 1 : I_size(1)
%     for j = 1 : I_size(2)
%         if(Ig(i,j) > theta) Ib(i,j) = 1;
%         else Ib(i,j) = 0;
%         end
%     end
% end
% 
% Ib_f = convn(Ib,filt_ave,'same');             % ��ݍ��݂ɂ��t�B���^�����O
% figure; imshow(Ib,[]);                        % ���摜�̕\��            
% figure; imshow(Ib_f,[]);                      % �t�B���^�����O��̉摜�̕\��
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%�@�����̂���摜�@%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
I = imread('neon.jpg');                       % �摜�̓ǂݍ���
I_size = size(I);                             % �摜�T�C�Y�̎擾

%%%�@�O���[�X�P�[���摜�ւ̕ϊ��@%%%
for i = 1 : I_size(1)
    for j = 1 : I_size(2)
        Ig(i,j) =  0.229 * I(i,j,1) + 0.587 * I(i,j,2) + 0.114 * I(i,j,3);
    end
end

Ig_f = convn(Ig,filt_ave,'same');             % ��ݍ��݂ɂ��t�B���^�����O
figure; imshow(Ig,[]);                        % ���摜�̕\��            
figure; imshow(Ig_f,[]);                      % �t�B���^�����O��̉摜�̕\��
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%