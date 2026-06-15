
def print_board(board):
    for row in board:
        print(" | ".join(row))
        print("-" * 9)

def check_winner(board):
    for row in board:
        if row[0] == row[1] == row[2] != " ":
            return row[0]
    
    for col in range(3):
        if board[0][col] == board[1][col] == board[2][col] != " ":
            return board[0][col]
    
    if board[0][0] == board[1][1] == board[2][2] != " ":
        return board[0][0]
    if board[0][2] == board[1][1] == board[2][0] != " ":
        return board[0][2]
    
    if all(board[i][j] != " " for i in range(3) for j in range(3)):
        return "Draw"
    
    return None

def minimax(board, is_maximizing):
    winner = check_winner(board)
    
    if winner == "X":
        return -1
    elif winner == "O":
        return 1
    elif winner == "Draw":
        return 0
    
    if is_maximizing:
        best_score = -float('inf')
        for i in range(3):
            for j in range(3):
                if board[i][j] == " ":
                    board[i][j] = "O"
                    score = minimax(board, False)
                    board[i][j] = " "
                    best_score = max(score, best_score)
        return best_score
    else:
        best_score = float('inf')
        for i in range(3):
            for j in range(3):
                if board[i][j] == " ":
                    board[i][j] = "X"
                    score = minimax(board, True)
                    board[i][j] = " "
                    best_score = min(score, best_score)
        return best_score

def best_move(board):
    best_score = -float('inf')
    move = None
    
    for i in range(3):
        for j in range(3):
            if board[i][j] == " ":
                board[i][j] = "O"
                score = minimax(board, False)
                board[i][j] = " "
                
                if score > best_score:
                    best_score = score
                    move = (i, j)
    
    return move

def main():
    board = [[" " for _ in range(3)] for _ in range(3)]
    print("Tic-Tac-Toe: You are X, AI is O")
    print_board(board)
    
    while True:
        print("\nYour turn (X)")
        try:
            row = int(input("Enter row (0-2): "))
            col = int(input("Enter col (0-2): "))
            
            if board[row][col] != " ":
                print("Cell occupied! Try again.")
                continue
            
            board[row][col] = "X"
            print_board(board)
            
            winner = check_winner(board)
            if winner:
                if winner == "X":
                    print("You win!")
                elif winner == "Draw":
                    print("It's a draw!")
                break
            
            print("\nAI's turn (O)")
            move = best_move(board)
            if move:
                board[move[0]][move[1]] = "O"
                print_board(board)
                
                winner = check_winner(board)
                if winner:
                    if winner == "O":
                        print("AI wins!")
                    elif winner == "Draw":
                        print("It's a draw!")
                    break
        
        except (ValueError, IndexError):
            print("Invalid input! Try again.")

if __name__ == "__main__":
    main()
