import random


size = 1024 #input('Input size ')
fileName = "inputFile1024.txt"# + str(size) + ".txt"
fileWriter = open(fileName,'a')
arr =[]
for j in range(128):
        arr = []
        length = random.randint(1000,10000)
        for i in range(length):
                arr.append(random.randint(1,10000))
	action = 'b'
	fileWriter.write(str(length) + " " + action + " ")
	for item in arr:
        	fileWriter.write("%s " % item)
        fileWriter.write("\n")
        action = 'q'
        fileWriter.write(str(length) + " " + action + " ")
	for item in arr:
                fileWriter.write("%s " % item)
	fileWriter.write("\n")
	action = 'm'
        fileWriter.write(str(length) + " " + action + " ")
        for item in arr:
                fileWriter.write("%s " % item)
        fileWriter.write("\n")
	action = 'o'
        fileWriter.write(str(length) + " " + action + " ")
        for item in arr:
                fileWriter.write("%s " % item)
        fileWriter.write("\n")

	action = 'c'
        fileWriter.write(str(length) + " " + action + " ")
        for item in arr:
                fileWriter.write("%s " % item)
        fileWriter.write("\n")
	action = 's'
        fileWriter.write(str(length) + " " + action + " ")
        for item in arr:
                fileWriter.write("%s " % item)
        fileWriter.write("\n")
	action = 'g'
        fileWriter.write(str(length) + " " + action + " ")
        for item in arr:
                fileWriter.write("%s " % item)
        fileWriter.write("\n")
 	action = 'i'
        fileWriter.write(str(length) + " " + action + " ")
        for item in arr:
                fileWriter.write("%s " % item)
        fileWriter.write("\n")
