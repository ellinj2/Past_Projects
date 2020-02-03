import numpy as np

np.random.seed(444)

N=10000
sigma = 0.1
noise = sigma * np.random.randn(N)
x=np.linspace(0,2,N)
d=3+2*x+noise
d.shape=(N,1)

X=np.column_stack((np.ones(N,dtype=x.dtype),x))
print(X.shape)
#(10000,2)

Xplus=np.linalg.pinv(X)
w_opt=Xplus@d
print(w_opt)
#[[2.99536719],
 #[2.00288672]]
