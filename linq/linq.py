from collections import defaultdict


class Linq:
    def __init__(self, generator):
        self.__generator = generator

    def select(self, func=lambda x: x):
        return Linq(func(item) for item in self.__generator)

    def flatten(self):
        return Linq(item for sublist in self.__generator for item in sublist)

    def where(self, func=lambda x: True):
        return Linq(filter(func, self.__generator))

    def take(self, n=1):
        return Linq(zip(self.__generator, range(n))).select(lambda x: x[0])

    def group_by(self, func=lambda x: x):
        groups = defaultdict(list)
        for item in self.__generator:
            groups[func(item)].append(item)
        return Linq(iter(groups.items()))

    def order_by(self, func=None, reverse=False):
        return Linq(sorted(self.__generator, key=func, reverse=reverse))

    def to_list(self):
        return list(self.__generator)
