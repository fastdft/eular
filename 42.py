import os, sys, re

def gen_trian_number(max_num):
    ret = set() 
    now = 1
    n = 1
    while now <= max_num:
        ret.add(now)
        n = n + 1
        now = now + n
    return ret

def calc_word(word):
    ret = 0
    word = word.lower()
    for c in word:
        ret = ret + ord(c) - ord('a') + 1
    return ret

if __name__ == '__main__':
    trian_number = gen_trian_number(26 * 40)
    with open("words.txt") as fin:
        count = 0
        s = fin.read()
        words = re.findall("\w+", s)
        for word in words:
            if calc_word(word) in trian_number:
                print(word)
                count = count + 1

        print(str(count))

