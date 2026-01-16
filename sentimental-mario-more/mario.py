height = ""

while (not(height.isdigit())) or int(height) <= 0 or int(height) > 8:
    height = input("Height = ")

height = int(height)

bricks = 0
for row in range(0, height, 1):   #start from 0 and create rows until height value reached
    bricks += 1
    space = height - bricks
    # print(f"line {row} ", end = "")

    for _ in range(0, space, 1):  #start from spaces = height - bricks, where x starts from 1 and keeps increasing until height reached
        # print(f"space = {space} ", end = "")
        print(" ", end = "")

    for _ in range(0, bricks, 1):   #start from bricks starts from 1 and until height
        # print(f"bricks = {bricks} ", end = "")
        print("#", end = "")

    print("  ", end = "")

    for _ in range(0, bricks, 1):   #start from bricks starts from 1 and until height
        # print(f"bricks = {bricks} ", end = "")
        print("#", end = "")

    # for _ in range(0, space, 1):  #start from spaces = height - bricks, where x starts from 1 and keeps increasing until height reached
    #     # print(f"space = {space} ", end = "")
    #     print(" ", end = "")

    print()

