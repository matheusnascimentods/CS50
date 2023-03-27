def get_positive():

    while True:

        n = int(input("n: "))

        if n > 0: break

    return n

def main():

    x = get_positive()
    print(x)

main()