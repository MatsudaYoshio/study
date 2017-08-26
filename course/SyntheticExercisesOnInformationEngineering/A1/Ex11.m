clear all; close all;                            % ������

N = 100;                                         % �t�B���^�̎����i�t�B���^���j
omega_c = pi / 4;                                % �J�b�g�I�t���g���i�Ւf���g���j

n = 1 : 2*N+1;                                   % n�͈̔͂��C���͈̔͂ɃV�t�g����   

h_c(n) = (1 ./ (pi .* (n-(N+1)))) .* sin(omega_c .* (n-(N+1)));
                                                 % ���[�p�X�t�B���^�̃C���p���X����
h_c(N+1) = omega_c / pi;                         % n = N+1 �̂Ƃ���ɒl������
T_c = fft(h_c);                                  % �t�B���^�̎��g�������iFFT�j
A_c = abs(T_c);                                  % �U�������iAmplitude�j
P_c = unwrap(atan2(imag(T_c),real(T_c)));        % �ʑ������iPhase�j

%%%�@���g�������̕\���@%%%
figure; axis on;
subplot(2,1,1); plot(A_c);
axis([0 N 0 1.5]); title('Amplitude'); xlabel('n'); ylabel('A(��)');

subplot(2,1,2); plot(P_c);
axis([0 N -80 2]); title('Phase'); xlabel('n'); ylabel('��(��)');