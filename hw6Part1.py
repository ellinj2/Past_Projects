'''
This code acts as a primative spellcheck, taking each word from a file of words and checking them against
a dictionary file of known words. If the word isn't in the dictionary, it then tries to drop each letter, then
swap neighboring letters, then replace each letter. If the word still isn't found, then output likewise.

Date: 11/3/2018
Author: Jesse Ellin
Version: 1
'''


def check_word(word, dic):
    '''Checks if the word -word- is in the dictionary -dic-'''
    if word in dic:
        return True
    return False

def drop(word, dic):
    '''checks if the word -word- is in the dictionary -dic- after dropping each letter individually'''
    possible = []
    for i in range(0, len(word)):
        lst = [letter for letter in word]
        del lst[i]
        temp = ''.join(lst)
        if check_word(temp, dic):
            possible.append(temp)
    
    if possible: #isthere anything in the list of possible words?
        return min(possible)
    
    return False

def listify(name):
    '''Turns a file into a list'''
    file = open(name, 'r')
    temp = file.read().split('\n')
    temp.remove('')
    file.close()
    
    return temp

def replace(word, dic):
    '''checks if the word -word- is in the dictionary -dic- after replacing each letter with each letter from the
    alphapbet individually'''
    possible = []
    alphabet = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
                'u', 'v', 'w', 'x', 'y', 'z']
    lst = [letter for letter in word]
    #check every possible index
    for i in range(0, len(lst)):
        for letter in alphabet:
            templst = lst[:]
            templst[i] = letter
            if check_word(''.join(templst), dic):
                possible.append(''.join(templst))
    
    if possible: #is there anything in the list of possible words?
        return min(possible)
    
    return False

def swap(word, dic):
    '''checks if the word -word- is in the dictionary -dic- after swapping neighboring letters'''
    possible = []
    lst = [letter for letter in word]
    #check every possible index except the last one
    for i in range(0, len(word) - 1):
        templst = lst[:]
        templst[i], templst[i + 1] = templst[i + 1], templst[i]
        if check_word(''.join(templst), dic):
            possible.append(''.join(templst))

    if possible: #is there anything in the list of possible words?
        return min(possible)
    return False

def run():
    '''does the things'''
    dictionaryname = input('Dictionary file => ')
    print(dictionaryname)
    wordsname = input('Input file => ')
    print(wordsname)
    words = listify(wordsname)
    dictionary = set(listify(dictionaryname))
    #check each word
    for word in words:
        if check_word(word, dictionary):
            print('{:15s} -> {:15s} :FOUND'.format(word, word))
        elif drop(word, dictionary) is not False:
            print('{:15s} -> {:15s} :DROP'.format(word, drop(word, dictionary)))
        elif swap(word, dictionary) is not False:
            print('{:15s} -> {:15s} :SWAP'.format(word, swap(word, dictionary)))
        elif replace(word, dictionary) is not False:
            print('{:15s} -> {:15s} :REPLACE'.format(word, replace(word, dictionary)))
        else:
            print('{0:15s} -> {0:15s} :NO MATCH'.format(word))


run()
