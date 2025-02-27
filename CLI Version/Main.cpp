// Chess Engine

#include <iostream>
#include <string>
using namespace std;

struct AnsiiCodeEscapes
{
    // Standard text colors
    const string RESET = "\033[0m";
    const string BLACK = "\033[30m";
    const string RED = "\033[31m";
    const string GREEN = "\033[32m";
    const string YELLOW = "\033[33m";
    const string BLUE = "\033[34m";
    const string MAGENTA = "\033[35m";
    const string CYAN = "\033[36m";
    const string WHITE = "\033[37m";

    // Bright text colors
    const string B_BLACK = "\033[90m";
    const string B_RED = "\033[91m";
    const string B_GREEN = "\033[92m";
    const string B_YELLOW = "\033[93m";
    const string B_BLUE = "\033[94m";
    const string B_MAGENTA = "\033[95m";
    const string B_CYAN = "\033[96m";
    const string B_WHITE = "\033[97m";

    // Background colors
    const string BG_BLACK = "\033[40m";
    const string BG_RED = "\033[41m";
    const string BG_GREEN = "\033[42m";
    const string BG_YELLOW = "\033[43m";
    const string BG_BLUE = "\033[44m";
    const string BG_MAGENTA = "\033[45m";
    const string BG_CYAN = "\033[46m";
    const string BG_WHITE = "\033[47m";

    // Bright background colors
    const string BG_B_BLACK = "\033[100m";
    const string BG_B_RED = "\033[101m";
    const string BG_B_GREEN = "\033[102m";
    const string BG_B_YELLOW = "\033[103m";
    const string BG_B_BLUE = "\033[104m";
    const string BG_B_MAGENTA = "\033[105m";
    const string BG_B_CYAN = "\033[106m";
    const string BG_B_WHITE = "\033[107m";

    // Text styles
    const string BOLD = "\033[1m";
    const string DIM = "\033[2m";
    const string ITALIC = "\033[3m";
    const string UNDERLINE = "\033[4m";
    const string BLINK = "\033[5m";
    const string FAST_BLINK = "\033[6m";
    const string REVERSED = "\033[7m";
    const string HIDDEN = "\033[8m";
    const string STRIKETHROUGH = "\033[9m";
};
AnsiiCodeEscapes as;

//   \033[38;2;<r>;<g>;<b>m  # Foreground
//   \033[48;2;<r>;<g>;<b>m  # Background

struct Piece
{
    string representation;
    string type;

    int color; // 1 for white, 0 for black, 888 for empty
};

inline char YtoFiles(int y)
{
    return y + 96;
}

void ResetBoard(Piece board[][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board[i][j].representation = " ";
            board[i][j].color = 888;
        }
    }
}

void FENtoBoard(Piece board[][8], string fen)
{
    string pieceSymbols[128] = {};
    pieceSymbols['P'] = "P";
    pieceSymbols['N'] = "N";
    pieceSymbols['B'] = "B";
    pieceSymbols['R'] = "R";
    pieceSymbols['Q'] = "Q";
    pieceSymbols['K'] = "K"; // White pieces
    pieceSymbols['p'] = "p";
    pieceSymbols['n'] = "n";
    pieceSymbols['b'] = "b";
    pieceSymbols['r'] = "r";
    pieceSymbols['q'] = "q";
    pieceSymbols['k'] = "k"; // Black pieces

    int row = 0, col = 0;
    for (char ch : fen)
    {
        if (ch == '/')
        {
            row++;
            col = 0;
        }
        else if (isdigit(ch))
        {
            col += ch - '0';
        }
        else if (isalpha(ch))
        {
            board[row][col].representation = pieceSymbols[ch];
            board[row][col].type = pieceSymbols[ch];
            col++;
        }
        else
        {
            break;
        }
    }
}

