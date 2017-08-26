function i = sample(p,n)
    i = 1 + sum(bsxfun(@gt, rand(n, 1), cumsum(p) / sum(p)), 2)';
end
