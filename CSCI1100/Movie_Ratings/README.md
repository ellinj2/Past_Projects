# Movie_Ratings

This project takes in two json files, one that contains information about a movie including IMDB rating and one that contains Twitter ratings for that movie. The user is then prompted for specification for a search, including minimum and maximum production year, relative weights for IMDB and Twitter ratings (floats between 0 and 1), and the desired genre. Algorithms are then used to return the best and worst movies in those specifications and basic information about those movies

## Files

- **hw7Part2.py**: Main file that contains algorithms and interface

- **movies.json**: Data file that contains information about movies, including movie id number, genre, year, name, actors, IMDB rating, and number of votes

- **ratings.json**: Data file that contains Twitter ratings for movie id numbers
