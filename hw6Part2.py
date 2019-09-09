'''
This code takes an input portion of a book title, then finds the first book that has that portion in its title,
finds all the creatures in that book, any book that has at least one creature in common, and the creatures that are
unique to the original book.

Date: 11/3/2018
Author: Jesse Ellin
Version: 1.1
'''

import textwrap

def breakup(lst):
    '''Breaks up a long list'''
    temp = ', '.join(lst).replace(', ', '', 1)
    lines = textwrap.wrap(temp)
    return lines

def get_dict(title):
    '''Turns the contents of a file into a dictionary'''
    with open('titles.txt', 'r') as inset:
        by_title = dict()
        half_way = inset.read().strip().split('\n')
        #for every possible index
        for i in range(0, len(half_way)):
            line = half_way[i].split('|')
            by_title[line[0]] = line[1:]

    return by_title.get(title), by_title

def find_title(phrase):
    '''Finds the closest title based on input phrase'''
    with open('titles.txt', 'r') as inset:
        setup = [book for book in inset.read().strip().split('\n')]
        titles = [setup[i].split('|')[0] for i in range(0, len(setup))]

    #check every title
    for name in titles:
        if phrase.lower() in name.lower(): #is phrase in title?
            return name, titles

    return False

def run():
    '''Do the tings'''
    phrase = input('Enter a title (stop to end) => ')
    print(phrase)
    #set controlled infinite loop
    while phrase != 'stop':
        print('')
        if find_title(phrase) is False: #the phrase never appears in the library
            print('This title is not found!', end='\n\n')
        else:
            all_books = find_title(phrase)
            title = all_books[0] #get first result
            library = get_dict(title)
            title_beasts = ['Beasts in this title: '] + sorted(library[0]) #populates first return field
            cousins = ['Other titles containing beasts in common: '] #starts second return field
            temp_cousins = []
            unique_beasts = ['Beasts appearing only in this title: '] + title_beasts[1:] #starts third return field
            for beast in title_beasts: #checks each beast
                for book in all_books[1]: #checks each book
                    if beast in library[1].get(book) and book != title: #is the beast in a different book?
                        temp_cousins.append(book) #add book to cousins
                        if beast in unique_beasts:
                            unique_beasts.remove(beast) #remove beast from unique beasts

            #setsup final outputs
            title_beasts_lines = breakup(title_beasts)
            cousins_lines = breakup(cousins + sorted(list(set(temp_cousins))))
            unique_beasts_lines = breakup(unique_beasts)

            print('Found the following title: {}'.format(title))
            for line in title_beasts_lines: #line by line
                print(line)
            print('')
            for line in cousins_lines:
                print(line)
            print('')
            for line in unique_beasts_lines:
                print(line)
            print('')

        phrase = input('Enter a title (stop to end) => ')
        print(phrase)    


run()
