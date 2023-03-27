from cs50 import get_string

def countLetters(digit):

    if digit.isalpha(): return 1
    return 0

def countSentences(digit):

    digits = [".", "!", "?"]
    if digit in digits: return 1
    return 0

def countWords(digit):

    if digit.isspace(): return 1
    return 0

def printGrade(words,letters,sentences):

    l = letters / words * 100
    s = sentences / words * 100

    i = int(0.0588 * l - 0.29 * s - 15.8)

    if i > 16:
        print("Grade 16+")

    elif i > 1 and i < 17:
        print(f"Grade {i}")

    else:
        print("Before Grade 1")

text = get_string("Text: ")
size = len(text)

words,letters,sentences = 0, 0, 0

for i in range(size):

    words += countWords(text[i])
    letters += countLetters(text[i])
    sentences += countSentences(text[i])

printGrade(words + 1,letters,sentences)