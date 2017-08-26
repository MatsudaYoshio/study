clear all; close all;                            % 初期化

N = 100;                                         % フィルタの次数（フィルタ長）
omega_c = pi / 4;                                % カットオフ周波数（遮断周波数）

n = 1 : 2*N+1;                                   % nの範囲を，正の範囲にシフトする   

h_c(n) = (1 ./ (pi .* (n-(N+1)))) .* sin(omega_c .* (n-(N+1)));
                                                 % ローパスフィルタのインパルス応答
h_c(N+1) = omega_c / pi;                         % n = N+1 のところに値を入れる
T_c = fft(h_c);                                  % フィルタの周波数特性（FFT）
A_c = abs(T_c);                                  % 振幅特性（Amplitude）
P_c = unwrap(atan2(imag(T_c),real(T_c)));        % 位相特性（Phase）

%%%　周波数特性の表示　%%%
figure; axis on;
subplot(2,1,1); plot(A_c);
axis([0 N 0 1.5]); title('Amplitude'); xlabel('n'); ylabel('A(ω)');

subplot(2,1,2); plot(P_c);
axis([0 N -80 2]); title('Phase'); xlabel('n'); ylabel('θ(ω)');