from itertools import izip_longest

file_list = ['a2timeInputFile.txt','rspeedInputFile.txt', 'aifftr01InputFile.txt', 'aiifft01InputFile.txt', 'idctrn01InputFile.txt', 'puwmod01InputFile.txt', 'tblook01InputFile.txt']
files = [open(filename) for filename in file_list]
fw = open("out.txt","w")
counter=0
for lines in izip_longest(*files, fillvalue=''):
	if counter == 896:
		break
	counter +=7
	fw.write("".join(lines))
fw.close()
