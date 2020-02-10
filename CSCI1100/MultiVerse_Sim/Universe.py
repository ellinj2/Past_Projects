'''
This code builds the Universe class with attributes (name, rewards, portals) and modules (__str__, locs)

Date: November 27, 2018
Author: Jesse Ellin
Version: 1.0
'''
class Universe(object):
    '''Class for each Universe in the file'''
    def __init__(self, name, rewards, portals):
        '''initializes Universe instance with name, reward list, and portal list'''
        self.name = name
        self.rewards = rewards
        self.portals = portals

    def __str__(self):
        '''returns a string for a universe instance'''
        final = 'Universe: {} ({} rewards and {} portals)\n'.format(self.name, len(self.rewards), len(self.portals))
        final += 'Rewards:\n'
        if self.rewards:
            for item in self.locs('reward'):
                final += 'at {} for {} points: {}'.format(item[0], item[1], item[2])
                final += '\n'
        else:
            final += 'None\n'
        final += 'Portals:\n'
        if self.portals:
            for portal in self.locs('portal'):
                final += portal
                final += '\n'
        else:
            final += 'None\n'

        return final

    def locs(self, kind):
        '''returns list of locations for each reward or each portal'''
        if kind == 'reward':
            lst = [('({},{})'.format(item[0], item[1]), item[2], item[3]) for item in self.rewards]
        elif kind == 'portal':
            lst = ['{}:({},{}) -> {}:({},{})'.format(self.name, item[0], item[1], item[2], item[3], item[4])\
                                                                       for item in self.portals]
        return lst
