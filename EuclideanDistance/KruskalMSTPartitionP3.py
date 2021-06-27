import math
import networkx as nx
#import matplotlib
#matplotlib.use('Agg')
#import matplotlib.pyplot as plt

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
        # A utility function to find set of an element i
        # (uses path compression technique)
    def find(self, parent, i):
        if parent[i] == i:
            return i
        return self.find(parent, parent[i])
    # A function that does union of two sets of x and y
    # (uses union by rank)
    def union(self, parent, rank, x, y):
        xroot = self.find(parent, x)
        yroot = self.find(parent, y)

        # Attach smaller rank tree under root of
        # high rank tree (Union by Rank)
        if rank[xroot] < rank[yroot]:
            parent[xroot] = yroot
        elif rank[xroot] > rank[yroot]:
            parent[yroot] = xroot
        else:
            parent[yroot] = xroot
            rank[xroot] += 1

    # The main function to construct MST using Kruskal's
    # algorithm
    def KruskalMST(self):
        result = nx.Graph()#[] #This will store the resultant MST
        i = 0 # An index variable, used for sorted edges
        e = 0 # An index variable, used for result[]

        # Step 1:  Sort all the edges in non-decreasing
        # order of their
        # weight.  If we are not allowed to change the
        # given graph, we can create a copy of graph
        g1 = sorted(self.graph.edges(data=True), key=lambda x: x[2]['weight'])#sorted(self.graph,key=lambda item: item[2])
        parent = {} ; rank = {}
        # Create V subsets with single elements
        for node in self.graph.nodes():
            parent.update({node:node})
            rank.update({node:0})

        # Number of edges to be taken is equal to V-1
        while e < self.V -1 :
            # Step 2: Pick the smallest edge and increment
            # the index for next iteration
            u,v,w =  g1[i]
            i = i + 1
            x = self.find(parent, u)
            y = self.find(parent, v)

            # If including this edge does't cause cycle,
            # include it in result and increment the index
            # of result for next edge
            if x != y:
                e = e + 1
                result.add_edge(u,v,weight=w)
                self.union(parent, rank, x, y)
                listConnectedComp = sorted(list(nx.connected_component_subgraphs(result)), key = len, reverse=True)
                #for l in listConnectedComp:
                j = 0
                if listConnectedComp[0].number_of_nodes() >= bucketSize:
                    connected = []
                    l = sorted(listConnectedComp[0].edges(data=True), key=lambda x: x[2]['weight'])
                    for u, v, w in l:
                        if u not in connected and j<bucketSize:
                            connected.append(u)
                            j+=1
                        if v not in connected and j<bucketSize:
                            connected.append(v)
                            j+=1
                        if j==bucketSize:
                            break
                    for u in connected:
                        self.graph.remove_node(u)
                    bucketList.append(connected)
                    break
        # Else discard the edge

        # print the contents of result[] to display the built MST
        #for u,v,weight  in result:
        #	print str(u) + " -- " + str(v) + " == " + str(weight)
        #for i in range(len(bucketList)):
        #	print(i)
        #	print(bucketList[i])

        #nx.draw(result)
        #plt.savefig('tree.png')
        #print(result)
        return self.graph

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
    result = g.KruskalMST()
    print(result.number_of_nodes())
    while result.number_of_nodes() != 0:
        g = Graph(result.number_of_nodes())
        g.graph = result
        result = g.KruskalMST()
    with open('outputBuckets.txt', 'w') as f:
        for n in bucketList:
            f.write(repr(n))
            f.write("\n")
    print("DONE")
