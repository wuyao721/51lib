import math
#for i in range(1, 100):
for i in range(100000, 999999):
    root = int(math.sqrt(i));
    flag = True
    for j in range(2, root+1):
        if i % j == 0:
            flag = False
            break
    if flag:
        print i
