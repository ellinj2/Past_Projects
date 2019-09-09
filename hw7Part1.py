'''
This code checks a set of input words against a set of known words. If the word isn't in the dictionary, it tries
dropping each letter and checking the new word, then inserting each letter in the alphabet into each index and
checking the new words, then swapping consecutive letters and checking the new words, then replacing each letter
with a letter form the set of possible letters from the keyboard input. It then returns the top 3 matches by
the frequency ratings found in the dictionary file. If no matches are found, return thusly.

Date: November 9, 2018
Author: Jesse Ellin
Version: 1.2
'''

def check_word(word, dic):
    '''Checks if the word -word- is in the dictionary -dic-'''
    if word in dic:
        return True
    return False

def drop(word, dic):
    '''checks if the word -word- is in the dictionary -dic- after dropping each letter individually'''
    possible = set()
    for i in range(0, len(word)):
        lst = [letter for letter in word]
        del lst[i]
        temp = ''.join(lst)
        '''if word == 'darmed':
            print(temp)'''
        if check_word(temp, dic):
            possible.add(temp)

    if possible: #is there anything in the list of possible words?
        return list(possible)
    return False

def flatten(lst):
    '''Creates a flat list out of a list of lists'''
    flat_list = []
    for i in range(0, len(lst)):
        if isinstance(lst[i], list): #if the item is a list
            flat_list.extend(flatten(lst[i])) #extend flat list by a flattened lst
        else:
            flat_list.append(lst[i]) #add the item

    return flat_list

def get_dictionary(name):
    '''Converts file to dictionary'''
    out = dict()
    with open(name, 'r') as file:
        temp = file.read().strip().split('\n')
        semi = [line.strip().split(',') for line in temp]
        for item in semi:
            out[item[0]] = item[1]

    return out

def insert(word, dic):
    '''Inserts and checks each possible letter at each possible index'''
    possible = set()
    alphabet = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',\
                'u', 'v', 'w', 'x', 'y', 'z']
    lst = [letter for letter in word]
    #checks every possible letter in every possible index
    for i in range(0, len(lst)):
        for letter in alphabet:
            templst = lst[:]
            templst.insert(i, letter)
            if check_word(''.join(templst), dic):
                possible.add(''.join(templst))
    if possible: #Is there anything in the list of possible words?
        return list(possible)
    return False

def listify(name):
    '''Turns a file into a list'''
    file = open(name, 'r')
    temp = file.read().strip().split('\n')
    file.close()

    return temp

def replace(word, dic, keyboard):
    '''checks if the word -word- is in the dictionary -dic- after replacing each letter with each letter from the
    alphapbet individually'''
    possible = set()
    lst = [letter for letter in word]
    #check every possible index
    for i in range(0, len(lst)):
        alphabet = keyboard.get(lst[i])
        if alphabet:
            for item in alphabet:
                templst = lst[:]
                templst[i] = item
                '''if word == 'darmed':
                    print(''.join(templst))'''
                if check_word(''.join(templst), dic):
                    possible.add(''.join(templst))

    if possible: #is there anything in the list of possible words?
        return list(possible)
    return False

def swap(word, dic):
    '''checks if the word -word- is in the dictionary -dic- after swapping neighboring letters'''
    possible = set()
    lst = [letter for letter in word]
    #check every possible index except the last one
    for i in range(0, len(word) - 1):
        templst = lst[:]
        templst[i], templst[i + 1] = templst[i + 1], templst[i]
        if check_word(''.join(templst), dic):
            possible.add(''.join(templst))

    if possible: #is there anything in the list of possible words?
        return list(possible)
    return False

def run():
    '''does the things'''
    #print('Hello world!')
    dictionaryname = input('Dictionary file => ')
    print(dictionaryname)
    wordsname = input('Input file => ')
    print(wordsname)
    keyboardname = input('Keyboard file => ')
    print(keyboardname)

    #dictionaryname = 'words_10percent.txt'
    #wordsname = 'input_words.txt'
    #keyboardname = 'keyboard.txt'

    words = listify(wordsname)
    dictionary_setup = dict()
    with open(dictionaryname, 'r') as file:
        temp = file.read().strip().split('\n')
        semi = [line.strip().split(',') for line in temp]
        for item in semi:
            dictionary_setup[item[0]] = item[1]

    dictionary = list(set(dictionary_setup.keys()))

    keyboard = dict()
    with open(keyboardname, 'r') as file:
        temp = file.read().strip().split('\n')
        semi = [line.strip().split(' ') for line in temp]
        for item in semi:
            keyboard[item[0]] = item[1:]

    #check each word
    for word in words:
        #print(word)
        word = word.strip()
        if check_word(word, dictionary):
            print('{:15s} -> {:15s} :FOUND'.format(word, word))
        else:
            possible = []
            result_type = dict()
            if drop(word, dictionary) is not False:
                possible.append(drop(word, dictionary))
                for item in drop(word, dictionary):
                    result_type[item] = 'DROP'
            if insert(word, dictionary) is not False:
                possible.append(insert(word, dictionary))
                for item in insert(word, dictionary):
                    result_type[item] = 'INSERT'
            if swap(word, dictionary) is not False:
                possible.append(swap(word, dictionary))
                for item in swap(word, dictionary):
                    result_type[item] = 'SWAP'
            if replace(word, dictionary, keyboard) is not False:
                possible.append(replace(word, dictionary, keyboard))
                for item in replace(word, dictionary, keyboard):
                    result_type[item] = 'REPLACE'
            if not drop(word, dictionary) and not insert(word, dictionary) and not swap(word, dictionary)\
                and not replace(word, dictionary, keyboard):
                print('{0:15s} -> {0:15s} :NO MATCH'.format(word))
            else:
                outcomes = []
                for item in flatten(possible):
                    outcomes.append([dictionary_setup.get(item), item])
                    outcomes.sort(reverse=True)
                    result = [item[1] for item in outcomes]

                output = result[0:3]

                for i in range(0, len(output)):
                    print('{:15s} -> {:15s} :MATCH {}'.format(word, output[i], i + 1))


run()
