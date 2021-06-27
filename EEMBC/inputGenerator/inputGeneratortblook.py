import random
f = open("tblook01GetValue.txt","r")
#Numbers = [[int(n) for n in line.split()] for line in f.read()]
#f.close()
counter =0
fw = open("tblook01InputFile.txt","w")
for val in f.read().split():
	if counter % 2 ==0:
               fw.writelines("\nt " + val + " ")
	
	else:
		fw.writelines(val + " ")
	counter +=1
f.close()
for i in range(1024):
	fw.writelines("\nt " + str(random.randint(0,9999)) + " " + str(random.randint(0,9999)))
fw.close()

