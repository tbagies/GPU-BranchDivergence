import random

num = int(input('How many random numbers?: '))
fileName = "inputFile" + str(num) + ".txt"
afile = open(fileName, "w" )
for i in range(1024/2):
    M=str(random.randint(5,1901))
    N = str(random.randint(5,2200))
    afile.write('1 ' + M + " " + N)
    afile.write("\n")
    M=str(random.randint(5,2000))
    s = str(random.randint(5,50))
    afile.write('0 ' + M + " " + s)
    afile.write("\n")

afile.close()
