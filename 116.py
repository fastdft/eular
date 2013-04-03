import os
import sys

def count_recur(cnt, length, cnt_dict):
    if cnt < length:
        return 1

    #because the tiles may not replace at all, so there should be 1 more case
    ret = 1
    # i means the number of titles been eaten, the cnt+1 means all titles have been eaten
    for i in range(length, cnt+1):
        if cnt-i in cnt_dict:
            ret = ret + cnt_dict[cnt-i]
        else:
            tmp = count_recur(cnt-i, length, cnt_dict)
            ret = ret + tmp
            cnt_dict[cnt-i] = tmp
    return ret

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('usage: python3 exe num')
        sys.exit(0)
    ret = 0
    cnt = int(sys.argv[1])
    for l in range(2,min(5,cnt+1)):
        cnt_dict = {}
        #decrease 1 means no one tile has been replaced
        tmp = count_recur(cnt, l, cnt_dict) - 1
        ret = ret + tmp
    print(str(ret))
