from cs50 import get_float

Amount = -1
while Amount < 0:
    Amount = get_float("Change: ")

# Cent Avaialable: 25c , 10c, 5c, 1c
Quarters = 0
Dimes = 0
Nickels = 0
Pennies = 0
Amount = Amount * 100

while Amount != 0:
    if Amount >= 25:
        Quarters = int(Amount/25)
        Amount = Amount % 25
        # print(f"Q {Amount}")
    elif Amount >= 10 and Amount < 25:
        Dimes = int(Amount/10)
        Amount = Amount % 10
        # print(f"D {Amount}")
    elif Amount >= 5 and Amount < 25 and Amount < 10:
        Nickels = int(Amount/5)
        Amount = Amount % 5
        # print(f"N {Amount}")
    elif Amount >= 1 and Amount < 5 and Amount < 25 and Amount < 10:
        Pennies = int(Amount/1)
        Amount = Amount % 1
        # print(f"P {Amount}")
    elif Amount < 1:
        Amount = 0

coins = Quarters + Dimes + Nickels + Pennies
print(f"{coins}")
