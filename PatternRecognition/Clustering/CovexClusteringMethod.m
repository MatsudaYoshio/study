clear all; close all;

n = 500;
%mu = [-3 3; 2 4; 0 0; -2 -4; 3 -2];
%sigma = cat(3,[0.8 0; 0 0.48],[0.5 0; 0 0.7],[0.5 0; 0 0.5],[1.2 1; 1 1.8],[0.4 0; 0 0.2]);
mu = [-4 4; 4 4; 0 0; -4 -4; 4 -4];
sigma = cat(3, eye(2), eye(2), eye(2), eye(2), eye(2));
pi = [0.4 0.2 0.2 0.1 0.1];
ite = 10000;

s = sample(pi,n);
x = mvnrnd(mu(s,:),sigma(:,:,s));
figure;
plot(x(:,1),x(:,2),'.');

x1 = -7:0.1:7;
x2 = x1;
X2 = meshgrid(x1);
X1 = X2.';
N = size(x1,2);
Z = zeros(N,N);

for i = 1:length(mu)
    for j = 1:N
        for k = 1:N
                Z(j,k) = mvnpdf([x1(j) x2(k)],mu(i,:),sigma(:,:,i));
        end
    end
    hold on;
    contour(X1,X2,Z,2,'LevelList',[0.02],'LineWidth',15*pi(i),'LineColor','r');
end

pi_init = ones(1,n)/n;
pi = pi_init;
pi_hat = pi;
sigma = eye(2);
f = zeros(n,n);
pif = zeros(n,n);
pif_sum = zeros(1,n);
logP = 0;

for i = 1:n
    for j = 1:i
        f(i,j) = mvnpdf(x(i,:),x(j,:),sigma);
    end
end

for i = 1:n
    for j = 1:i-1
        f(j,i) = f(i,j);
    end
end

th = 0.001;

for t = 1:ite
    th = th + 0.00001;
    
    for i = 1:n
        pif(i,:) = pi(i)*f(i,:);
    end

    pif_sum = sum(pif);

    for i = 1:n
        s = 0;
        for k = 1:n
            s = s + pif(i,k)/pif_sum(k);
        end
        pi_hat(i) = s/n;
    end
    
    pi_hat = pi_hat.*(pi_hat > th);
    pi_sum = sum(pi_hat);
    pi_hat = pi_hat / pi_sum;
    
    if(rem(t,1000) == 0)
        figure;
        plot(x(:,1),x(:,2),'.');
        for i = 1:n
            if(pi_hat(i) == 0)
                continue;
            end
            Z = zeros(N,N);
            for j = 1:N
                for k = 1:N
                    Z(j,k) = mvnpdf([x1(j) x2(k)],x(i,:),sigma);
                end
            end
            hold on;
            contour(X1,X2,Z,2,'LevelList',[0.02],'LineWidth',15*pi_hat(i),'LineColor','r');
        end
    end
    
    logP_hat = sum(log(pif_sum));
    
    if(abs(logP_hat-logP) < 0.000000001)
        break;
    end
    
    logP = logP_hat;
    pi = pi_hat;
end