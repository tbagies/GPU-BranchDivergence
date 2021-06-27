f=open("aifftr01InputFile.txt", "r")
numbers = [int(w) for w in f.read().split()]
#f.close()
fw = open("out.txt","w")
counter =0
for i in numbers:
#for line in f.readlines():
        if counter<1024:
		fw.writelines(str(i) + " " )
		counter +=1
        	#fw.writelines("f " + line.rstrip('\n'))
	else:
		fw.writelines("\nf ") 
		counter=0
		#fw.write(line)
	#counter +=1
f.close()
fw.close()
