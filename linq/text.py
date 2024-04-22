from linq import Linq

with open('text.txt', 'r') as file:
    lines = file.readlines()

    word_count = (Linq(lines)
                  .select(lambda x: x.split(' '))
                  .flatten()
                  .group_by()
                  .select(lambda x: (x[0], len(x[1])))
                  .order_by(lambda x: x[1], reverse=True)
                  .take(15)
                  .to_list())

    for item in word_count:
        print(item)
