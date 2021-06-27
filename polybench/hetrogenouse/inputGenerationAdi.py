import random

num = int(input('How many random numbers?: '))
fileName = "inputFile" + str(num) + ".txt"
afile = open(fileName, "w" )
for i in range(500):
    M=str(random.randint(5,32))
    s=str(2)
    afile.write(M + " " + s)
    afile.write("\n")
for i in range(500):
    M=str(random.randint(250,500))
    s=str(random.randint(2,10))
    afile.write(M + " " + s)
    afile.write("\n")
for i in range(13):
    M=str(random.randint(501,1024))
    s=str(random.randint(11,50))
    afile.write(M + " " + s)
    afile.write("\n")
for i in range(10):
    M=str(random.randint(1024,2000))
    s=str(random.randint(2,50))
    afile.write(M + " " + s)
    afile.write("\n")
afile.write("4000 100")
afile.write("\n")
afile.close()
