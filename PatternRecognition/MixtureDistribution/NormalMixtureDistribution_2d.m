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

x1 = -7:0.1:7;
x2 = x1;
X2 = meshgrid(x1);
X1 = X2.';
N = size(x1,2);

for i = 1:c
    for j = 1:N
        for k = 1:N
                Z(j,k) = mvnpdf([x1(j) x2(k)],mu(i,:),sigma(:,:,i));
        end
    end
    hold on;
    contour(X1,X2,Z,2,'LevelList',[0.02],'LineWidth',15*pi(i),'LineColor','r');
end

mu_init = [-4 0; -2 0; 0 0; 2 0; 4 0];
mu = mu_init;
pi_init = ones(1,c).*0.2;
pi = pi_init;
pi_num = pi;
for i = 1:c
    sigma_init(:,:,i) = eye(2);
end
sigma = sigma_init;
logP = 0;
logP_num = [];
ite = 50;

for t = 1:ite
    for i = 1:n
        for j = 1:c
            p(i,j) = mvnpdf(x(i,:),mu(j,:),sigma(:,:,j));
        end
    end
    
    for i = 1:n
        for j = 1:c
            P(i,j) = pi(j)*p(i,j)/dot(p(i,:),pi.');
        end
    end
    
    for i = 1:c
        mu_hat(i,:) = (P(:,i).'*x)./sum(P(:,i));
    end
    
    for i = 1:c
        pi_hat(1,i) = sum(P(:,i))/n;
    end
    
    for i = 1:c
        d = zeros(2);
        for j = 1:n
            d = d + P(j,i)*((x(j,:)-mu_hat(i,:)).')*(x(j,:)-mu_hat(i,:));
        end
        sigma_hat(:,:,i) = d./sum(P(:,i));
    end
    
    if(t == 1 || t == 2 || t == 4 || t == 10)
        figure;
        plot(x(:,1),x(:,2),'.');
        for i = 1:c
            for j = 1:N
                for k = 1:N
                    Z(j,k) = mvnpdf([x1(j) x2(k)],mu(i,:),sigma(:,:,i));
                end
            end
            hold on;
            contour(X1,X2,Z,2,'LevelList',[0.02],'LineWidth',15*pi_hat(i),'LineColor','r');
        end
    end
    logP_hat = sum(log(p*pi.'));
    if(abs(logP_hat-logP) < 0.00001) break; end
    logP = logP_hat;
    logP_num = [logP_num; logP];
    mu = mu_hat;
    pi = pi_hat;
    pi_num = [pi_num; pi];
    sigma = sigma_hat;
end

figure;
plot(x(:,1),x(:,2),'.');

for i = 1:c
    for j = 1:N
        for k = 1:N
            Z(j,k) = mvnpdf([x1(j) x2(k)],mu(i,:),sigma(:,:,i));
        end
    end
    hold on;
    contour(X1,X2,Z,2,'LevelList',[0.02],'LineWidth',15*pi(i),'LineColor','r');
end

figure;
plot(logP_num);

figure;
for i = 1:c
    hold on;
    plot(pi_num(:,i).');
end