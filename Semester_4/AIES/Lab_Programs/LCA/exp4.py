board = [" " for i in range(9)]

def print_board():
    print()
    print(board[0], "|", board[1], "|", board[2])
    print("--+---+--")
    print(board[3], "|", board[4], "|", board[5])
    print("--+---+--")
    print(board[6], "|", board[7], "|", board[8])
    print()

def check_winner(b, player):
    win_positions = [
        [0,1,2],[3,4,5],[6,7,8],
        [0,3,6],[1,4,7],[2,5,8],
        [0,4,8],[2,4,6]
    ]

    for pos in win_positions:
        if b[pos[0]] == b[pos[1]] == b[pos[2]] == player:
            return True
    return False


def is_draw(b):
    return " " not in b


def minimax(b, is_max):
    if check_winner(b, "O"):
        return 1
    if check_winner(b, "X"):
        return -1
    if is_draw(b):
        return 0

    if is_max:
        best = -100
        for i in range(9):
            if b[i] == " ":
                b[i] = "O"
                val = minimax(b, False)
                b[i] = " "
                if val > best:
                    best = val
        return best
    else:
        best = 100
        for i in range(9):
            if b[i] == " ":
                b[i] = "X"
                val = minimax(b, True)
                b[i] = " "
                if val < best:
                    best = val
        return best

def best_move():
    best_val = -100
    move = -1

    for i in range(9):
        if board[i] == " ":
            board[i] = "O"
            val = minimax(board, False)
            board[i] = " "

            if val > best_val:
                best_val = val
                move = i

    return move

while True:
    print_board()

    pos = int(input("Enter position (0-8): "))
    if board[pos] != " ":
        print("Invalid move")
        continue

    board[pos] = "X"

    if check_winner(board, "X"):
        print_board()
        print("You Win!")
        break

    if is_draw(board):
        print_board()
        print("Draw!")
        break

    comp = best_move()
    board[comp] = "O"
    print("Computer chose:", comp)

    if check_winner(board, "O"):
        print_board()
        print("Computer Wins!")
        break

    if is_draw(board):
        print_board()
        print("Draw!")
        break