from cs50 import get_string

Text = get_string("Text: ")

n = 0
Words = 1
Sentences = 0
Letters = 0

for n in range(len(Text)):
    if Text[n] == " ":
        Words += 1
    elif Text[n] in {'!', '.', '?'}:
        Sentences += 1
    elif Text[n].isalpha(): # not in {",", ";", "-", "'", '"'}:
        Letters += 1

print(f"Words: {Words}")
print(f"Sentences: {Sentences}")
print(f"Letters: {Letters}")

L = (Letters/Words) * 100
S = (Sentences/Words) * 100
Index = (0.0588 * L) - (0.296 * S) - 15.8

if Index >= 16:
    print("Grade 16+")
elif Index < 1:
    print("Before Grade 1")
else:
    Index = round(Index)
    print(f"Grade {Index}")
