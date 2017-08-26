clear all; close all;                         % ������

%%%�@���ϒl�t�B���^�̍쐬�@%%%
N = 3;                                        % �t�B���^�W���̃T�C�Y
filt_ave = ones(N,N) / N^2;                   % ���ϒl�t�B���^

%%%�@���ϒl�t�B���^�̎��g���X�y�N�g���@%%%
M = 512;                                      % �t�B���^�����O����摜�̃T�C�Y
filt_ave(M,M) = 0;                            % �[����t������M�sM��ɂ���
ft_ave = fft2(filt_ave);                      % �t�[���G�ϊ�
fts_ave = fftshift(ft_ave);                   % ����g�����𒆐S�Ɉړ�
ps = abs(fts_ave).^2;                         % �p���[�X�y�N�g��
figure; imshow(ps,[]); axis on;               % �p���[�X�y�N�g���̕\��

%%%�@Sobel�t�B���^�̍쐬�@%%%
filt_sobel_h = [-1 0 1; -2 0 2; -1 0 1];      % Sobel�t�B���^(��������)
filt_sobel_v = [-1 -2 -1; 0 0 0; 1 2 1];      % Sobel�t�B���^(��������)

%%%�@Sobel�t�B���^�̎��g���X�y�N�g���@%%%
M = 512;                                      % �t�B���^�����O����摜�̃T�C�Y
filt_sobel_h(M,M) = 0;                        % �[����t������M�sM��ɂ���
ft_sobel_h = fft2(filt_sobel_h);              % �t�[���G�ϊ�
fts_sobel_h = fftshift(ft_sobel_h);           % ����g�����𒆐S�Ɉړ�
ps = abs(fts_sobel_h).^2;                     % �p���[�X�y�N�g��
figure; imshow(ps,[]); axis on;               % �p���[�X�y�N�g���̕\��

filt_sobel_v(M,M) = 0;                        % �[����t������M�sM��ɂ���
ft_sobel_v = fft2(filt_sobel_v);              % �t�[���G�ϊ�
fts_sobel_v = fftshift(ft_sobel_v);           % ����g�����𒆐S�Ɉړ�
ps = abs(fts_sobel_v).^2;                     % �p���[�X�y�N�g��
figure; imshow(ps,[]); axis on;               % �p���[�X�y�N�g���̕\��

%%%�@���v���V�A���t�B���^�̍쐬�@%%%
filt_lap = [0 1 0; 1 -4 1; 0 1 0];            % ���v���V�A���t�B���^

%%%�@���v���V�A���t�B���^�̎��g���X�y�N�g���@%%%
M = 512;                                      % �t�B���^�����O����摜�̃T�C�Y
filt_lap(M,M) = 0;                            % �[����t������M�sM��ɂ���
ft_lap = fft2(filt_lap);                      % �t�[���G�ϊ�
fts_lap = fftshift(ft_lap);                   % ����g�����𒆐S�Ɉړ�
ps = abs(fts_lap).^2;                         % �p���[�X�y�N�g��
figure; imshow(ps,[]); axis on;               % �p���[�X�y�N�g���̕\��

%%%�@�l���̃O���[�X�P�[���摜�@%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
I = imread('person.jpg');                     % �摜�̓ǂݍ���
I_size = size(I);                             % �摜�T�C�Y�̎擾
Ig = zeros(I_size(1),I_size(2));              % �O���[�X�P�[���摜�̂��߂̔z��̏�����

%%%�@�O���[�X�P�[���摜�ւ̕ϊ��@%%%
for i = 1 : I_size(1)
    for j = 1 : I_size(2)
        Ig(i,j) =  0.229 * I(i,j,1) + 0.587 * I(i,j,2) + 0.114 * I(i,j,3);
    end
end

%%%�@���ϒl�t�B���^�ɂ��t�B���^�����O�@%%%
Ig_f = ifft2(fft2(Ig) .* ft_ave);
figure; imshow(Ig,[]);                        % ���摜�̕\��            
figure; imshow(Ig_f,[]);                      % �t�B���^�����O��̉摜�̕\��

%%%�@Sobel�t�B���^�ɂ��t�B���^�����O�@%%%
Ig_f = ifft2(fft2(Ig) .* ft_sobel_h);          
figure; imshow(Ig_f,[]);                      % �t�B���^�����O��̉摜�̕\��

Ig_f = ifft2(fft2(Ig) .* ft_sobel_v);        
figure; imshow(Ig_f,[]);                      % �t�B���^�����O��̉摜�̕\��

%%%�@���v���V�A���t�B���^�ɂ��t�B���^�����O�@%%%
Ig_f = ifft2(fft2(Ig) .* ft_lap);         
figure; imshow(Ig_f,[]);                      % �t�B���^�����O��̉摜�̕\��
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%�@������2�l�摜�@%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
I = imread('character.jpg');                  % �摜�̓ǂݍ���
I_size = size(I);                             % �摜�T�C�Y�̎擾
Ig = zeros(I_size(1),I_size(2));              % �O���[�X�P�[���摜�̂��߂̔z��̏�����

%%%�@�O���[�X�P�[���摜�ւ̕ϊ��@%%%
for i = 1 : I_size(1)
    for j = 1 : I_size(2)
        Ig(i,j) =  0.229 * I(i,j,1) + 0.587 * I(i,j,2) + 0.114 * I(i,j,3);
    end
end

%%%�@�摜��2�l���@%%%
Ib = zeros(I_size(1),I_size(2));              % 2�l���摜�̂��߂̔z��̏�����
theta = 220;                                  % 臒l
for i = 1 : I_size(1)
    for j = 1 : I_size(2)
        if(Ig(i,j) > theta) Ib(i,j) = 1;
        else Ib(i,j) = 0;
        end
    end
end


%%%�@���ϒl�t�B���^�ɂ��t�B���^�����O�@%%%
Ib_f = ifft2(fft2(Ib) .* ft_ave);
figure; imshow(Ib,[]);                        % ���摜�̕\��            
figure; imshow(Ib_f,[]);                      % �t�B���^�����O��̉摜�̕\��

%%%�@Sobel�t�B���^�ɂ��t�B���^�����O�@%%%
Ib_f = ifft2(fft2(Ig) .* ft_sobel_h);         
figure; imshow(Ib_f,[]);                      % �t�B���^�����O��̉摜�̕\��

Ib_f = ifft2(fft2(Ib) .* ft_sobel_v);          
figure; imshow(Ib_f,[]);                      % �t�B���^�����O��̉摜�̕\��

%%%�@���v���V�A���t�B���^�ɂ��t�B���^�����O�@%%%
Ib_f = ifft2(fft2(Ib) .* ft_lap);        
figure; imshow(Ib_f,[]);                      % �t�B���^�����O��̉摜�̕\��
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%�@�����̂���摜�@%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
I = imread('neon.jpg');                       % �摜�̓ǂݍ���
I_size = size(I);                   

%%%�@�O���[�X�P�[���摜�ւ̕ϊ��@%%%
for i = 1 : I_size(1)
    for j = 1 : I_size(2)
        Ig(i,j) =  0.229 * I(i,j,1) + 0.587 * I(i,j,2) + 0.114 * I(i,j,3);
    end
end

%%%�@���ϒl�t�B���^�ɂ��t�B���^�����O�@%%%
Ig_f = ifft2(fft2(Ig) .* ft_ave);
figure; imshow(Ig,[]);                        % ���摜�̕\��            
figure; imshow(Ig_f,[]);                      % �t�B���^�����O��̉摜�̕\��

%%%�@Sobel�t�B���^�ɂ��t�B���^�����O�@%%%
Ig_f = ifft2(fft2(Ig) .* ft_sobel_h);
figure; imshow(Ig_f,[]);                      % �t�B���^�����O��̉摜�̕\��

Ig_f = ifft2(fft2(Ig) .* ft_sobel_v);          
figure; imshow(Ig_f,[]);                      % �t�B���^�����O��̉摜�̕\��

%%%�@���v���V�A���t�B���^�ɂ��t�B���^�����O�@%%%
Ig_f = ifft2(fft2(Ig) .* ft_lap);          
figure; imshow(Ig_f,[]);                      % �t�B���^�����O��̉摜�̕\��
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%