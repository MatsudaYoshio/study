clear all; close all;                         % 初期化

%%%　平均値フィルタの作成　%%%
N = 3;                                        % フィルタ係数のサイズ
filt_ave = ones(N,N) / N^2;                   % 平均値フィルタ

%%%　平均値フィルタの周波数スペクトル　%%%
M = 512;                                      % フィルタリングする画像のサイズ
ave = filt_ave;
ave(M,M) = 0;                                 % ゼロを付加してM行M列にする
ft_ave = fft2(ave);                           % フーリエ変換
ft_ave = fftshift(ft_ave);                    % 低周波成分を中心に移動
ps = abs(ft_ave).^2;                          % パワースペクトル
figure; imshow(ps,[]); axis on;               % パワースペクトルの表示


% %%%　人物のグレースケール画像　%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% I = imread('person.jpg');                     % 画像の読み込み
% I_size = size(I);                             % 画像サイズの取得
% Ig = zeros(I_size(1),I_size(2));              % グレースケール画像のための配列の初期化
% 
% %%%　グレースケール画像への変換　%%%
% for i = 1 : I_size(1)
%     for j = 1 : I_size(2)
%         Ig(i,j) =  0.229 * I(i,j,1) + 0.587 * I(i,j,2) + 0.114 * I(i,j,3);
%     end
% end
% 
% Ig_f = convn(Ig,filt_ave,'same');             % 畳み込みによるフィルタリング
% figure; imshow(Ig,[]);                        % 元画像の表示            
% figure; imshow(Ig_f,[]);                      % フィルタリング後の画像の表示
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 
% 
% %%%　文字の2値画像　%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% I = imread('character.jpg');                  % 画像の読み込み
% I_size = size(I);                             % 画像サイズの取得
% Ig = zeros(I_size(1),I_size(2));              % グレースケール画像のための配列の初期化
% 
% %%%　グレースケール画像への変換　%%%
% for i = 1 : I_size(1)
%     for j = 1 : I_size(2)
%         Ig(i,j) =  0.229 * I(i,j,1) + 0.587 * I(i,j,2) + 0.114 * I(i,j,3);
%     end
% end
% 
% %%%　画像の2値化　%%%
% Ib = zeros(I_size(1),I_size(2));              % 2値化画像のための配列の初期化
% theta = 220;                                  % 閾値
% for i = 1 : I_size(1)
%     for j = 1 : I_size(2)
%         if(Ig(i,j) > theta) Ib(i,j) = 1;
%         else Ib(i,j) = 0;
%         end
%     end
% end
% 
% Ib_f = convn(Ib,filt_ave,'same');             % 畳み込みによるフィルタリング
% figure; imshow(Ib,[]);                        % 元画像の表示            
% figure; imshow(Ib_f,[]);                      % フィルタリング後の画像の表示
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%　特徴のある画像　%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
I = imread('neon.jpg');                       % 画像の読み込み
I_size = size(I);                             % 画像サイズの取得

%%%　グレースケール画像への変換　%%%
for i = 1 : I_size(1)
    for j = 1 : I_size(2)
        Ig(i,j) =  0.229 * I(i,j,1) + 0.587 * I(i,j,2) + 0.114 * I(i,j,3);
    end
end

Ig_f = convn(Ig,filt_ave,'same');             % 畳み込みによるフィルタリング
figure; imshow(Ig,[]);                        % 元画像の表示            
figure; imshow(Ig_f,[]);                      % フィルタリング後の画像の表示
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%