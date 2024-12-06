def findNextLetter(word, lines, letterIndex, position, direction):
    i = position[0] + direction[0]
    j = position[1] + direction[1]
    
    if (0 <= i < len(lines)) and (0 <= j < len(lines[i])):  
        if lines[i][j] == word[letterIndex]:  
            letterIndex += 1
            if letterIndex == len(word):
                return True
            else:
                return findNextLetter(word, lines, letterIndex, [i, j], direction)
        else: 
            return False
    else:
        return False

def findXMAS(lines):
    word = "XMAS"
    countWord = 0

    for i in range(len(lines)):
        for j in range(len(lines[i])):
            if lines[i][j] == word[0]: 
                for m in range(-1, 2):
                    for n in range(-1, 2):
                        if m == 0 and n == 0:
                            continue
                        if findNextLetter(word, lines, 1, [i, j], [m, n]):
                            countWord += 1

    print(f"Le mot '{word}' a été trouvé {countWord} fois.")

def findShapeOfXMAS(lines):
    word = "MAS"
    countShape = 0

    lengthWord = len(word)
    if lengthWord < 3 or lengthWord % 2 != 1:
        return

    center = lengthWord // 2

    leftPartWord = word[:center][::-1]
    rightPartWord = word[center + 1:]

    for i in range(len(leftPartWord), len(lines) - len(leftPartWord)):
        for j in range(len(leftPartWord), len(lines[i]) - len(leftPartWord)):
            if lines[i][j] == word[center]: 
                if (
                    (findNextLetter(leftPartWord, lines, 0, [i, j], [-1, -1]) and findNextLetter(rightPartWord, lines, 0, [i, j], [1, 1])) or
                    (findNextLetter(rightPartWord, lines, 0, [i, j], [-1, -1]) and findNextLetter(leftPartWord, lines, 0, [i, j], [1, 1])) 
                ) and (
                    (findNextLetter(leftPartWord, lines, 0, [i, j], [1, -1]) and findNextLetter(rightPartWord, lines, 0, [i, j], [-1, 1])) or
                    (findNextLetter(rightPartWord, lines, 0, [i, j], [1, -1]) and findNextLetter(leftPartWord, lines, 0, [i, j], [-1, 1]))
                ):
                    countShape += 1
                    
    print(f"Le mot '{word}' en forme de X a été trouvé {countShape} fois.")


with open('input.txt', 'r') as file:
    lines = file.readlines()

lines = [line.strip() for line in lines]

findXMAS(lines)
findShapeOfXMAS(lines)

