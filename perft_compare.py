inp = ""

#Mine perft result
mine = dict()
inp = input()
while inp != '':
    move, count = tuple(inp.split(' '))
    move = move[:-1]
    count = int(count)
    mine[move] = count
    inp = input()

#Stockfish perft result
stock = dict()
inp = input()
while inp != '':
    move, count = tuple(inp.split(' '))
    move = move[:-1]
    move = move[0:2] + '-' + move[2:4]
    count = int(count)
    stock[move] = count
    inp = input()

for mv in mine:
    if mv not in stock:
        print(mv + " is excess")
    elif mine[mv] != stock[mv]:
        print("Mine " + mv + " is", mine[mv], " and stockfish's is", stock[mv])

for mv in stock:
    if mv not in mine:
        print(mv + " is missing")
