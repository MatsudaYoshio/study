clear; close all;

n = 500;
mu = [-3 3; 2 4; 0 0; -2 -4; 3 -2];
sigma = cat(3,[0.8 0; 0 0.48],[0.5 0; 0 0.7],[0.5 0; 0 0.5],[1.2 1; 1 1.8],[0.4 0; 0 0.2]);
pi = [0.4 0.2 0.2 0.1 0.1];
c = length(pi);

s = sample(pi,n);
x = mvnrnd(mu(s,:),sigma(:,:,s));
figure;
plot(x(:,1),x(:,2),'.');
title('Random sampling');

x1 = -7:0.1:7;
x2 = x1;
X2 = meshgrid(x1);
X1 = X2.';
N = size(x1,2);
Z = zeros(N,N);

for i = 1:c
    for j = 1:N
        for k = 1:N
            Z(j,k) = mvnpdf([x1(j) x2(k)],mu(i,:),sigma(:,:,i));
        end
    end
    hold on;
    contour(X1,X2,Z,2,'LevelList',0.02,'LineWidth',15*pi(i),'LineColor','r');
end

clearvars pi;

alpha = 1.0;
beta = 1/3;
nu = 15;
S = [0.1 0; 0 0.1];
mu0 = mean(x);
mu = mu0;
lambda = inv(cov(x));
m = n;
c = 1;
s = ones(n,1);
d = length(mu);
P_max = 0;
ite = 200;
log_v = zeros(ite,1);
c_num = zeros(ite,1);

for t = 1:ite
    
    for i = 1:n
        m(s(i)) = m(s(i)) - 1;
        if(m(s(i)) == 0)
            s(s > s(i)) = s(s > s(i)) - 1;
            c = c - 1;
            m(s(i)) = [];
            mu(s(i),:) = [];
            lambda(:,:,s(i)) = [];
        end
        
        p_max = -1;
        p = zeros(1,c);
        for j = 1:c
            p(j) = (m(j)/(n-1+alpha))*mvnpdf(x(i,:),mu(j,:),inv(lambda(:,:,j)));
        end
    
        S_b = inv( inv(S) + (beta/(1+beta)) .* (((x(i,:)-mu0).')*(x(i,:)-mu0)) );
        Nu = (det(S_b).^((nu+1)/2))*(gamma((nu+1)/2));
        De = (det(S).^(nu/2))*gamma((nu+1-d)/2);
        p(c+1) = (alpha/(n-1+alpha))*((beta/((1+beta)*pi)).^(d/2))*Nu/De;
        
        p = p ./ sum(p);
        
        omega = sample(p,1);
        if(omega == c+1)
            s(i) = c+1;
            c = c + 1;
            m(s(i)) = 1;
        else
            s(i) = omega;
            m(s(i)) = m(s(i)) + 1;
        end
        
        for j = 1:c
            nu_c = nu + m(j);
            x_k = x(s == j,:);
            x_bar = mean(x_k,1);
            [r,d] = size(x_k);
            x_bar_rep = repmat(x_bar,r,1);
            mu_c = (m(j).*x_bar+beta.*mu0)./(m(j)+beta);
            S_q_inv = inv(S) + ((x_k-x_bar_rep).')*(x_k-x_bar_rep) + (m(j)*beta/(m(j)+beta)).*(((x_bar-mu0).')*(x_bar-mu0));
            lambda(:,:,j) = wishrnd(inv(S_q_inv),nu_c);
            lambda_c = (m(j)+beta).*lambda(:,:,j);
            mu(j,:) = mvnrnd(mu_c,inv(lambda_c));
        end
        
    end
    
    r = m ./ sum(m);
    if(rem(t,50) == 0)
        figure;
        plot(x(:,1),x(:,2),'.');
        title(strcat('iteration = ',num2str(t)));
        
        for i = 1:c
            for j = 1:N
                for k = 1:N
                    Z(j,k) = mvnpdf([x1(j) x2(k)],mu(i,:),inv(lambda(:,:,i)));
                end
            end
            hold on;
            contour(X1,X2,Z,2,'LevelList',0.02,'LineWidth',15*r(i),'LineColor','r');
        end        
    end
    
    c_num(t) = c;
    
    log_v(t) = c*log(alpha);
    for i = 1:c
        log_v(t) = log_v(t) + sum(log(1:m(i)-1)) + log(mvnpdf(mu(i,:),mu0,inv(beta.*lambda(:,:,i))));
        y = x(s==i,:);
        for j = 1:m(i)
            log_v(t) = log_v(t) + log(mvnpdf(y(j,:),mu(i,:),inv(lambda(:,:,i))));
        end
    end
    log_v(t) = log_v(t) - sum(log(alpha+(1:n)-1));
    
end

figure;
plot(1:ite,log_v);
xlabel('iteration');
ylabel('log(v)');

figure;
plot(1:ite,c_num);
xlabel('iteration');
ylabel('c');