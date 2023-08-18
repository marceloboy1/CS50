from cs50 import get_string

text = get_string("Text:")

letters = 0
words = 1
sentences = 0

for letter in text:
    if letter in ['.','!','?']:
        sentences += 1
    elif letter == ' ':
        words += 1
    elif letter.isalpha():
        letters +=1

print("Letters:", letters)
print("Words:", words)
l = (letters * 100) / words
s = (sentences * 100) / words
grade = int(((0.0588 * l) - (0.296 * s) - 15.8)+0.5)


if grade < 1:
    print("Before Grade 1")
elif grade > 16:
    print("Grade 16+")
else:
    print("Grade", grade)
