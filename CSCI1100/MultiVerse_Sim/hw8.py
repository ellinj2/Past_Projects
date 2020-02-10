'''
This code takes an input file name, that file containing a dictionary of universes with rewards, individuals, and 
portals, then runs a simulation based on that dictionary to see which individual collects the most
rewards before either everyone stops moving or 100 simulation steps occur.

Date: December 8, 2018
Author: Jesse Ellin
Version: 1.7
'''

import json
from copy import deepcopy
from math import sqrt
from Person import Person
from Universe import Universe

def copy(person):
    '''returns a deepcopy of the person with all values rounded to one decimal'''
    temp = fix(deepcopy(person))
    return temp

def drop_r(person, n):
    '''performs the speed modifications when person drops a reward'''
    person.dx += (n%2) * (n / 6) * person.dx
    person.dy += ((n + 1) % 2) * (n / 6) * person.dy
    return person.dx, person.dy

def end(results):
    '''prints the end of simulation statement'''
    line = '-' * 40
    persons, stopped, step = results[0], results[1], results[2]
    score_dic = dict()
    for person in persons:
        score_dic[person.name] = [0, []] #[score, reward list]
        for reward in person.rewards:
            score_dic[person.name][0] += reward[2]
            score_dic[person.name][1].append(reward)
    by_score = sorted([(score_dic[person.name][0], person.name) for person in persons])
    best = by_score[-1]
    peeps = [person for person in persons if score_dic[person.name][0] == best[0]]
    if len(persons) - len(stopped) > 0:
        still_going = '{} individuals still moving: '.format(len(persons) - len(stopped))
    else:
        still_going = '0 individuals still moving'
    moving = [person for person in persons if person not in stopped]
    for person in moving:
        still_going += '{}'.format(person.name)
        if moving.index(person) < len(moving) - 1:
            still_going += ', '
            
    print('\n{}'.format(line))
    print('Simulation stopped at step {}'.format(step))
    print(still_going)
    print('Winners:')
    for person in peeps:
        print(person)
        print('Rewards:')
        for reward in score_dic[person.name][1]:
            print('    {}'.format(reward[3]))
        print()

def fix(person):
    '''rounds all values in person to one decimal'''
    person.x, person.y = round(float(person.x), 1), round(float(person.y), 1)
    person.dx, person.dy = round(float(person.dx), 1), round(float(person.dy), 1)
    return person

def pickup_r(person, n):
    '''runs the speed modifications for when person picks up a reward'''
    person.dx -= (n%2) * (n / 6) * person.dx
    person.dy -= ((n + 1) % 2) * (n / 6) * person.dy
    return person.dx, person.dy

def post_col(person, u_by_r, r_by_u):
    '''runs post-colision operations'''
    r = person.rewards.pop(0)
    r_by_u[person.current_universe].append(r)
    n = len(person.rewards)
    new = drop_r(person, n)
    person.dx, person.dy = new[0], new[1]
    person.dx, person.dy = -1 * person.dx, -1 * person.dy
    print('{} dropped "{}", reward returned to {} at ({},{})'.format(person.name, r[3],\
                                                          u_by_r[r[3]], r[0], r[1]))
    return person

def start(universes, data):
    '''prints start of simulation message'''
    line = '-' * 40
    print('All universes', line, sep='\n')
    for universe in universes:
        print('{}'.format(universe))
    print('All individuals', line, sep='\n')
    for u in data:
        for ind in u['individuals']:
            person = Person(ind[0], ind[1], u['universe_name'], ind[2], ind[3], ind[4], ind[5], u['universe_name'])
            temp = copy(person)
            print(temp)
    print('\nStart simulation\n{}'.format(line))

