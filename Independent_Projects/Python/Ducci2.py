'''
This is a modified copy of a worked solution from /r/dailyprogramming
'''

def ducci(x, new_x=[]):
    x = [abs(a - b) for a, b in zip(x, x[1:] + [x[0]])]
    if x in new_x:
        return len(new_x) + 1, new_x
    return ducci(x, new_x + [x])
    
if __name__ == '__main__':
    user_input = []
    n = int(input("How many numbers are in the list? "))
    print(n)
    for i in range(n):
        new_in = int(input("Enter a number: "))
        print(new_in)
        user_input.append(new_in)
    size, new_x = ducci(user_input)
    print('\n')
    for x in new_x:
        print(x)
    print(f'{size} steps taken.')
    if sum(new_x[-1])!=0:
        print("Couldn't resolve to 0")
