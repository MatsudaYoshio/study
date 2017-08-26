clear all; close all;                            % ������

N = 100;                                         % �t�B���^�̎����i�t�B���^���j
omega_c = pi / 4;                                % �J�b�g�I�t���g���i�Ւf���g���j

n = 1 : 2*N+1;                                   % n�͈̔͂��C���͈̔͂ɃV�t�g����   

%%%%�@���֐���p���Ȃ��@���[�p�X�t�B���^�@%%%%
h_c(n) = (1 ./ (pi .* (n-(N+1)))) .* sin(omega_c .* (n-(N+1)));
                                                 % ���[�p�X�t�B���^�̃C���p���X����
h_c(N+1) = omega_c / pi;                         % n = N+1 �̂Ƃ���ɒl������

%%%%�@���֐���p�����@���[�p�X�t�B���^�@%%%%
%w(n) = 0.54 + 0.46 .* cos((n-(N+1)).*pi./N);     % ���֐��̒�`�i�n�~���O���̏ꍇ�j
w(n) = 0.42 + 0.5 .* cos((n-(N+1)).*pi./N) + 0.08 .* cos(2.*(n-(N+1)).*pi./N);
                                                 % ���֐��̒�`�i�u���b�N�}�����̏ꍇ�j
h_cw = w .* h_c;                                 % ���֐����|�����킹���t�B���^�W��
T_cw = fft(h_cw);                                % �t�B���^�̎��g�������iFFT�j
A_cw = abs(T_cw);                                % �U�������iAmplitude�j
P_cw = unwrap(atan2(imag(T_cw),real(T_cw)));     % �ʑ������iPhase�j

%%%�@���g�������̕\���@%%%
figure; axis on;
subplot(2,1,1); plot(A_cw);
axis([0 N 0 1.5]); title('Amplitude'); xlabel('n'); ylabel('A(��)');

subplot(2,1,2); plot(P_cw);
axis([0 N -90 2]); title('Phase'); xlabel('n'); ylabel('��(��)');