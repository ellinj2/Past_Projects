with open('titles.txt', 'r') as x:
    x = x.read().strip().split('\n')
    dictionary = dict()
    for i in range(0, len(x)):
        line = x[i].split('|')
        dictionary[line[0]] = line[1:]
    print(dictionary)
    lst = [key[0] for key in dictionary.items()]
    print(lst)
#print(x)