import os,sys

a = 3
b = 5
sum_multi = 0
for i in range(3, 1000):
    if i % a == 0:
        sum_multi = sum_multi + i
    elif i % b == 0:
        sum_multi = sum_multi + i

print(sum_multi)
