'''
This code builds the Person class with attributes (name, radius, home_universe, current_universe, x, y, dx, dy,
rewards, movable) and modules (__str__, loc, move, points).

Date: November 27, 2018
Author: Jesse Ellin
Version: 1.0
'''
class Person(object):
    '''Class for each Person in the file'''
    def __init__(self, name, r, home, x, y, dx, dy, current):
        '''initializes each Person with name, radius, home, current, x, y, dx, dy, rewards, and movability'''
        self.name = name
        self.radius = r
        self.home_universe, self.current_universe = home, current
        self.x, self.y = x, y
        self.dx, self.dy = dx, dy
        self.rewards = []
        self.movable = True

    def __str__(self):
        '''returns print statement for Person instance'''
        final = '{} of {} in universe {}\n'.format(self.name, self.home_universe, self.current_universe)
        final += '    at {} speed {} with {} rewards and {} points'.format(self.loc()[0], self.loc()[1],\
                                                                       len(self.rewards), self.points())
        return final

    def loc(self):
        '''return list of location elements for Person'''
        return ['({},{})'.format(self.x, self.y), '({},{})'.format(self.dx, self.dy)]

    def move(self):
        '''updates x and y'''
        self.x += self.dx
        self.y += self.dy

    def points(self):
        '''sums points for person'''
        total = 0
        for item in self.rewards:
            total += int(item[2])
        return total
