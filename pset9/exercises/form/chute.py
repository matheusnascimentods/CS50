secret = 42

chute = input("chute: ")
print(f'você digitou {chute}')

if secret == chute:
    print("Você acertou")
else:
    print("Você errou")