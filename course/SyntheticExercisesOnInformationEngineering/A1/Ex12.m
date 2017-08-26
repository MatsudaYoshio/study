clear all; close all;                            % 初期化

N = 100;                                         % フィルタの次数（フィルタ長）
omega_c = pi / 4;                                % カットオフ周波数（遮断周波数）

n = 1 : 2*N+1;                                   % nの範囲を，正の範囲にシフトする   

%%%%　窓関数を用いない　ローパスフィルタ　%%%%
h_c(n) = (1 ./ (pi .* (n-(N+1)))) .* sin(omega_c .* (n-(N+1)));
                                                 % ローパスフィルタのインパルス応答
h_c(N+1) = omega_c / pi;                         % n = N+1 のところに値を入れる

%%%%　窓関数を用いた　ローパスフィルタ　%%%%
%w(n) = 0.54 + 0.46 .* cos((n-(N+1)).*pi./N);     % 窓関数の定義（ハミング窓の場合）
w(n) = 0.42 + 0.5 .* cos((n-(N+1)).*pi./N) + 0.08 .* cos(2.*(n-(N+1)).*pi./N);
                                                 % 窓関数の定義（ブラックマン窓の場合）
h_cw = w .* h_c;                                 % 窓関数を掛け合わせたフィルタ係数
T_cw = fft(h_cw);                                % フィルタの周波数特性（FFT）
A_cw = abs(T_cw);                                % 振幅特性（Amplitude）
P_cw = unwrap(atan2(imag(T_cw),real(T_cw)));     % 位相特性（Phase）

%%%　周波数特性の表示　%%%
figure; axis on;
subplot(2,1,1); plot(A_cw);
axis([0 N 0 1.5]); title('Amplitude'); xlabel('n'); ylabel('A(ω)');

subplot(2,1,2); plot(P_cw);
axis([0 N -90 2]); title('Phase'); xlabel('n'); ylabel('θ(ω)');