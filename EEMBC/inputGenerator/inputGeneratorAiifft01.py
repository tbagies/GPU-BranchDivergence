import random
fw = open("out.txt","w")
counter =0
fw.writelines("i ")
for i in range(1024):
#for line in f.readlines():
        while counter<1024:
		num = random.randint(-10437, 16369)
		fw.writelines(str(num) + " ")
		counter +=1
        	#fw.writelines("f " + line.rstrip('\n'))
	fw.writelines("\ni ") 
	counter=0
		#fw.write(line)
	#counter +=1
fw.close()
