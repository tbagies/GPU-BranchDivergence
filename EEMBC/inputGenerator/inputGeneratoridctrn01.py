f = open("idctrn01InputFile.txt","r")
Numbers = [[int(n) for n in line.split()] for line in f.readlines()]
fw = open("idctrn01out.txt","w")
counter = 0
for i in Numbers:
        if counter % 16 ==0:
		fw.writelines("\nd " + str(i) + " ")
		counter =0
	else:
		fw.writelines(str(i) + " ")
	counter +=1

