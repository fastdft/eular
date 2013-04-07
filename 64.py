import os
import sys
import math

def get_sequence(dec, length):
    if length < 0:
        return ()
    n = dec[0]
    a = dec[1]
    b = dec[2]
    x = int(float(b)/(math.sqrt(n)-a))
    #print('input: %d %d %d' % (n, a, b))
    return tuple([x]) + get_sequence((n, (n*x-a*a*x-a*b)/b, (n-a*a)/b), length-1)

def get_cycle(seq):
    times = 0
    #print(seq)
    for i in range(1,int(len(seq)/2)):
        l = len(seq) - i
        if seq[:l] == seq[i:]:
            return seq[:i]
    raise Exception('no cycle')

def get_sqrt_factor(num):
    integer = int(math.sqrt(num))
    dec = (num, integer, 1)
    cycle = get_cycle(get_sequence(dec, 500))
    return (integer, cycle)

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('usage: python exe cnt')
        sys.exit(0)

    ret = 0
    for i in range(int(sys.argv[1])):
        sq = math.sqrt(i)
        if sq > int(sq):
            fac = get_sqrt_factor(i)
            if len(fac[1])%2 == 1:
                ret = ret + 1
    print(str(ret))
