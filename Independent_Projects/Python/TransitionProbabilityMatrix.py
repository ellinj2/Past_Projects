class Node:
	def __init__(self, val):
		self.id=val
		self.outs=[]

	def addOut(self, A):
		self.outs.append(A)

class Graph:
	def __init__(self):
		self.nodes = []

	def addNode(self, A):
		if A not in self.nodes:
			self.nodes.append(A)

class PageRank:
	def __init__(self, G):
		if type(G) is list:
			self.vector=G
		else:
			self.vector=[]
			for i in range(len(G.nodes)):
				self.vector.append([[]])
			for node in G.nodes:
				self.vector[node.id][0]=1/len(G.nodes)

	def iterate(self, M):
		matrix = matrixMultiply(M, self.vector)
		return PageRank(matrix)

	def __str__(self):
		string = ""
		for val in self.vector:
			string += "{}\n".format(val)
		return string.strip()

def matrixMultiply(A, B):
	#Initialize new matrix
	newMatrix = []
	for i in range(len(A)):
		newMatrix.append([])
		for j in range(len(B[0])):
			newMatrix[i].append(0)

	#Assign values in new matrix
	for fR in range(len(A)):
		for sC in range(len(B[0])):
			tempsum=0
			for fC in range(len(A[fR])):
				tempsum+=A[fR][fC]*B[fC][sC]
			newMatrix[fR][sC]=tempsum

	return newMatrix


def adjacency(G):
	#Initialize adjacency matrix
	retMatrix=[]
	for i in range(len(G.nodes)):
		retMatrix.append([])
		for j in range(len(G.nodes)):
			retMatrix[i].append(0)
	
	#Assign adjacency values
	for v in G.nodes:
		for u in G.nodes:
			if v.id!=u.id:
				if u in v.outs:
					retMatrix[v.id][u.id]+=1

	return retMatrix

def diagonal(G):
	#Initialize diagonal matrix
	retMatrix=[]
	for i in range(len(G.nodes)):
		retMatrix.append([])
		for j in range(len(G.nodes)):
			retMatrix[i].append(0)

	#Assign values
	for node in G.nodes:
		retMatrix[node.id][node.id]=1/len(node.outs)

	return retMatrix

def invert(M):
	for i in range(len(M)):
		for j in range(i+1):
			temp = M[i][j]
			M[i][j]=M[j][i]
			M[j][i]=temp

	return M

test = Graph()
Y = Node(0)
M = Node(1)
K = Node(2)
S = Node(3)
A = Node(4)
Y.addOut(K)
M.addOut(Y)
K.addOut(A)
K.addOut(S)
S.addOut(A)
S.addOut(Y)
A.addOut(M)
test.addNode(Y)
test.addNode(M)
test.addNode(K)
test.addNode(S)
test.addNode(A)

print(type(Y))

AM=adjacency(test)
D=diagonal(test)
TPM=matrixMultiply(D,AM)

for row in AM:
	print(row)
print()

for row in D:
	print(row)
print()

for row in TPM:
	print(row)
print()

TPM=invert(TPM)

for row in TPM:
	print(row)
print()

v0 = PageRank(test)
print(v0)
print()
v1 = v0.iterate(TPM)

print(v1)