def run():
    '''does the things'''
    name = input('Input file => ')
    print(name)
    data = json.loads(open(name).read())
    collisions = []
    step = 0
    stopped = set()
    p_by_u = dict() #{universe: [portals]}
    r_by_u = dict() #{universe: [rewards]}
    u_by_r = dict() #{reward: universe}
    universes = [Universe(uni['universe_name'], uni['rewards'], uni['portals']) for uni in data]
    for uni in universes:
        p_by_u[uni.name] = uni.portals
        r_by_u[uni.name] = uni.rewards
    for uni in universes:
        for reward in uni.rewards:
            u_by_r[reward[3]] = uni.name
    persons = [Person(person[0], person[1], uni['universe_name'], person[2], person[3], person[4],\
                      person[5], uni['universe_name']) for uni in data for person in uni['individuals']]
    start(universes, data)
    for person in persons:
        #check boundary conditions
        loc_check = bool(person.x <= 0 or person.x >= 1000 or person.y <= 0 or person.y >= 1000)
        speed_check = bool(-10 < person.dx < 10 or -10 < person.dy < 10)
        if person.movable and (loc_check or speed_check):
            person.movable = False
            temp = deepcopy(person)
            fix(temp)
            print('{} stopped at simulation step {} at location ({},{})\n'.format(\
                  temp.name, step, temp.x, temp.y))
            stopped.add(person)
    while step < 100 and len(stopped) < len(persons):
        step += 1
        for person in persons:
            #check if the person can move
            if person.movable:
                person.move()
        for person in persons:
            #check boundary conditions
            if person.movable and (person.x <= 0 or person.x >= 1000 or person.y <= 0 or person.y >= 1000):
                person.movable = False
                temp = deepcopy(person)
                fix(temp)
                print('{} stopped at simulation step {} at location ({},{})\n'.format(\
                        temp.name, step, temp.x, temp.y))
                stopped.add(person)
        #Check for rewards
        for person in persons:
            #check if person can do anything
            if person not in stopped:
                #check if person is near reward
                for reward in r_by_u[person.current_universe]:
                    if sqrt((person.x - reward[0]) ** 2 + (person.y - reward[1]) ** 2) <= person.radius:
                        temp = r_by_u[person.current_universe]
                        name = reward[3]
                        person.rewards.append(temp.pop(temp.index(reward)))
                        n = len(person.rewards)
                        new = pickup_r(person, n)
                        person.dx, person.dy = new[0], new[1]
                        print('{} picked up "{}" at simulation step {}'.format(person.name, name, step))
                        temp = copy(person)
                        print(temp, end='\n\n')
                        #check stop conditions
                        if abs(person.dx) < 10 or abs(person.dy) < 10:
                            person.movable = False
                            temp = copy(person)
                            print('{} stopped at simulation step {} at location ({},{})\n'.format(\
                                    temp.name, step, temp.x, temp.y))
                            stopped.add(person)
        #Check for collisions
        for person in persons:
            #check if person can do anything
            if person not in stopped:
                #check for collisions
                for other in persons:
                    if other not in stopped:
                        if person.name != other.name and person.current_universe == other.current_universe:
                            temp1, temp2 = copy(person), copy(other)
                            distance = sqrt((temp1.x - temp2.x) ** 2 + (temp1.y - temp2.y) ** 2)
                            if distance <= (person.radius + other.radius) and\
                                (other.name, person.name) not in collisions:
                                collisions.append((person.name, other.name))
                                print('{} and {} crashed at simulation step {} in universe {}'.format\
                                      (person.name, other.name, step, person.current_universe))
                                if person.rewards:
                                    post_col(person, u_by_r, r_by_u)
        
                                if other.rewards:
                                    post_col(other, u_by_r, r_by_u)
        
                                temp1 = copy(person)
                                temp2 = copy(other)
                                print(str(temp1), str(temp2), '', sep='\n')
                            elif distance > person.radius + other.radius:
                                if (other.name, person.name) in collisions:
                                    collisions.remove((other.name, person.name))
                                if (person.name, other.name) in collisions:
                                    collisions.remove((person.name, other.name))
        #Check for portals
        for person in persons:
            #check if person can do anything
            if person not in stopped:
                #check for portalling
                for portal in p_by_u[person.current_universe]:
                    if sqrt((person.x - portal[0]) ** 2 + (person.y - portal[1]) ** 2) <= person.radius:
                        person.x, person.y, person.current_universe = portal[3], portal[4], portal[2]
                        print('{} passed through a portal at simulation step {}'.format(person.name, step))
                        temp = copy(person)
                        print(temp, end='\n\n')
                if (abs(person.dx) < 10 or abs(person.dy) < 10) and person.movable:
                    person.movable = False
                    temp = copy(person)
                    print('{} stopped at simulation step {} at location ({},{})\n'.format(\
                            temp.name, step, temp.x, temp.y))
                    stopped.add(person)
    for person in persons:
        fix(person)
    results = (persons, stopped, step)
    end(results)

run()
