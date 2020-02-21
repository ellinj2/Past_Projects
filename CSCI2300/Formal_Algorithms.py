from copy import deepcopy
from random import choice, randint

global ID
ID=0


class Node:
	def __init__(self):
		global ID
		self.id=ID
		ID+=1
		self.neighbors=[]
		self.edges=[]
		self.visited=False
		self.skip=False

	def add_edge(self, e):
		self.edges.append(e)
		if e.first.id!=self.id:
			self.neighbors.append(e.first)
		else:
			self.neighbors.append(e.second)

	def BFS(self, edges):
		self.visited=True
		chain=[self]
		for root in chain:
			es=[edge for edge in edges if edge.first.id==root.id]
			for edge in es:
				if edge.second.visited == False:
					edge.second.visited=True
					chain.append(edge.second)

		for node in chain:
			node.visited=False
		return chain

class Edge:
	def __init__(self, one, two, weight):
		self.first=one
		self.second=two
		self.weight=weight

	def __str__(self):
		return "{} <-({})-> {}".format(self.first.id, self.weight, self.second.id)

class Graph:
	def __init__(self, nodes, edges, name=""):
		self.nodes=nodes
		self.edges=edges
		self.name=name

	def numComponents(self):
		copyNodes=deepcopy(self.nodes)
		components=[]
		for node in copyNodes:
			if node.skip==False:
				found=node.BFS(sorted(self.edges, key=lambda x: x.first.id))
				for node in found:
					for item in copyNodes:
						if item.id==node.id:
							item.skip=True
				components.append(found)

		return len(components)

	def Kruskal(self):
		tree=Graph(self.nodes, [], "Kruskal Tree of {}".format(self.name))
		self.edges.sort(key=lambda x: x.weight)
		for edge in self.edges:
			test=Graph(tree.nodes, deepcopy(tree.edges), "Test")
			test.edges.append(edge)
			if test.numComponents()<tree.numComponents():
				tree.edges.append(edge)
			if tree.numComponents()==1:
				break
		return tree

	def Prim(self):
		tree=Graph([], [], "Prim Tree of {}".format(self.name))
		tree.nodes.append(choice(self.nodes))
		print("Randomly picked:",tree.nodes[0].id)
		ids=[]
		ids.append(tree.nodes[0].id)
		edges=deepcopy(sorted(self.edges, key=lambda x: x.weight))
		while len(tree.nodes) != len(self.nodes):
			for edge in edges:
				if edge.first.id in ids and edge.second.id not in ids:
					tree.edges.append(edge)
					tree.nodes.append(edge.second)
					ids.append(edge.second.id)
				elif edge.first.id not in ids and edge.second.id in ids:
					tree.edges.append(edge)
					tree.nodes.append(edge.first)
					ids.append(edge.first.id)
		return tree

	def Bollman_Ford(self):
		test=Graph(deepcopy(self.nodes), [], "Bollman_Ford Tree of {}".format(self.name))
		distance={}
		for node in test.nodes:
			distance[node.id]=len(test.nodes)**4 #initialize distances to MASSIVE number
		initial=choice(test.nodes)
		distance[initial.id]=0
		print(distance)
		for node in test.nodes:
			for edge in self.edges:
				if node.id==edge.second.id:
					print(edge, distance[edge.first.id]+edge.weight, distance[node.id])
					if distance[edge.first.id]+edge.weight<distance[node.id]:
						distance[node.id]=distance[edge.first.id]+edge.weight
						test.edges.append(edge)
				if node.id==edge.first.id:
					if distance[edge.second.id]+edge.weight<distance[node.id]:
						distance[node.id]=distance[edge.first.id]+edge.weight
						test.edges.append(edge)

		for edge in test.edges:
			if node.id==edge.second.id:
				if distance[edge.first.id]+edge.weight<distance[node.id]:
					raise Exception("ERROR: Infinite negative cycle found!!!")
			if node.id==edge.first.id:
				if distance[edge.second.id]+edge.weight<distance[node.id]:
					raise Exception("ERROR: Infinite negative cycle found!!")
		return test


	def __str__(self):
		retstr="{}:\n".format(self.name)
		self.edges.sort(key=lambda x: x.first.id)
		for edge in self.edges:
			retstr+=str(edge)+"\n"
		return retstr.strip()


size=int(input("How many vertices are in the graph? "))

weights=set()
while len(weights)<size*(size-1)//2:
	weights.add(randint(0,size*(size-1)//2))
weights=list(weights)

nodes=[Node() for i in range(0,size)]
edges=[]
for i in range(0,size):
	for j in range(i+1,size):
		weight=choice(weights)
		weights.remove(weight)
		edge=Edge(nodes[i],nodes[j],weight)
		edges.append(edge)
		nodes[i].add_edge(edge)
		nodes[j].add_edge(edge)

G=Graph(nodes, edges, "Original")
print(G)
print()

u_in=""
while u_in != "End":
	u_in=input("What algorithm do you want to run? (Please use capitalized name) or \"End\" ")
	if u_in=="Kruskal":
		result=G.Kruskal()

	elif u_in=="Prim":
		result=G.Prim()

	elif u_in=="Bollman_Ford":
		result=G.Bollman_Ford()

	print(result)
	print()