void DrawBoard(Piece board[][8])
{
    system("cls");
    string white = as.BOLD + "\033[38;2;255;255;255m";
    string black = as.BOLD + "\033[38;2;0;0;0m";

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j].representation == "p" || board[i][j].representation == "r" || board[i][j].representation == "n" || board[i][j].representation == "b" || board[i][j].representation == "q" || board[i][j].representation == "k")
            {
                if (board[i][j].representation == "p")
                {
                    board[i][j].representation = "P";
                    board[i][j].type = "P";
                }
                else if (board[i][j].representation == "r")
                {
                    board[i][j].representation = "R";
                    board[i][j].type = "R";
                }
                else if (board[i][j].representation == "n")
                {
                    board[i][j].representation = "N";
                    board[i][j].type = "N";
                }
                else if (board[i][j].representation == "b")
                {
                    board[i][j].representation = "B";
                    board[i][j].type = "B";
                }
                else if (board[i][j].representation == "q")
                {
                    board[i][j].representation = "Q";
                    board[i][j].type = "Q";
                }
                else if (board[i][j].representation == "k")
                {
                    board[i][j].representation = "K";
                    board[i][j].type = "K";
                }

                board[i][j].representation = black + board[i][j].representation;
                board[i][j].color = 0;
            }
            else if (board[i][j].representation == "P" || board[i][j].representation == "R" || board[i][j].representation == "N" || board[i][j].representation == "B" || board[i][j].representation == "Q" || board[i][j].representation == "K")
            {
                board[i][j].representation = white + board[i][j].representation;
                board[i][j].color = 1;
            }
        }
    }

    string backDark = "\033[48;2;240;128;128m";
    string backLight = "\033[48;2;255;182;193m";
    string borderBG = "\033[48;2;32;32;32m";
    string borderText = as.DIM + "\033[38;2;255;255;255m";
    string sep = "";
    int n = 8, f1 = 8, f2 = 8;
    string offX = "                          ", offY = "\n"; // 3:1
    cout << offY << offX << borderBG + borderText << as.BOLD + " " << "   a  b  c  d  e  f  g  h    " << as.RESET << "\n";
    // cout << offX << borderBG + borderText + as.BOLD + "   " + as.RESET << as.DIM + " --------------------------------- " << as.RESET << borderBG + borderText + as.BOLD << "   " << as.RESET << "\n";

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (j == 1)
            {
                if (i % 2 != 0)
                {
                    cout << offX << borderBG + borderText << as.BOLD + " " << f1 << " " << as.RESET << as.DIM + sep + as.RESET << backDark << as.BOLD << " " << board[i - 1][j - 1].representation << " " << as.RESET;
                    f1--;
                }
                else
                {
                    cout << offX << borderBG + borderText << as.BOLD + " " << f1 << " " << as.RESET << as.DIM + sep + as.RESET << backLight << as.BOLD << " " << board[i - 1][j - 1].representation << " " << as.RESET;
                    f1--;
                }
            }
            else if (j == n)
            {
                if (i % 2 == 0)
                {
                    cout << "" + as.DIM + sep + as.RESET << backDark << as.BOLD << " " << board[i - 1][j - 1].representation << " " + as.RESET << as.DIM << sep + as.RESET << as.RESET + borderBG + borderText << as.BOLD + " " << f2 << " " << as.RESET;
                    f2--;
                }
                else
                {
                    cout << "" + as.DIM + sep + as.RESET << backLight << as.BOLD << " " << board[i - 1][j - 1].representation << " " + as.RESET << as.DIM << sep + as.RESET << as.RESET + borderBG + borderText << as.BOLD + " " << f2 << " " << as.RESET;
                    f2--;
                }
            }
            else
            {
                if (i % 2 == 0 && j % 2 == 0 || i % 2 != 0 && j % 2 != 0)
                {
                    cout << "" + as.DIM + sep + as.RESET << backDark + as.BOLD << " " << board[i - 1][j - 1].representation << " " << as.RESET;
                }
                else
                {
                    cout << "" + as.DIM + sep + as.RESET << backLight + as.BOLD << " " << board[i - 1][j - 1].representation << " " << as.RESET;
                }
            }
        }
        cout << "\n";
        // cout << offX << borderBG + borderText + as.BOLD + "   " + as.RESET << as.DIM << " --------------------------------- " << as.RESET << borderBG + borderText + as.BOLD << "   " << as.RESET << "\n";
    }
    cout << offX << borderBG + borderText << as.BOLD + " " << "   a  b  c  d  e  f  g  h    " << as.RESET << offY << "\n";
}

