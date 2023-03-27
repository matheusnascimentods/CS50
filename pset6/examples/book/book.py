from cs50 import get_string

peoples = {
    "Pedro Raul": "97982000",
    "Jair": "11189897"
}

name = get_string("name: ")

if name in peoples:

    number = peoples[name]
    print(f"{name}: {number}")