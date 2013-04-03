a = 0
for i in range(1, 101):
    sum1 = 0;
    for j in range(i+1, 101):
        sum1 = sum1 + j
    a = a + sum1 * i

print(str(a * 2))
