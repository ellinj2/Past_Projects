'''
This code takes a dic file of IMDB information for a movie code and a Twitter rating file for the same movie codes
(not all movie codes are in Twitter ratings). It then takes an input range of years, weights for the IMDB rating
and the Twitter rating, and the desired genre, and returns the best and worst movies in that range, when 
they were released, and what their aggregate score was.

Date: November 10, 2018
Author: Jesse Ellin
Version: 1.1
'''


import json

def dictionaries(movies):
    '''creates the IMDB dictionary types'''
    by_genre = dict() #genre: [titles]
    by_year = dict() #year: [titles]
    ratings = dict() #title: ratings
    my = dict() #title: year

    #populate for every movie code
    for key in movies.keys():
        for item in movies[key]['genre']: #populate by_genre
            if item in by_genre.keys():
                by_genre[item].append(movies[key]['name'])
            else:
                by_genre[item] = [movies[key]['name']]
        if movies[key]['movie_year'] in by_year.keys(): #populate by_year
            by_year[movies[key]['movie_year']].append(movies[key]['name'])
        else:
            by_year[movies[key]['movie_year']] = [movies[key]['name']]
        ratings[movies[key]['name']] = movies[key]['rating'] #populate ratings
        my[movies[key]['name']] = movies[key]['movie_year'] #populate my
    return by_genre, by_year, ratings, my

def twitted(movies, file):
    '''creates the average Twitter ratings'''
    ratings = dict() #title: score

    #populate for every movie code
    for key in movies.keys():
        if key in file.keys() and len(file.get(key)) >= 3: #NEEDS TO HAVE AT LEAST THREE RATINGS!!!
            average = sum(file[key]) / len(file[key])
            ratings[movies[key]['name']] = average

    return ratings

def run():
    '''Does the things'''
    movies = json.loads(open("movies.json").read())
    ratings = json.loads(open("ratings.json").read())

    #get inputs
    year1 = input('Min year => ')
    print(year1)
    year2 = input('Max year => ')
    print(year2)
    w1 = input('Weight for IMDB => ')
    print(w1)
    w1 = float(w1)
    w2 = input('Weight for Twitter => ')
    print(w2, end='\n\n')
    w2 = float(w2)
    genre = input('What genre do you want to see? ')
    print(genre, end='\n\n')
    genre = genre.title()
    if w1 == 0:
        w2 = 1
    elif w2 == 0:
        w1 = 1

    while genre != 'Stop': #keep going until you're told to stop
        by_year = set()
        by_genre = set()
        by_rating = list()
        temp = dictionaries(movies) #only want to run once for efficiency
        genres = temp[0] #by_genre
        yearly = temp[1] #by_year
        imdb_ratings = temp[2] #ratings
        my = temp[3] #my
        twitter_ratings = twitted(movies, ratings)

        if genre not in genres.keys(): #make sure genre exists
            print('No {} movie found in {} through {}'.format(genre, year1, year2), end='\n\n')
        else:
            for movie in list(genres.get(genre)): #populate all movies in genre
                by_genre.add(movie)
            for year in range(int(year1), int(year2) + 1):
                if yearly.get(year):
                    for movie in yearly.get(year): #populate all movies in year range
                        by_year.add(movie)

            possibilities = by_year & by_genre #populate possibilities with movies in both sets
            for movie in possibilities:
                if movie in twitter_ratings.keys(): #make sure each movie has a Twitter rating
                    by_rating.append((w1 * imdb_ratings[movie] + w2 * twitter_ratings[movie], movie))

            by_rating.sort(reverse=True) #sort best to worst
            
            if by_rating:
                b = (by_rating[0][1], my[by_rating[0][1]], by_rating[0][0]) #name, year, rating
                w = (by_rating[-1][1], my[by_rating[-1][1]], by_rating[-1][0]) #name, year, rating
                print('Best:\n\tReleased in {}, {} has a rating of {:.2f}'.format(b[1], b[0], b[2]), end='\n\n')
                print('Worst:\n\tReleased in {}, {} has a rating of {:.2f}'.format(w[1], w[0], w[2]), end='\n\n')

            else:
                print('No {} movie found in {} through {}'.format(genre, year1, year2), end='\n\n')

        genre = input('What genre do you want to see? ')
        if genre.lower() != 'stop':
            print(genre, end='\n\n')
        else:
            print(genre)
        genre = genre.title()


run()
    
