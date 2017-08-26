clear all; close all;                         % 初期化

%%%　平均値フィルタの作成　%%%
N = 3;                                        % フィルタ係数のサイズ
filt_ave = ones(N,N) / N^2;                   % 平均値フィルタ

%%%　平均値フィルタの周波数スペクトル　%%%
M = 512;                                      % フィルタリングする画像のサイズ
filt_ave(M,M) = 0;                            % ゼロを付加してM行M列にする
ft_ave = fft2(filt_ave);                      % フーリエ変換
fts_ave = fftshift(ft_ave);                   % 低周波成分を中心に移動
ps = abs(fts_ave).^2;                         % パワースペクトル
figure; imshow(ps,[]); axis on;               % パワースペクトルの表示

%%%　Sobelフィルタの作成　%%%
filt_sobel_h = [-1 0 1; -2 0 2; -1 0 1];      % Sobelフィルタ(水平方向)
filt_sobel_v = [-1 -2 -1; 0 0 0; 1 2 1];      % Sobelフィルタ(垂直方向)

%%%　Sobelフィルタの周波数スペクトル　%%%
M = 512;                                      % フィルタリングする画像のサイズ
filt_sobel_h(M,M) = 0;                        % ゼロを付加してM行M列にする
ft_sobel_h = fft2(filt_sobel_h);              % フーリエ変換
fts_sobel_h = fftshift(ft_sobel_h);           % 低周波成分を中心に移動
ps = abs(fts_sobel_h).^2;                     % パワースペクトル
figure; imshow(ps,[]); axis on;               % パワースペクトルの表示

filt_sobel_v(M,M) = 0;                        % ゼロを付加してM行M列にする
ft_sobel_v = fft2(filt_sobel_v);              % フーリエ変換
fts_sobel_v = fftshift(ft_sobel_v);           % 低周波成分を中心に移動
ps = abs(fts_sobel_v).^2;                     % パワースペクトル
figure; imshow(ps,[]); axis on;               % パワースペクトルの表示

%%%　ラプラシアンフィルタの作成　%%%
filt_lap = [0 1 0; 1 -4 1; 0 1 0];            % ラプラシアンフィルタ

%%%　ラプラシアンフィルタの周波数スペクトル　%%%
M = 512;                                      % フィルタリングする画像のサイズ
filt_lap(M,M) = 0;                            % ゼロを付加してM行M列にする
ft_lap = fft2(filt_lap);                      % フーリエ変換
fts_lap = fftshift(ft_lap);                   % 低周波成分を中心に移動
ps = abs(fts_lap).^2;                         % パワースペクトル
figure; imshow(ps,[]); axis on;               % パワースペクトルの表示

%%%　人物のグレースケール画像　%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
I = imread('person.jpg');                     % 画像の読み込み
I_size = size(I);                             % 画像サイズの取得
Ig = zeros(I_size(1),I_size(2));              % グレースケール画像のための配列の初期化

%%%　グレースケール画像への変換　%%%
for i = 1 : I_size(1)
    for j = 1 : I_size(2)
        Ig(i,j) =  0.229 * I(i,j,1) + 0.587 * I(i,j,2) + 0.114 * I(i,j,3);
    end
end

%%%　平均値フィルタによるフィルタリング　%%%
Ig_f = ifft2(fft2(Ig) .* ft_ave);
figure; imshow(Ig,[]);                        % 元画像の表示            
figure; imshow(Ig_f,[]);                      % フィルタリング後の画像の表示

%%%　Sobelフィルタによるフィルタリング　%%%
Ig_f = ifft2(fft2(Ig) .* ft_sobel_h);          
figure; imshow(Ig_f,[]);                      % フィルタリング後の画像の表示

Ig_f = ifft2(fft2(Ig) .* ft_sobel_v);        
figure; imshow(Ig_f,[]);                      % フィルタリング後の画像の表示

%%%　ラプラシアンフィルタによるフィルタリング　%%%
Ig_f = ifft2(fft2(Ig) .* ft_lap);         
figure; imshow(Ig_f,[]);                      % フィルタリング後の画像の表示
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%　文字の2値画像　%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
I = imread('character.jpg');                  % 画像の読み込み
I_size = size(I);                             % 画像サイズの取得
Ig = zeros(I_size(1),I_size(2));              % グレースケール画像のための配列の初期化

%%%　グレースケール画像への変換　%%%
for i = 1 : I_size(1)
    for j = 1 : I_size(2)
        Ig(i,j) =  0.229 * I(i,j,1) + 0.587 * I(i,j,2) + 0.114 * I(i,j,3);
    end
end

%%%　画像の2値化　%%%
Ib = zeros(I_size(1),I_size(2));              % 2値化画像のための配列の初期化
theta = 220;                                  % 閾値
for i = 1 : I_size(1)
    for j = 1 : I_size(2)
        if(Ig(i,j) > theta) Ib(i,j) = 1;
        else Ib(i,j) = 0;
        end
    end
end


%%%　平均値フィルタによるフィルタリング　%%%
Ib_f = ifft2(fft2(Ib) .* ft_ave);
figure; imshow(Ib,[]);                        % 元画像の表示            
figure; imshow(Ib_f,[]);                      % フィルタリング後の画像の表示

%%%　Sobelフィルタによるフィルタリング　%%%
Ib_f = ifft2(fft2(Ig) .* ft_sobel_h);         
figure; imshow(Ib_f,[]);                      % フィルタリング後の画像の表示

Ib_f = ifft2(fft2(Ib) .* ft_sobel_v);          
figure; imshow(Ib_f,[]);                      % フィルタリング後の画像の表示

%%%　ラプラシアンフィルタによるフィルタリング　%%%
Ib_f = ifft2(fft2(Ib) .* ft_lap);        
figure; imshow(Ib_f,[]);                      % フィルタリング後の画像の表示
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%　特徴のある画像　%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
I = imread('neon.jpg');                       % 画像の読み込み
I_size = size(I);                   

%%%　グレースケール画像への変換　%%%
for i = 1 : I_size(1)
    for j = 1 : I_size(2)
        Ig(i,j) =  0.229 * I(i,j,1) + 0.587 * I(i,j,2) + 0.114 * I(i,j,3);
    end
end

%%%　平均値フィルタによるフィルタリング　%%%
Ig_f = ifft2(fft2(Ig) .* ft_ave);
figure; imshow(Ig,[]);                        % 元画像の表示            
figure; imshow(Ig_f,[]);                      % フィルタリング後の画像の表示

%%%　Sobelフィルタによるフィルタリング　%%%
Ig_f = ifft2(fft2(Ig) .* ft_sobel_h);
figure; imshow(Ig_f,[]);                      % フィルタリング後の画像の表示

Ig_f = ifft2(fft2(Ig) .* ft_sobel_v);          
figure; imshow(Ig_f,[]);                      % フィルタリング後の画像の表示

%%%　ラプラシアンフィルタによるフィルタリング　%%%
Ig_f = ifft2(fft2(Ig) .* ft_lap);          
figure; imshow(Ig_f,[]);                      % フィルタリング後の画像の表示
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%