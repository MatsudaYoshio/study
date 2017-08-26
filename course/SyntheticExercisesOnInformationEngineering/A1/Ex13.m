clear all; close all;                           % ������

N = 100;                                        % �t�B���^�̎����i�t�B���^���j
omega_c = pi / 4;                               % �J�b�g�I�t���g���i�Ւf���g���j

n = 1 : 2*N+1;                                  % n�͈̔͂��C���͈̔͂ɃV�t�g����   

h_c(n) = (1 ./ (pi .* (n-(N+1)))) .* sin(omega_c .* (n-(N+1)));
                                                % ���[�p�X�t�B���^�̃C���p���X����
h_c(N+1) = omega_c / pi;                        % n = N+1 �̂Ƃ���ɒl������
T_c = fft(h_c);                                 % �t�B���^�̎��g�������iFFT�j
A_c = abs(T_c);                                 % �U�������iAmplitude�j
P_c = unwrap(atan2(imag(T_c),real(T_c)));       % �ʑ������iPhase�j


x(n) = 2.0 .* sin(pi/6 .* n) + 2.0 .* sin(pi/4 .* n) + sin(pi/2 .* n) + sin(pi/1.5 .* n);
                                                % ���������g�M���𐶐�
y = filter(x, 1, h_c);                          % ���͐M��x�̃t�B���^�����O

M_x = length(x); M_y = length(y);               % ��������f�[�^��
T_x = fft(x, 2*M_x);                            % ���͐M��x��FFT
A_x = abs(T_x);                                 % x�̐U�������iAmplitude�j
P_x = unwrap(atan2(imag(T_x),real(T_x)));       % x�̈ʑ������iPhase�j
T_y = fft(y, 2*M_y);                            % �o�͐M��y��FFT
A_y = abs(T_y);                                 % y�̐U�������iAmplitude�j
P_y = unwrap(atan2(imag(T_y),real(T_y)));       % y�̈ʑ������iPhase�j

%%%�@�U�������@%%%
figure; axis on;
subplot(2,1,1); plot(A_x);
axis([0 2*N 0 100]); title('Amplitude (INPUT)'); xlabel('n'); ylabel('A(��)');
subplot(2,1,2); plot(A_y);
axis([0 2*N 0 100]); title('Amplitude (OUTPUT)'); xlabel('n'); ylabel('A(��)');

%%%�@�ʑ������@%%%
figure; axis on;
subplot(2,1,1); plot(P_x);
axis([0 2*N -100 2]); title('Phase (INPUT)'); xlabel('n'); ylabel('��(��)');
subplot(2,1,2); plot(P_y);
axis([0 2*N -100 2]); title('Phase (OUTPUT)'); xlabel('n'); ylabel('��(��)');

%%%�@���ԗ̈�ł̓��͐M���Əo�͐M���@%%%
figure; axis on;
subplot(2,1,1); plot(x);
axis([0 2*N -5 5]); title('Time-Domain Wave (INPUT)'); xlabel('n'); ylabel('x(n)');
subplot(2,1,2); plot(y);
axis([0 2*N -5 5]); title('Time-Domain Wave (OUTPUT)'); xlabel('n'); ylabel('y(n)');