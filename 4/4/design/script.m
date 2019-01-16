clc;
clear;
R = zeros;
C = zeros;
for p=0.8:0.1:1
    for N=3:1:8
        acc=0;
        for i=0:N-3
            acc = acc + nchoosek(N,i)*(p^(N-i))*((1-p)^i);
        end
        R(N-2,p*10-7) = acc;
        if(p==0.8)
            C(N-2,p*10-7) = 1000*N;
        end
        if(p==0.9)
            C(N-2,p*10-7) = 1500*N;
        end
        if(p==1)
            C(N-2,p*10-7) = 2000*N;
        end
    end
end
reliability_min=R(C==min(C(R>0.99&R<1.0)));
