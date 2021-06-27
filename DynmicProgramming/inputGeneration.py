import random

num = int(input('How many random numbers?: '))
fileName = "inputFile" + str(num) + ".txt"
afile = open(fileName, "w" )
for i in range(64):
    n = random.randint(2,1000)
    k = random.randint(0,n-2)
    afile.write('c ' + str(n) + " " + str(k))
    afile.write("\n")
    afile.write('m ' + str(n))
    for j in range(n):
    	r = str(random.randint(2,1000))
    	afile.write(" " + r)
    afile.write("\n")
    afile.write('f ' + str(n))
    afile.write("\n")
    afile.write('k ' + str(n))
    for j in range(n):
        r = str(random.randint(2,1000))
        afile.write(" " + r)
    afile.write("\n")
    afile.write('n ' + str(n) + " " + str(k))
    for j in range(n):
        r = str(random.randint(2,1000))
        afile.write(" " + r)
    for j in range(n):
        r = str(random.randint(2,1000))
        afile.write(" " + r)
    afile.write("\n")
    afile.write('s ' + str(n) + " " + str(k))
    for j in range(n):
        r = str(random.randint(2,1000))
        afile.write(" " + r)
    afile.write("\n")
    afile.write('l ' + str(n) + " " + str(k))
    for j in range(n):
        r = random.choice('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ')
        afile.write(" " + r)
    for j in range(k):
        r = random.choice('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ')
        afile.write(" " + r)
    afile.write("\n")
    afile.write('e ' + str(n) + " " + str(k))
    for j in range(n):
        r = random.choice('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ')
        afile.write(" " + r)
    for j in range(k):
        r = random.choice('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ')
        afile.write(" " + r)
    afile.write("\n")
    afile.write('g ' + str(n) + " " + str(k))
    afile.write("\n")
    afile.write('o ' + str(n))
    for j in range(n):
        r = str(random.randint(2,1000))
        afile.write(" " + r)
    afile.write("\n")
    afile.write('i ' + str(n))
    for j in range(n):
        r = str(random.randint(2,1000))
        afile.write(" " + r)
    afile.write("\n")
for i in range(32):
    n = random.randint(5,1000)
    k = random.randint(5,1000)
    afile.write('c ' + str(n) + " " + str(k))
    afile.write("\n")
    afile.write('m ' + str(n))
    for j in range(n):
        r = str(random.randint(2,1000))
        afile.write(" " + r)
    afile.write("\n")
    afile.write('f ' + str(n))
    afile.write("\n")
    afile.write('k ' + str(n))
    for j in range(n):
        r = str(random.randint(2,1000))
        afile.write(" " + r)
    afile.write("\n")
    afile.write('n ' + str(n) + " " + str(k))
    for j in range(n):
        r = str(random.randint(2,1000))
        afile.write(" " + r)
    for j in range(n):
        r = str(random.randint(2,1000))
        afile.write(" " + r)
    afile.write("\n")
    afile.write('s ' + str(n) + " " + str(k))
    for j in range(n):
        r = str(random.randint(2,1000))
        afile.write(" " + r)
    afile.write("\n")
    afile.write('l ' + str(n) + " " + str(k))
    for j in range(n):
        r = random.choice('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ')
        afile.write(" " + r)
    for j in range(k):
        r = random.choice('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ')
        afile.write(" " + r)
    afile.write("\n")
    afile.write('e ' + str(n) + " " + str(k))
    for j in range(n):
        r = random.choice('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ')
        afile.write(" " + r)
    for j in range(k):
        r = random.choice('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ')
        afile.write(" " + r)
    afile.write("\n")
    afile.write('g ' + str(n) + " " + str(k))
    afile.write("\n")
    afile.write('o ' + str(n))
    for j in range(n):
        r = str(random.randint(2,1000))
        afile.write(" " + r)
    afile.write("\n")
