clear all; close all;                           % 初期化

N = 100;                                        % フィルタの次数（フィルタ長）
omega_c = pi / 4;                               % カットオフ周波数（遮断周波数）

n = 1 : 2*N+1;                                  % nの範囲を，正の範囲にシフトする   

h_c(n) = (1 ./ (pi .* (n-(N+1)))) .* sin(omega_c .* (n-(N+1)));
                                                % ローパスフィルタのインパルス応答
h_c(N+1) = omega_c / pi;                        % n = N+1 のところに値を入れる
T_c = fft(h_c);                                 % フィルタの周波数特性（FFT）
A_c = abs(T_c);                                 % 振幅特性（Amplitude）
P_c = unwrap(atan2(imag(T_c),real(T_c)));       % 位相特性（Phase）


x(n) = 2.0 .* sin(pi/6 .* n) + 2.0 .* sin(pi/4 .* n) + sin(pi/2 .* n) + sin(pi/1.5 .* n);
                                                % 合成正弦波信号を生成
y = filter(x, 1, h_c);                          % 入力信号xのフィルタリング

M_x = length(x); M_y = length(y);               % 処理するデータ数
T_x = fft(x, 2*M_x);                            % 入力信号xのFFT
A_x = abs(T_x);                                 % xの振幅特性（Amplitude）
P_x = unwrap(atan2(imag(T_x),real(T_x)));       % xの位相特性（Phase）
T_y = fft(y, 2*M_y);                            % 出力信号yのFFT
A_y = abs(T_y);                                 % yの振幅特性（Amplitude）
P_y = unwrap(atan2(imag(T_y),real(T_y)));       % yの位相特性（Phase）

%%%　振幅特性　%%%
figure; axis on;
subplot(2,1,1); plot(A_x);
axis([0 2*N 0 100]); title('Amplitude (INPUT)'); xlabel('n'); ylabel('A(ω)');
subplot(2,1,2); plot(A_y);
axis([0 2*N 0 100]); title('Amplitude (OUTPUT)'); xlabel('n'); ylabel('A(ω)');

%%%　位相特性　%%%
figure; axis on;
subplot(2,1,1); plot(P_x);
axis([0 2*N -100 2]); title('Phase (INPUT)'); xlabel('n'); ylabel('θ(ω)');
subplot(2,1,2); plot(P_y);
axis([0 2*N -100 2]); title('Phase (OUTPUT)'); xlabel('n'); ylabel('θ(ω)');

%%%　時間領域での入力信号と出力信号　%%%
figure; axis on;
subplot(2,1,1); plot(x);
axis([0 2*N -5 5]); title('Time-Domain Wave (INPUT)'); xlabel('n'); ylabel('x(n)');
subplot(2,1,2); plot(y);
axis([0 2*N -5 5]); title('Time-Domain Wave (OUTPUT)'); xlabel('n'); ylabel('y(n)');