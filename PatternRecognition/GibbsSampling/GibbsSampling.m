clear; close all;

n = 400;
a = 0.6;
mu = zeros(1,2);
sigma = [1 a; a 1]./sqrt(1-a^2);
x_init = [5 -5];
x = x_init;

figure;
plot(x(:,1),x(:,2),'ro');

x1 = -6:0.1:6;
x2 = x1;
X2 = meshgrid(x1);
X1 = X2.';
N = size(x1,2);
Z = zeros(N);
for i = 1:N
    for j = 1:N
        Z(i,j) = mvnpdf([x1(i) x2(j)],mu,sigma);
    end
end
hold on;
contour(X1,X2,Z);

sigma = ones(1);
for i = 1:n
    if(rem(i,2) == 1)
        x(1) = normrnd(a*x(2),sigma);
    else
        x(2) = normrnd(a*x(1),sigma);
    end
    hold on;
    plot(x(:,1),x(:,2),'ro');
end