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