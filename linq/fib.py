from linq import Linq


def fib_gen():
    x, y = 1, 1
    while True:
        yield x
        x, y = y, x + y


fib = (Linq(fib_gen())
       .where(lambda x: x % 3 == 0)
       .select(lambda x: x ** 2 if x % 2 == 0 else x)
       .take(5)
       .to_list())

print(fib)
