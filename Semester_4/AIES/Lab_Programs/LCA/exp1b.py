def hamming(state, goal):
    count = 0
    for i in range(3):
        for j in range(3):
            if state[i][j] != 0 and state[i][j] != goal[i][j]:
                count = count + 1
    return count


def manhattan(state, goal):
    dist = 0
    for i in range(3):
        for j in range(3):
            val = state[i][j]

            if val != 0:
                for x in range(3):
                    for y in range(3):
                        if goal[x][y] == val:
                            dist = dist + abs(x - i) + abs(y - j)

    return dist

print("Enter State:")
state = []
for i in range(3):
    row = list(map(int, input().split()))
    state.append(row)

print("Enter Goal:")
goal = []
for i in range(3):
    row = list(map(int, input().split()))
    goal.append(row)

print("Hamming Distance =", hamming(state, goal))
print("Manhattan Distance =", manhattan(state, goal))