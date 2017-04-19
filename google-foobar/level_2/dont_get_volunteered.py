import sys

board_dim = 8
nums = [-2, -1, 1, 2]
offsets = []
for i in nums:
    j = 3 - abs(i)
    offsets.append([i,j])
    offsets.append([i,-j])

def print_board(board):
    print '['
    for row in board:
        print row
    print ']'

def answer(src, dest):
    src_row = src / board_dim
    src_col = src % board_dim
    dest_row = dest / board_dim
    dest_col = dest % board_dim

    board = [[sys.maxint]*board_dim for _ in xrange(board_dim)]
    board[src_row][src_col] = 0
    
    populate_board(board, src_row, src_col)

    return board[dest_row][dest_col]

# breadth first search
def populate_board(board, row, col):
    i = 0
    queue = [[row, col]]
    while i < len(queue):
        row = queue[i][0]
        col = queue[i][1]
        i = i + 1
        new_cost = board[row][col] + 1
        for offset in offsets:
            new_row = row + offset[0]
            new_col = col + offset[1]
            if 0 <= new_row < board_dim and 0 <= new_col < board_dim:
                # print new_row, new_col
                # print_board()
                if new_cost < board[new_row][new_col]:
                    queue.append([new_row, new_col])
                    board[new_row][new_col] = new_cost

print answer(19, 36) == 1
print answer(0, 1) == 3
