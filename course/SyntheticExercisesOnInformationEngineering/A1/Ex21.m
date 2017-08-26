clear all; close all;                           % 初期化

N = 256;                                        % 画像サイズ

%%%　周波数　%%%
f_x1 = 1/32;
f_x2 = 1/16;
f_y1 = 1/64;
f_y2 = 1/8;

%%%　角周波数　%%%
omega_x1 = 2*pi*f_x1;
omega_x2 = 2*pi*f_x2;
omega_y1 = 2*pi*f_y1;
omega_y2 = 2*pi*f_y2;

%%%　角周波数とNで範囲を調整　%%%
[x1,y1] = meshgrid(omega_x1:omega_x1:omega_x1*N,omega_y1:omega_y1:omega_y1*N);
[x2,y2] = meshgrid(omega_x2:omega_x2:omega_x2*N,omega_y2:omega_y2:omega_y2*N);

I_h = sin(x1);                                  % 横縞画像(周波数f_x1)
I_v = sin(y1);                                  % 縦縞画像(周波数f_y1)
I_hv = I_h+I_v+sin(x2)+sin(y2);                 % 縦と横の縞を合わせた画像

%%%　横縞画像の表示　%%%
figure; imshow(I_h,[]);                         % 画像の表示   
ftI = fft2(I_h);                                % フーリエ変換
ftI = fftshift(ftI);                            % 低周波成分を中心に移動
ps = abs(ftI).^2;                               % パワースペクトル
figure; imshow(ps,[]); axis on;                 % パワースペクトルの表示

%%%　縦縞画像の表示　%%%
figure; imshow(I_v,[]);                         % 画像の表示   
ftI = fft2(I_v);                                % フーリエ変換
ftI = fftshift(ftI);                            % 低周波成分を中心に移動
ps = abs(ftI).^2;                               % パワースペクトル
figure; imshow(ps,[]); axis on;                 % パワースペクトルの表示

%%%　縦と横の縞を合わせた画像の表示　%%%
figure; imshow(I_hv,[]);                        % 画像の表示   
ftI = fft2(I_hv);                               % フーリエ変換
ftI = fftshift(ftI);                            % 低周波成分を中心に移動
ps = abs(ftI).^2;                               % パワースペクトル
figure; imshow(ps,[]); axis on;                 % パワースペクトルの表示

%%%　横方向の周波数f_x1のみを通すバンドパスフィルタの作成　%%%
[p,q] = meshgrid(-N/2:N/2-1,-N/2:N/2-1);        % 軸の作成
filt = zeros(N,N);                              % 配列の初期化
filt(p == -f_x1*N | p == f_x1*N) = 1;           % 横の特定の周波数にだけ値を代入
figure; imshow(filt,[]); axis on;               % フィルタの表示

%%%　フィルタリング　%%%
ftI = ftI .* filt;                              % フィルタをかける
ps = abs(ftI).^2;                               % フィルタリング後のパワースペクトル
figure; imshow(ps,[]); axis on;                 % パワースペクトルの表示
ftI = ifftshift(ftI);                           % 逆fftshift
I_filt = ifft2(ftI);                            % 逆フーリエ変換
figure; imshow(I_filt, []);                     % フィルタリング後の画像の表示
