function [R,C,c_min,r_min] = reliabilityMoutofN(M,N)
R = zeros;
C = zeros;
for p=0.8:0.1:1
    for n=3:1:N
        acc=0;
        for i=0:n-M
            acc = acc + nchoosek(n,i)*(p^(n-i))*((1-p)^i);
        end
        R(n-2,p*10-7) = acc;
        if(p==0.8)
            C(n-2,p*10-7) = 1000*n;
        end
        if(p==0.9)
            C(n-2,p*10-7) = 1500*n;
        end
        if(p==1)
            C(n-2,p*10-7) = 2000*n;
        end
    end
end
c_min = min(C(R>0.99&R<1.0));
r_min = R(C==min(C(R>0.99&R<1.0)));
end

