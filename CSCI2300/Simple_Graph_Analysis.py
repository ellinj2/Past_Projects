from random import random
from numpy import arange
import plotly.graph_objects as go

global ID
ID=0

class Node:
	def __init__(self):
		global ID
		self.id=ID
		ID+=1
		self.neighbors=[]
		self.visited=False

	def add_edge(self, e):
		self.neighbors.append(e)

class Edge:
	def __init__(self, a, b):
		self.params=(a,b)
		a.add_edge(b)
		b.add_edge(a)

class Graph:
	def __init__(self, n, e):
		self.root=n[0]
		self.all_nodes=n
		self.all_edges=e

def G(n,p):
	if n<=1:
		raise ValueError("n is too low")
	if p<0 or p>1:
		raise ValueError("Invalid p")
	all_edges=[]
	all_nodes=[]
	for i in range(n):
		all_nodes.append(Node())
	for i in range(n):
		for j in range(i+1,n):
			if random()<=p:
				all_edges.append(Edge(all_nodes[i],all_nodes[j]))
				#print("Added edge from {} to {}".format(all_nodes[i].id,all_nodes[j].id))

	return Graph(all_nodes, all_edges)

def component(t, g, printer):
	for i in range(len(g.all_nodes)):
		start=g.all_nodes[i]
		success=[start]
		start.visited=True
		current=start
		queue=[current]
		clear=[]
		count=1
		while(len(queue)>0):
			current=queue.pop(0)
			clear.append(current)
			for node in current.neighbors:
				if node.visited is False:
					queue.append(node)
					success.append(node)
					node.visited=True
					count+=1
					if count==t:
						if printer:
							print("Nodes in component")
							for node in success:
								print(node.id)
						return True
		for node in clear:
			node.visited=False
		success=[]
	return False

def visualize(total, data):
	fig = go.Figure(data=[go.Bar(name="Successful Graphs", x=[val for val in data.keys()], y=[val for val in data.values()])])
	fig.update_layout(barmode="group")
	fig.show()

mode=input("What checkpoint are we looking at? ")
if mode=="a":
	g=G(5,0.7)
	print("This graph contains the following nodes:")
	for node in g.all_nodes:
		print(node.id)
	print("\nAnd the following edges:")
	for edge in g.all_edges:
		print("{}->{}".format(edge.params[0].id, edge.params[1].id))

elif mode=="b":
	g=G(5,0.5)
	result=component(3,g,True)
	if result:
		print("A component was found!")
	else:
		print("No such component exists")

else:
	results={}
	sumof=0
	n=40
	for c in arange(0.2,3.0,0.2):
		results[c]=0
		p=c/n
		for i in range(500):
			g=G(n,p)
			sumof+=1
			ID=0
			if component(30,g,False):
				results[c]+=1

	for key in results.keys():
		print("Number of successes for c={}: {}".format(key,results[key]))

	visualize(sumof, results)