int **CalculateLegalMoves(Piece board[][8], bool color, int x, int y, int &moveCount)
{
    moveCount = 0;
    int **moves = new int *[64];
    for (int i = 0; i < 64; i++)
        moves[i] = new int[2];

    if (board[x][y].type == "P") // Pawn
    {
        if (color == 1) // White moves up
        {
            if (x - 1 >= 0 && board[x - 1][y].color == 888)
            {
                moves[moveCount][0] = x - 1;
                moves[moveCount][1] = y;
                moveCount++;
            }
            if (x == 6 && board[x - 1][y].color == 888 && board[x - 2][y].color == 888)
            {
                moves[moveCount][0] = x - 2;
                moves[moveCount][1] = y;
                moveCount++;
            }
            if (x - 1 >= 0 && y - 1 >= 0 && board[x - 1][y - 1].color != 888 && board[x - 1][y - 1].color != color)
            {
                moves[moveCount][0] = x - 1;
                moves[moveCount][1] = y - 1;
                moveCount++;
            }
            if (x - 1 >= 0 && y + 1 < 8 && board[x - 1][y + 1].color != 888 && board[x - 1][y + 1].color != color)
            {
                moves[moveCount][0] = x - 1;
                moves[moveCount][1] = y + 1;
                moveCount++;
            }
        }
        else // Black moves down
        {
            if (x + 1 < 8 && board[x + 1][y].color == 888)
            {
                moves[moveCount][0] = x + 1;
                moves[moveCount][1] = y;
                moveCount++;
            }
            if (x == 1 && board[x + 1][y].color == 888 && board[x + 2][y].color == 888)
            {
                moves[moveCount][0] = x + 2;
                moves[moveCount][1] = y;
                moveCount++;
            }
            if (x + 1 < 8 && y - 1 >= 0 && board[x + 1][y - 1].color != 888 && board[x + 1][y - 1].color != color)
            {
                moves[moveCount][0] = x + 1;
                moves[moveCount][1] = y - 1;
                moveCount++;
            }
            if (x + 1 < 8 && y + 1 < 8 && board[x + 1][y + 1].color != 888 && board[x + 1][y + 1].color != color)
            {
                moves[moveCount][0] = x + 1;
                moves[moveCount][1] = y + 1;
                moveCount++;
            }
        }
    }
    else if (board[x][y].type == "N") // Knight
    {
        int knightMoves[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
        for (int i = 0; i < 8; i++)
        {
            int nx = x + knightMoves[i][0];
            int ny = y + knightMoves[i][1];
            if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8 && (board[nx][ny].color == 888 || board[nx][ny].color != color))
            {
                moves[moveCount][0] = nx;
                moves[moveCount][1] = ny;
                moveCount++;
            }
        }
    }
    else if (board[x][y].type == "R") // Rook
    {
        int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        for (int d = 0; d < 4; d++)
        {
            int nx = x, ny = y;
            while (true)
            {
                nx += directions[d][0];
                ny += directions[d][1];
                if (nx < 0 || nx >= 8 || ny < 0 || ny >= 8)
                    break;
                if (board[nx][ny].color == 888)
                {
                    moves[moveCount][0] = nx;
                    moves[moveCount][1] = ny;
                    moveCount++;
                }
                else
                {
                    if (board[nx][ny].color != color)
                    {
                        moves[moveCount][0] = nx;
                        moves[moveCount][1] = ny;
                        moveCount++;
                    }
                    break;
                }
            }
        }
    }
    else if (board[x][y].type == "B") // Bishop
    {
        int directions[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
        for (int d = 0; d < 4; d++)
        {
            int nx = x, ny = y;
            while (true)
            {
                nx += directions[d][0];
                ny += directions[d][1];
                if (nx < 0 || nx >= 8 || ny < 0 || ny >= 8)
                    break;
                if (board[nx][ny].color == 888)
                {
                    moves[moveCount][0] = nx;
                    moves[moveCount][1] = ny;
                    moveCount++;
                }
                else
                {
                    if (board[nx][ny].color != color)
                    {
                        moves[moveCount][0] = nx;
                        moves[moveCount][1] = ny;
                        moveCount++;
                    }
                    break;
                }
            }
        }
    }
    else if (board[x][y].type == "Q") // Queen (combines Rook and Bishop moves)
    {
        int directions[8][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
        for (int d = 0; d < 8; d++)
        {
            int nx = x, ny = y;
            while (true)
            {
                nx += directions[d][0];
                ny += directions[d][1];
                if (nx < 0 || nx >= 8 || ny < 0 || ny >= 8)
                    break;
                if (board[nx][ny].color == 888)
                {
                    moves[moveCount][0] = nx;
                    moves[moveCount][1] = ny;
                    moveCount++;
                }
                else
                {
                    if (board[nx][ny].color != color)
                    {
                        moves[moveCount][0] = nx;
                        moves[moveCount][1] = ny;
                        moveCount++;
                    }
                    break;
                }
            }
        }
    }
    else if (board[x][y].type == "K") // King
    {
        for (int dx = -1; dx <= 1; dx++)
        {
            for (int dy = -1; dy <= 1; dy++)
            {
                if (dx == 0 && dy == 0)
                    continue;
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8 && (board[nx][ny].color == 888 || board[nx][ny].color != color))
                {
                    moves[moveCount][0] = nx;
                    moves[moveCount][1] = ny;
                    moveCount++;
                }
            }
        }
    }

    return moves;
}

void PlayerMove(Piece board[][8], bool color = 1)
{
    struct PieceType
    {
        string type;
        string name;
    };

    PieceType pieces[6] = {{"P", "Pawn"}, {"R", "Rook"}, {"N", "Knight"}, {"B", "Bishop"}, {"Q", "Queen"}, {"K", "King"}};

    int validPieceCount = 0;
    int validPieces[6] = {}; // Stores indexes of pieces that can move

    string colorName = color == 1 ? "white" : "black";
    cout << as.BOLD << "Select a " << colorName << " piece to move:\n"
         << as.RESET;

    for (int i = 0; i < 6; i++)
    {
        bool hasValidMove = false;

        for (int x = 0; x < 8 && !hasValidMove; x++)
        {
            for (int y = 0; y < 8 && !hasValidMove; y++)
            {
                if (board[x][y].color == color && board[x][y].type == pieces[i].type)
                {
                    int moveCount;
                    int **moves = CalculateLegalMoves(board, color, x, y, moveCount);

                    if (moveCount > 0)
                    {
                        hasValidMove = true;
                        validPieces[validPieceCount++] = i;
                    }

                    for (int j = 0; j < 64; j++)
                        delete[] moves[j];
                    delete[] moves;
                }
            }
        }

        if (hasValidMove)
        {
            cout << as.B_YELLOW + as.BOLD + as.B_YELLOW << validPieceCount << ". " << pieces[i].name << as.RESET << "\n";
        }
    }

    if (validPieceCount == 0)
    {
        cout << as.B_RED << "No pieces have legal moves!" << as.RESET << "\n";
        cout << "STALEMATE";
        return;
    }

    int selectedPiece;
    if (validPieceCount == 1)
    {
        selectedPiece = 1; // Auto-select if only one type of piece has a move
    }
    else
    {
        while (true)
        {
            cout << as.BOLD + "Select a piece to move (1 - " << validPieceCount << "): ";
            cin >> selectedPiece;
            if (cin.fail() || selectedPiece < 1 || selectedPiece > validPieceCount)
            {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << as.B_RED << "Invalid input. Please enter a number between 1 and " << validPieceCount << "." << as.RESET << "\n";
                continue;
            }
            cout << "\n";
            break;
        }
    }

    string pieceType = pieces[validPieces[selectedPiece - 1]].type;

    // Find all pieces of this type that can move
    int pieceCount = 0;
    int positions[16][2]; // Maximum 16 of any type

    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            if (board[x][y].color == color && board[x][y].type == pieceType)
            {
                int moveCount;
                int **moves = CalculateLegalMoves(board, color, x, y, moveCount);

                if (moveCount > 0)
                {
                    positions[pieceCount][0] = x;
                    positions[pieceCount][1] = y;
                    pieceCount++;
                }

                for (int j = 0; j < 64; j++)
                    delete[] moves[j];
                delete[] moves;
            }
        }
    }

    int selectedPieceIndex;
    if (pieceCount == 1)
    {
        selectedPieceIndex = 1; // Auto-select if only one piece of that type exists
    }
    else
    {
        for (int i = 0; i < pieceCount; i++)
        {
            cout << as.B_YELLOW + as.BOLD << i + 1 << ". " << YtoFiles(positions[i][1] + 1) << 8 - positions[i][0] << as.RESET << "    ";
        }
        cout << "\n";

        while (true)
        {
            cout <<as.BOLD + "Select a " << pieceType << " to move (1 - " << pieceCount << "): ";
            cin >> selectedPieceIndex;
            if (cin.fail() || selectedPieceIndex < 1 || selectedPieceIndex > pieceCount)
            {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << as.B_RED << "Invalid input. Please enter a number between 1 and " << pieceCount << "." << as.RESET << "\n";
                continue;
            }
            break;
        }
    }

    int x = positions[selectedPieceIndex - 1][0];
    int y = positions[selectedPieceIndex - 1][1];

    int moveCount;
    int **moves = CalculateLegalMoves(board, color, x, y, moveCount);

    cout << "\n";
    for (int i = 0; i < moveCount; i++)
    {
        cout << as.B_YELLOW + as.BOLD << i + 1 << ". " << YtoFiles(moves[i][1] + 1) << 8 - moves[i][0] << as.RESET << "    ";
    }
    cout << "\n";

    int selectedMove;
    if (moveCount == 1)
    {
        selectedMove = 1;
    }
    else
    {
        while (true)
        {
            cout <<as.BOLD + "Select move (1 - " << moveCount << "): ";
            cin >> selectedMove;
            if (cin.fail() || selectedMove < 1 || selectedMove > moveCount)
            {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << as.B_RED << "Invalid input. Please enter a number between 1 and " << moveCount << "." << as.RESET << "\n";
                continue;
            }
            break;
        }
    }

    int newX = moves[selectedMove - 1][0];
    int newY = moves[selectedMove - 1][1];

    // Apply move
    board[newX][newY] = board[x][y];
    board[x][y].representation = " ";
    board[x][y].type = "";
    board[x][y].color = 888;

    // Free allocated memory
    for (int i = 0; i < 64; i++)
        delete[] moves[i];
    delete[] moves;

    DrawBoard(board);
}

int main()
{
    system("");
    Piece board[8][8];
    ResetBoard(board);

    // SETTING BOARD ACCORDING TO STANDARD FEN NOTATION
    string startFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    FENtoBoard(board, startFEN);

    // cout << "\033[38;2;255;223;0m======================\n|    CHESS ENGINE    |\n======================";
    // while (true)
    // {
    //     /* code */
    // }
    

    // GAME STARTS
    DrawBoard(board);
    while (true)
    {
        PlayerMove(board, 1);
        PlayerMove(board, 0);
    }
    return 0;
}