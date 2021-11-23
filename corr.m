m = readmatrix('..\output.csv'); %Monto minha matriz a partir dos dados fornecidos pelo script python
[M N] = size(m);
k1 = 1:M;
r = xcorr(2*k1-1)
plot(r)