#include <stdio.h>

extern int shortest_distance[8];
/*
    棋盘初始化函数
    0 - 空， 1 - 白， 2 - 黑
*/
void ChessboardInit(int **Chessboard)
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if( (i == 3 & j == 3) |
                (i == 4 & j == 4) )
            {
                Chessboard[i][j] = 1;
            }
            else if((i == 3 & j == 4) |
                    (i == 4 & j == 3) )
            {
                Chessboard[i][j] = 2;
            }
            else
            {
                Chessboard[i][j] = 0;
            }
        }
    }
}

/*
    寻找最临近的相同颜色的棋子的距离

      1      2      3
       \     |     /
        \    |    /
     0 --   方向  -- 4
        /    |    \
       /     |     \
      7      6      5      
*/
int ShortestDistance(int chesscolor, int direction, int **chessboard, int row, int col)
{
    int shortest_distance = -1;
    switch (direction)
    {
    case 0:
        for(int i = col - 1; i >= 0; i--)
        {
            if(chessboard[row][i] == chesscolor & shortest_distance < 0)
            {
                shortest_distance = col - i;
                break;
            }
        }
        break;
    case 1:
        for(int i = row - 1; i >= 0; i--)
        {
            for(int j = col - 1; j >= 0; j--)
            {
                if(chessboard[i][j] == chesscolor)
                {
                    shortest_distance = row - i;
                    break;
                }
            }
            if(shortest_distance > 0)
            {
                break;
            }
        }
        break;
    case 2:
        for(int i = row - 1; i >= 0; i--)
        {
            if(chessboard[i][col] == chesscolor & shortest_distance < 0)
            {
                shortest_distance = row - i;
                break;
            }
        }
        break;
    case 3:
        for(int i = row - 1; i >= 0; i--)
        {
            for(int j = col + 1; j < 8; j++)
            {
                if(chessboard[i][j] == chesscolor)
                {
                    shortest_distance = row - i;
                    break;
                }
            }
            if(shortest_distance > 0)
            {
                break;
            }
        }
        break;
    case 4:
        for(int i = col + 1; i < 8; i++)
        {
            if(chessboard[row][i] == chesscolor & shortest_distance < 0)
            {
                shortest_distance = i - col;
                break;
            }
        }
        break;
    case 5:
        for(int i = row + 1; i < 8; i++)
        {
            for(int j = col + 1; j < 8; j++)
            {
                if(chessboard[i][j] == chesscolor)
                {
                    shortest_distance = i - row;
                    break;
                }
            }
            if(shortest_distance > 0)
            {
                break;
            }
        }
        break;
    case 6:
        for(int i = row + 1; i < 8; i++)
        {
            if(chessboard[i][col] == chesscolor & shortest_distance < 0)
            {
                shortest_distance = i - row;
                break;
            }
        }
        break;
    case 7:
        for(int i = row + 1; i < 8; i++)
        {
            for(int j = col - 1; j >= 0; j--)
            {
                if(chessboard[i][j] == chesscolor)
                {
                    shortest_distance = i - row;
                    break;
                }
            }
            if(shortest_distance > 0)
            {
                break;
            }
        }
        break;
    default:
        break;
    }

    return shortest_distance;
}

/*
    更新新放置的棋子所在位置八个方向上的相同颜色的棋子的最短距离
*/
void UpdateShortestDistance(int **chessboard, int chesscolor, int row, int col)
{
    for(int i = 0; i < 8; i++)
    {
        shortest_distance[i] = ShortestDistance(chesscolor, i, chessboard, row, col);
    }
}

int AllowFlip(int **chessboard, int begin_row, int begin_col, int end_row, int end_col) // 默认begin_row,begin_col 和 end_row,end_col之间形成45度斜线
{
    int chesscolor = chessboard[begin_row][begin_col];
    if(chesscolor == 0) // 如果该棋子位置为空，则不允许翻转
    {
        return 0;
    }
    int row = begin_row + (begin_row > end_row ? -1 : 1);
    int col = begin_col + (begin_col > end_col ? -1 : 1);
    
    while(row != end_row)
    {
        if(chessboard[row][col] == 0 | chessboard[row][col] == chesscolor)  // 中间路径如果有空位置或者有颜色相同的棋子，则
        {
            return 0;
        }
        row += (begin_row > end_row ? -1 : 1);
        col += (begin_col > end_col ? -1 : 1);
    }
    if(chessboard[end_row][end_col] != chesscolor)
    {
        return 0;
    }
    return 1;
}

void FlipOneDirection(int **chessboard, int begin_row, int begin_col, int direction, int flip_len)
{
    int chesscolor = chessboard[begin_row][begin_col];
    int row = begin_row;
    int col = begin_col;
    int flipped_len = 0;
    while(flipped_len < flip_len)
    {
        chessboard[row][col] = chesscolor;
        if(direction % 4 != 0)
        {
            if(direction < 4)
            {
                row -= 1;
            }
            else 
            {
                row += 1;
            }
        }
        if(direction % 4 != 2)
        {
            if(direction > 2 && direction < 6)
            {
                col += 1;
            }
            else 
            {
                col -= 1;
            }
        }
        flipped_len++;
    }
}
/*
    翻转棋子函数
    刚下的棋子处从八个方向计算最短的相同棋子的距离，将最短的距离的所有方向上的棋子全部翻转过来
*/
void FlipChess(int **chessboard, int row, int col, int chesscolor)
{
    int tmp_shortest_distance = -1;
    //更新新放置棋子到各个方向相同颜色棋子的最短距离
    UpdateShortestDistance(chessboard, chesscolor, row, col);
    //找到最短距离
    for(int i = 0; i < 8; i++)
    {
        if(shortest_distance[i] >= 2)
        {
            if((tmp_shortest_distance < 0) | (tmp_shortest_distance > shortest_distance[i]))
            {
                tmp_shortest_distance = shortest_distance[i];
            }
        }
    }
    
    for(int i = 0; i < 8; i++)
    {
        if(shortest_distance[i] == tmp_shortest_distance)
        {
            FlipOneDirection(chessboard, row, col, i, tmp_shortest_distance + 1);
        }
    }
}