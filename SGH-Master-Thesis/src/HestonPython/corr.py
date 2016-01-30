import numpy as np
#import Image
import matplotlib.pyplot as plt
import matplotlib.pyplot as plt
import scipy.stats as stats
linalg = np.linalg

np.random.seed(1)

num_samples = 100
num_variables = 2
cov = [[1.0, 0.2], [0.2, 1.0]]

L = linalg.cholesky(cov)

#rhos = []
uncorrelated = np.random.standard_normal((num_variables, num_samples))
correlated = np.dot(L, uncorrelated)
X, Y = correlated
    #rho, pval = stats.pearsonr(X, Y)
    #rhos.append(rho)


plt.plot(X)
plt.plot(Y)
plt.savefig('corr.png')
#Image.open('testplot.png').save('testplot.jpg','JPEG')
#plt.show()

#plt.hist(rhos)
#plt.show()
