import math
import networkx as nx
from scipy.cluster.hierarchy import dendrogram, linkage
import matplotlib 
matplotlib.use('Agg')

bucketSize =32
bucketList = []
def euclidean_dist(point1,point2):
	#print("from dist")
	dist =0
	x = point1.split()
	y = point2.split()
	for i in range(len(x)):
		x1 = int(x[i])
		y1 = int(y[i])
		dist = dist + (x1-y1)*(x1-y1)
	dist = math.sqrt(dist)
	return dist

#Class to represent a graph 
class Graph: 
	def __init__(self,vertices): 
        	self.V= vertices #No. of vertices 
        	self.graph = nx.Graph()# default dictionary  
                                # to store graph
	def addEdge(self,u,v,w): 
		self.graph.add_edge(u,v,weight=w)#append([u,v,w])

	def KruskalMST(self):
        	g1 = sorted(self.graph.edges(data=True), key=lambda x: x[2]['weight'])#sorted(self.graph,key=lambda item: item[2])
        	X = []
        	i=0
        	for u,v,w in g1:
            		X.append(w['weight'])
                    	i+=1
			#print(w['weight'])
        	Z = linkage(X, 'ward')
        	fig = plt.figure(figsize=(25, 10))
        	dn = dendrogram(Z)
		plt.show()

if __name__ == "__main__":
	fileName = raw_input('Enter file name?: ')
	fp= open(fileName,"r")
	dic = {}
	id =0
	for line in fp:
		str = line.split("-")
		#print(str[0])
		dic.update({id:str[0]})
		id +=1
	fp.close()
	matrix ={}
	i=0
	for i in dic.keys():
		j=i+1
		while(j<len(dic)):
			dis = euclidean_dist(dic[i],dic[j])
			dis = round(dis,2)
			matrix.update({(i,j):dis})
			j+=1
	g = Graph(1024)
	for key in matrix.keys():
		w = matrix[key]        
		g.addEdge(key[0],key[1],w)	
	g.KruskalMST()
	print("DONE")
