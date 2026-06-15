import itertools

def solve(word1, word2, result):
    letters = list(set(word1 + word2 + result))

    if len(letters) > 10:
        print("Too many letters")
        return

    for p in itertools.permutations(range(10), len(letters)):
        assign = dict(zip(letters, p))

        # no leading zero
        if assign[word1[0]] == 0 or assign[word2[0]] == 0 or assign[result[0]] == 0:
            continue

        # convert words to numbers
        n1 = int("".join(str(assign[ch]) for ch in word1))
        n2 = int("".join(str(assign[ch]) for ch in word2))
        n3 = int("".join(str(assign[ch]) for ch in result))

        if n1 + n2 == n3:
            print("\nSolution Found:")
            print(assign)
            print(n1, "+", n2, "=", n3)
            return

    print("No solution found")


# ===== INPUT =====
word1 = input("Enter first word: ").upper()
word2 = input("Enter second word: ").upper()
result = input("Enter result word: ").upper()

solve(word1, word2, result)