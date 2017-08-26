clear; close all;

n = 500;
mu = [3 -1];
sigma = [1 1];
pi = [0.6 0.4];

s = sample(pi,n);
x = mvnrnd(mu(s),sigma(s));
figure;
histogram(x,-4:0.25:7+0.125);

mu_init = [-2 -3];
mu = mu_init;
mu_num = [mu;];
logP = 0;
ite = 100;

for t = 1:ite
    for i = 1:n
        p(i,:) = normpdf(x(i),mu,sigma);
    end

    for i = 1:n
        for j = 1:length(pi)
            P(i,j) = pi(j)*p(i,j)/dot(p(i,:),pi.');
        end
    end
    
    mu_hat = x*P./sum(P);
    logP_hat = sum(p*pi.');
    if(logP_hat-logP < 0.000000001) break; end
    logP = logP_hat;
    mu = mu_hat;
    mu_num = [mu_num; mu];
end

figure;
plot(mu_num);