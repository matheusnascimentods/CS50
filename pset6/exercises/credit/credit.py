from cs50 import get_int

def isAMEX(digits):

    amex = [34, 37]

    if digits in amex: print("AMEX")

    else: print("INVALID")

def isMastercard(digits):

    mastercard = range(50, 56)

    if digits in mastercard: print("MASTERCARD")

    else: print("INVALID")

def isVisa(digits):

    if digits == 4: print("VISA")

    else: print("INVALID")

def printCard(n):

    n = str(n)
    size = len(n)

    if size == 15:

        digits = int(n[0] + n[1])
        isAMEX(digits)

    elif size == 16 and n[0] != "4":

        digits = int(n[0] + n[1])
        isMastercard(n)

    elif size > 12 and size < 17:

        digits = int(n[0])
        isVisa(n)

    else:
        print("INVALID")

n = get_int("Number: ")
printCard(n)
