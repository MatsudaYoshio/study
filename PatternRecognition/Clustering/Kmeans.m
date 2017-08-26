clear all; close all;

n = 500;
mu = [-3 3; 2 4; 0 0; -2 -4; 3 -2];
sigma = cat(3,[0.8 0; 0 0.48],[0.5 0; 0 0.7],[0.5 0; 0 0.5],[1.2 1; 1 1.8],[0.4 0; 0 0.2]);
pi = [0.4 0.2 0.2 0.1 0.1];
p = [-4 -6; 0 0; 0 -2; 2 0; 4 2];
p_hat = p;
c = length(pi);
qe = [];
ite = 20;

s = sample(pi,n);
x = mvnrnd(mu(s,:),sigma(:,:,s));
figure;
plot(x(:,1),x(:,2),'.');
hold on;
plot(p(:,1),p(:,2),'or');

for t = 1:ite
    delta = zeros(n,c);
    e = pdist2(x,p);
    [min_val, min_index] = min(e,[],2);
    
    for i = 1:n
        delta(i,min_index(i)) = 1;
    end
    
    qe = [qe; sum(sum(e.*delta))];

    for i = 1:c
        y = [];
        for j = 1:length(x(1,:))
            y = [y delta(:,i).*x(:,j)];
        end
        p(i,:) = sum(y)./sum(y ~= 0);
    end
    
    if(t == 2 || t == 3 || t == 6 || t == 9)
        figure;
        plot(x(:,1),x(:,2),'.');
        hold on;
        plot(p(:,1),p(:,2),'or');
    end
    
    if(p == p_hat)
        break;
    end
    p_hat = p;
end

figure;
plot(qe);