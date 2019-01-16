function [R,C,c_min,r_min] = reliabilityFunction(M,N)
R = zeros;
C = zeros;
p=[0.80, 0.88, 0.96];
for j=1:3
    for n=3:1:N
        acc=0;
        for i=0:n-M
            acc = acc + nchoosek(n,i)*(p(j)^(n-i))*((1-p(j))^i);
        end
        R(n-2,j) = acc;
        if(abs(p(j)-0.80)<eps)
            C(n-2,j) = 1000*n;
        end
        if(abs(p(j)-0.88)<eps)
            C(n-2,j) = 1500*n;
        end
        if(abs(p(j)-0.96)<eps)
            C(n-2,j) = 2000*n;
        end
    end
end
c_min = min(C(R>0.99));
r_min = R(C==min(C(R>0.99)));
end

