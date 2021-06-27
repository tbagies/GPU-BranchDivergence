import random

num = int(input('How many random numbers?: '))
fileName = "inputFile" + str(num) + ".txt"
afile = open(fileName, "w" )
for i in range(74):
    M=str(random.randint(5,39))
    N = str(random.randint(5,43))
    afile.write(M + " " + N)
    afile.write("\n")

for i in range(100):
    M=str(random.randint(39,117))
    N = str(random.randint(43,125))
    afile.write(M + " " + N)
    afile.write("\n")

for i in range(100):
    M=str(random.randint(117,391))
    N = str(random.randint(125,411))
    afile.write(M + " " + N)
    afile.write("\n")

for i in range(400):
    M=str(random.randint(391,1901))
    N = str(random.randint(411,2101))
    afile.write(M + " " + N)
    afile.write("\n")
i=0
for i in range(350):
    M=str(random.randint(1800,1901))
    N = str(random.randint(2101,2200))
    afile.write(M + " " + N)
    afile.write("\n")
afile.close()
