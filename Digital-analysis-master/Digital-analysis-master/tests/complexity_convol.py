import matplotlib.pyplot as plt
from pylab import linspace, meshgrid
import numpy as np
from mpl_toolkits.mplot3d.axes3d import Axes3D
from matplotlib import cm

def fic_to_tab(fichier):
    fichier = "/home/T/TMP-Moins/Digital-analysis/build/tests/" + fichier
    fic = open(fichier, "r")
    tab_n = []
    tab_m = []
    tab_t1 = []
    tab_t2 = []
    tab_n = np.array(tab_n)
    tab_m = np.array(tab_m)
    tab_t1 = np.array(tab_t1)
    tab_t2 = np.array(tab_t2)
    for line in fic.readlines():
        tmp = line.split()
        if tmp != []:
            tab_n = np.append(tab_n, [int(tmp[0])])
            tab_m = np.append(tab_m, [int(tmp[1])])
            tab_t1 = np.append(tab_t1, [float(tmp[2])])
            tab_t2 = np.append(tab_t2, [float(tmp[3])])
    fic.close()
    return tab_n, tab_m, tab_t1, tab_t2
    
def fic_to_tab_square(fichier):
    fichier = "/home/T/TMP-Moins/Digital-analysis/build/" + fichier
    fic = open(fichier, "r")
    tab_n = []
    tab_t1 = []
    tab_t2 = []
    tab_n = np.array(tab_n)
    tab_t1 = np.array(tab_t1)
    tab_t2 = np.array(tab_t2)
    for line in fic.readlines():
        tmp = line.split()
        if tmp != []:
            if int(tmp[0])==int(tmp[1]):
                tab_n = np.append(tab_n, [int(tmp[0])])
                tab_t1 = np.append(tab_t1, [float(tmp[2])*10**7])
                tab_t2 = np.append(tab_t2, [float(tmp[3])*10**7])
    fic.close()
    return tab_n, tab_t1, tab_t2

def plot_3D(n,m,t):
    X,Y = meshgrid(n, m)
    Z = t.T
    
    fig = plt.figure(figsize=(14,6))
    
    # `ax` is a 3D-aware axis instance, because of the projection='3d' keyword argument to add_subplot
    ax = fig.add_subplot(1, 2, 1, projection='3d')
    
#    for i in range(0,360,10):
    ax.view_init(20, 20)
    p = ax.plot_surface(X, Y, Z, rstride=4, cstride=4, linewidth=0, cmap=cm.coolwarm)
    
    fig.colorbar(p, shrink=0.5, aspect=10)

#n,m,t1,t2 = fic_to_tab("kernel3.txt")
#plot_3D(n,m,t1-t2)


n,t1,t2 = fic_to_tab_square("kernel3.txt")
#y1 = 15*15*n*n/100000000
#y2 = (6*n*np.log(2*n)+n*n)/10000000
p1, = plt.plot(np.log(n),np.log(t1))
p2, = plt.plot(np.log(n),np.log(t2))
n2 = [i for i in range(16,5000)]
#n3 = [i*i*np.log(i) for i in n2]
#n4 = [i*i for i in n2]
#p4, = plt.plot(np.log2(n2),np.log2(n3))
#p5, = plt.plot(np.log2(n2),np.log2(n4))
plt.title("Logarithmic scale : kernel of size 3")
plt.legend([p1, p2], ["Naive", "FFT"], loc = "best")
plt.ylabel("Number of computations (log2)")
plt.xlabel("Matrix dimension (log2)")
plt.show()

