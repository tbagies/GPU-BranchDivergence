import glob
import random
import networkx as nx

size = 1024 #input('Input size ')
fileName = "inputFile1024.txt"# + str(size) + ".txt"
fileWriter = open(fileName,'a')
for k in range(64):
	n = random.randint(10,1000)
        orintation = str(1)
	v = str(random.randint(0,(n-1)))
	e = random.randint(8,n)
	action = 'b'
        fileWriter.write(action + " " + str(n) + " " + orintation + " " + v)
	g = nx.gnm_random_graph(n,e, None, orintation)
	for i in range(0,n):
		for j in range (0,n):
			if g.get_edge_data(i,j) != None:
				e=str(random.randint(0,10000))
				fileWriter.write(" " + str(e))	
			else:
				fileWriter.write(" 0")
        fileWriter.write("\n")
	action = 'i'
	fileWriter.write(action + " " + str(n) + " " + orintation + " " + v)
	for i in range(0,n):
                for j in range (0,n):
			if g.get_edge_data(i,j) != None:
                                e=str(random.randint(0,10000))
                                fileWriter.write(" " + str(e))
                        else:
                                fileWriter.write(" 0")
        fileWriter.write("\n")
	action = 'm'
	fileWriter.write(action + " " + str(n) + " " + orintation + " " + v)
        for i in range(0,n):
                for j in range (0,n):
                        if g.get_edge_data(i,j) != None:
                                e=str(random.randint(0,10000))
                                fileWriter.write(" " + str(e))
                        else:
                                fileWriter.write(" 0")
        fileWriter.write("\n")
	action = 'f'
	fileWriter.write(action + " " + str(n) + " " + orintation + " " + v)
        for i in range(0,n):
                for j in range (0,n):
                        if g.get_edge_data(i,j) != None:
                                e=str(random.randint(0,10000))
                                fileWriter.write(" " + str(e))
                        else:
                                fileWriter.write(" 0")
        fileWriter.write("\n")


#################### UNDIRECTED RANDOM GRPAH ################
for k in range(64):
        n = random.randint(10,1000)
        orintation = str(0)
        v = str(random.randint(0,n))
        e = random.randint(8,n)
        action = 'b'
        fileWriter.write(action + " " + str(n) + " " + orintation + " " + v)
        g = nx.gnm_random_graph(n,e, None, orintation)
        for i in range(0,n):
                for j in range (0,n):
			if j<=i:
				fileWriter.write(" 0")
                        elif g.get_edge_data(i,j) != None:
                                e=str(random.randint(0,10000))
                                fileWriter.write(" " + str(e))
                        else:
                                fileWriter.write(" 0")
        fileWriter.write("\n")
	action = 'i'
        fileWriter.write(action + " " + str(n) + " " + orintation + " " + v)
	for i in range(0,n):
                for j in range (0,n):
                        if j<=i:
                                fileWriter.write(" 0")
                        elif g.get_edge_data(i,j) != None:
                                e=str(random.randint(0,10000))
                                fileWriter.write(" " + str(e))
                        else:
                                fileWriter.write(" 0")
        fileWriter.write("\n")
	action = 'm'
        fileWriter.write(action + " " + str(n) + " " + orintation + " " + v)
        for i in range(0,n):
                for j in range (0,n):
                        if j<=i:
                                fileWriter.write(" 0")
                        elif g.get_edge_data(i,j) != None:
                                e=str(random.randint(0,1000))
                                fileWriter.write(" " + str(e))
                        else:
                                fileWriter.write(" 0")
        fileWriter.write("\n")
	action = 'f'
        fileWriter.write(action + " " + str(n) + " " + orintation + " " + v)
        for i in range(0,n):
                for j in range (0,n):
                        if j<=i:
                                fileWriter.write(" 0")
                        elif g.get_edge_data(i,j) != None:
                                e=str(random.randint(0,n))
                                fileWriter.write(" " + str(e))
                        else:
                                fileWriter.write(" 0")
        fileWriter.write("\n")
########### DENSE GRAPH ####################
for k in range(64):
        n = random.randint(10,1000)
        orintation = str(0)
        v = str(random.randint(0,(n-1)))
        e = random.randint(8,n)
        action = 'b'
        fileWriter.write(action + " " + str(n) + " " + orintation + " " + v)
        g = nx.dense_gnm_random_graph(n,e, None)
        for i in range(0,n):
                for j in range (0,n):
                        if j<=i:
                                fileWriter.write(" 0")
                        elif g.get_edge_data(i,j) != None:
                                e=str(random.randint(0,n))
                                fileWriter.write(" " + str(e))
                        else:
                                fileWriter.write(" 0")
        fileWriter.write("\n")
	action = 'i'
        fileWriter.write(action + " " + str(n) + " " + orintation + " " + v)
	for i in range(0,n):
                for j in range (0,n):
                        if j<=i:
                                fileWriter.write(" 0")
                        elif g.get_edge_data(i,j) != None:
                                e=str(random.randint(0,n))
                                fileWriter.write(" " + str(e))
                        else:
                                fileWriter.write(" 0")
        fileWriter.write("\n")
	action = 'm'
        fileWriter.write(action + " " + str(n) + " " + orintation + " " + v)
        for i in range(0,n):
                for j in range (0,n):
                        if j<=i:
                                fileWriter.write(" 0")
                        elif g.get_edge_data(i,j) != None:
                                e=str(random.randint(0,n))
                                fileWriter.write(" " + str(e))
                        else:
                                fileWriter.write(" 0")
        fileWriter.write("\n")
	action = 'f'
        fileWriter.write(action + " " + str(n) + " " + orintation + " " + v)
        for i in range(0,n):
                for j in range (0,n):
                        if j<=i:
                                fileWriter.write(" 0")
                        elif g.get_edge_data(i,j) != None:
                                e=str(random.randint(0,n))
                                fileWriter.write(" " + str(e))
                        else:
                                fileWriter.write(" 0")
        fileWriter.write("\n")
####### COMPLETE GRAPH ######################
for k in range(64):
	n = random.randint(10,1000)
	orintation = str(0)
	v = str(random.randint(0,n))
	g=nx.complete_graph(n)
	action = 'b'
	fileWriter.write(action + " " + str(n) + " " + orintation + " " + v)
	for i in range(0,n):
		for j in range (0,n):
			if j>i:
				e=str(random.randint(0,10000))
				fileWriter.write(" " + str(e))
                	else:
                        	fileWriter.write(" 0")
	fileWriter.write("\n")
	action = 'm'
	fileWriter.write(action + " " + str(n) + " " + orintation + " " + v)
	for i in range(0,n):
        	for j in range (0,n):
                	if j>i:
                        	e=str(random.randint(0,n))
                        	fileWriter.write(" " + str(e))
                	else:
                        	fileWriter.write(" 0")
	fileWriter.write("\n")
	action = 'i'
	fileWriter.write(action + " " + str(n) + " " + orintation + " " + v)
	for i in range(0,n):
        	for j in range (0,n):
                	if j>i:
                        	e=str(random.randint(0,n))
                        	fileWriter.write(" " + str(e))
                	else:
                        	fileWriter.write(" 0")
	fileWriter.write("\n")
	action = 'f'
	fileWriter.write(action + " " + str(n) + " " + orintation + " " + v)
	for i in range(0,n):
        	for j in range (0,n):
                	if j>i:
                        	e=str(random.randint(0,n))
                        	fileWriter.write(" " + str(e))
                	else:
                        	fileWriter.write(" 0")
	fileWriter.write("\n")
