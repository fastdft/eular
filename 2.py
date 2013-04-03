even_sum = 0
count = 0
fib = 2
fib_p = 1

while fib <= 4000000:
    if count % 3 == 0:
        even_sum = even_sum + fib
    tmp = fib + fib_p
    fib_p = fib
    fib = tmp
    count = count + 1


print(even_sum)
