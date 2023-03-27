from cs50 import get_float

def printCoins(money):

    cents, total = [25, 10, 5, 1], 0

    for i in range(4):

        coins = int(money / cents[i])
        money = money - (cents[i] * coins)
        total = total + coins

        if money == 0: break

    print(total)


while True:

    cash = get_float("Change owed: ")
    if cash > 0: break

cash = int(cash * 100)
printCoins(cash)
