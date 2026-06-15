def hamming(state, goal):
    count = 0
    for i in range(3):
        for j in range(3):
            if state[i][j] != 0 and state[i][j] != goal[i][j]:
                count = count + 1
    return count


def find_zero(state):
    for i in range(3):
        for j in range(3):
            if state[i][j] == 0:
                return i, j


def copy_state(state):
    new = []
    for i in range(3):
        row = []
        for j in range(3):
            row.append(state[i][j])
        new.append(row)
    return new


def astar(start, goal):
    open_list = []
    visited = []

    open_list.append([start, 0])   # [state, g]

    steps = 0

    while len(open_list) > 0:

        # find best (minimum f)
        best_index = 0
        for i in range(len(open_list)):
            s = open_list[i][0]
            g = open_list[i][1]

            s2 = open_list[best_index][0]
            g2 = open_list[best_index][1]

            f = g + hamming(s, goal)
            f2 = g2 + hamming(s2, goal)

            if f < f2:
                best_index = i

        current = open_list[best_index][0]
        g = open_list[best_index][1]

        open_list.pop(best_index)

        print("\nStep", steps)
        for i in range(3):
            print(current[i])

        steps = steps + 1

        if current == goal:
            print("\nGoal Reached!")
            print("Total steps (cost g(n)) =", g)
            return

        visited.append(current)

        x, y = find_zero(current)

        moves = [(-1,0),(1,0),(0,-1),(0,1)]

        for move in moves:
            nx = x + move[0]
            ny = y + move[1]

            if nx >= 0 and nx < 3 and ny >= 0 and ny < 3:
                new_state = copy_state(current)

                # swap
                temp = new_state[x][y]
                new_state[x][y] = new_state[nx][ny]
                new_state[nx][ny] = temp

                if new_state not in visited:
                    open_list.append([new_state, g + 1])

print("Enter Initial State:")
start = []
for i in range(3):
    row = list(map(int, input().split()))
    start.append(row)

print("Enter Goal State:")
goal = []
for i in range(3):
    row = list(map(int, input().split()))
    goal.append(row)

astar(start, goal)