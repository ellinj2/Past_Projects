def fibint(x):
    fibseq = [1, 1]
    while x > fibseq[-1]:
        fibseq.append(fibseq[-1] + fibseq[-2])
    
    fibseq.pop()
    result = int(fibseq[-1] * int(float(x) / fibseq[-1]))
    return result


print(fibint(int(input("What number do you want to round? "))))