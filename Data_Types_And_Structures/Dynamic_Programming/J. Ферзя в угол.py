def can_player_win(n, m):

    board = [[0] * m for _ in range(n)]

    board[n - 1][m - 1] = -1

    for i in range(n - 1, -1, -1):
        for j in range(m - 1, -1, -1):

           if board[i][j] == 0:
            win = False

            for move_i in range(i+1,n):

                if board[move_i][j] == -1:
                    win = True
                    break

            for move_j in range(j+1,m):

                if board[i][move_j] == -1:
                     win = True
                     break

            for move_k in range(1, min(n - i, m - j)):

                 if board[i+move_k][j+move_k] == -1:
                    win = True
                    break

            if win:
                board[i][j] = 1
            else:
                 board[i][j] = -1
                    
    return 1 if board[0][0] == 1 else 2

n, m = map(int, input().split())

res = can_player_win(n, m)
print(res)
