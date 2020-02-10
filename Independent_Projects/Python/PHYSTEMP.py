from math import sqrt

def find_quad(a, b, c):
    x = []
    try:
        x1 = (-b + sqrt(b ** 2 - 4 * a * c)) / (2 * a)
        x.append(x1)
    except:
        pass
    try:
        x2 = (-b - sqrt(b ** 2 - 4 * a * c)) / (2 * a)
        x.append(x2)
    except:
        pass
    return x

def grav(m1, m2, r, G):
    return G * ((m1 * m2) / (r ** 2))

def quad():
    print('ax^2 + bx + c')
    a = float(input('a = '))
    b = float(input('b = '))
    c = float(input('c = '))
    return find_quad(a, b, c)

def scinot(num, sigs):
    lst = [char for char in str(num)]
    if lst[-1] == '0':
        lst[-1] = '1'
        num = float(''.join(lst))
    a = '%E' % num
    temp = a.split('E')[0].rstrip('0').rstrip('.')
    loc = temp.find('.')
    temp2 = temp.replace('.', '')
    while len(temp2) > sigs + 1:
        temp3 = [char for char in temp2]
        temp3.pop(-1)
        temp2 = ''.join(temp3)
    try:
        alef = temp3
        del alef
        temp = [char for char in temp3]
        temp.insert(loc, '.')
        temp = ''.join(temp)
    except:
        pass

    setup = temp.split('.')
    count = len(setup[1])
    temp = str(round(float(temp), count - 1))
    temp2 = temp.replace('.', '')
    
    while len(temp2) < sigs:
        temp += '0'
        temp2 = temp.replace('.', '')

    return temp[0:sigs + 1] + 'E' + str(int(a.split('E')[1].replace('+', '')))

def sigfig(num, places):
    val = scinot(num, places)
    print(val)
    temp = val.split('E')
    pos = float(temp[0])
    scale = 10 ** int(temp[1])
    result = pos * scale
    temp = str(result)
    if '.' in temp:
        temp = temp.split('.')
        temp = temp[0]
    return temp

if __name__ == '__main__':
    number = float(input('What number are we using (>=10)? '))
    sigs = int(input('How many sigfigs are we using? '))
    function = input('What are we looking for (scinot/sigfig)? ')
    if function.lower() == 'scinot':
        print(f'Here we go! {scinot(number, sigs)}')
    elif function.lower() == 'sigfig':
        print(f'Here we go! {sigfig(number, sigs)}')
    else:
        print("Sorry, that function doesn't exist")
#    places = 3
#    
#    G = 6.67 * 10 ** -11
#    m1 = 5.98 * 10 ** 24
#    m2 = 1.99 * 10 ** 30
#    r1 = 150000000000
#    output = G * ((m1 * m2) / (r1 ** 2))
#    
#    print(scinot(grav(m1, m2, r1, G), places))
#    
#    re = 6.38 * 10 ** 6
#    
#    print(scinot((G * m1 / (re ** 2)), places))
#    
#    g = 7.83 * 10 ** -6
#    G = 6.67 * 10 ** -11
#    msum = 190
#    m1 = find_quad(-1, 190, -3005.217391304348)[1]
#    r = 0.16
#
#    print(sigfig(m1, 3))
#    print(sigfig(msum - m1, 3))

'''
from decimal import Decimal
from math import floor, log10

def scinot(num, places):
    if isinstance(num, tuple):
        if num[1] == int:
            val = int(num[0])
        elif num[1] == float:
            val = float(num[0])
    else:
        val = num
    a = '%E' % val
    temp = a.split('E')[0].rstrip('0').rstrip('.')
    temp2 = temp.replace('.', '')
    while len(temp2) < places:
        temp += '0'
        temp2 = temp.replace('.', '')
    return temp + 'E' + str(int(a.split('E')[1].replace('+', '')))
    
def sigfig(num, places):
    if num != 0:
        output = round(num, -int(floor(log10(abs(num))) - (places - 1)))
        kind = type(output)
        temp = str(output).split('e')[0]
        output = []
        for char in temp:
            output.append(char)
        temp = output[:]
        if '.' in temp:
            temp.remove('.')
        count = len(temp)
        while count > places:
            output.pop(-1)
            temp = output[:]
            if '.' in temp:
                temp.remove('.')
            count = len(temp)
        while count < places:
            output.append('0')
            temp = output[:]
            if '.' in temp:
                temp.remove('.')
            count = len(temp)
        
        output = ''.join(output)
        """if kind == int:
            return int(output)
        if kind == float:
            temp = output.split('.')
            offset = len(temp[1])
            return Decimal(format(float(output), f'.{offset}f'))"""
        return output, kind
    return 0

#print(scinot(sigfig(G * m1 / (re ** 2), 3), places))
#print(scinot(sigfig(grav(m1, m2, r1, G), 3), places))
#print(sigfig(m1, 3)[0])
#print(sigfig(msum - m1, 3)[0])
'''