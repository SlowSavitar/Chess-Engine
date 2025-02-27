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
    string representation; // Their Representation on the board
    string type;           // Pawn, Rook, Knight, Bishop, Queen, King
    int color;             // 1 for white, 0 for black, 888 for empty
    int numberOfLegalMoves;
    int legalMoves[25][2];
};

inline char YtoFiles(int y)
{
    return y + 96;
}

void ResetBoard(Piece[][8]);
void FENtoBoard(Piece[][8], string);
void DrawBoard(Piece[][8]);
void CalculateLegalMoves(Piece[][8]);
void SwapPieces(Piece[][8], int, int, int, int);
void Move(Piece[][8], bool);

int main()
{
    system("");

    Piece board[8][8];
    string startFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"; // Standard starting position

    ResetBoard(board);
    FENtoBoard(board, startFEN);

    DrawBoard(board);
    // Move(board, 1);
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << board[i][j].type << " " << board[i][j].numberOfLegalMoves << "\n";
        }
        
    }
    
    return 0;
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

    int i = 0, j = 0;
    for (char letter : fen)
    {
        if (letter == '/')
        {
            i++;
            j = 0;
        }
        else if (isdigit(letter))
        {
            j += letter - '0';
        }
        else if (isalpha(letter))
        {
            board[i][j].representation = pieceSymbols[letter];
            board[i][j].type = pieceSymbols[letter];
            j++;
        }
        else
        {
            break;
        }
    }
}

void DrawBoard(Piece board[][8])
{
    // board[8 - x][y - 1].representation = as.BOLD + "X";
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            for (int k = 0; k < 25; k++)
            {
                board[i][j].legalMoves[k][0] = 888;
            }
        }
    }

    // CalculateLegalMoves(board);
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
    string offX = "      ", offY = "\n\n"; // 3:1
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

// void CalculateLegalMoves(Piece board[][8])
// {
//     for (int i = 0; i < 8; i++)
//     {
//         for (int j = 0; j < 8; j++)
//         {
//             board[i][j].numberOfLegalMoves = 0; // Reset legal moves

//             if (board[i][j].type == "P") // Pawn
//             {
//                 int legalMovesCount = 0;
//                 if (board[i][j].color == 1) // White Pawn
//                 {
//                     if (i > 0 && board[i - 1][j].color == 888) // Move forward
//                     {
//                         board[i][j].legalMoves[legalMovesCount][0] = i - 1;
//                         board[i][j].legalMoves[legalMovesCount][1] = j;
//                         legalMovesCount++;
//                     }
//                     if (i == 6 && board[i - 2][j].color == 888 && board[i - 1][j].color == 888) // Two-step move
//                     {
//                         board[i][j].legalMoves[legalMovesCount][0] = i - 2;
//                         board[i][j].legalMoves[legalMovesCount][1] = j;
//                         legalMovesCount++;
//                     }
//                     if (i > 0 && j > 0 && board[i - 1][j - 1].color == 0) // Capture left
//                     {
//                         board[i][j].legalMoves[legalMovesCount][0] = i - 1;
//                         board[i][j].legalMoves[legalMovesCount][1] = j - 1;
//                         legalMovesCount++;
//                     }
//                     if (i > 0 && j < 7 && board[i - 1][j + 1].color == 0) // Capture right
//                     {
//                         board[i][j].legalMoves[legalMovesCount][0] = i - 1;
//                         board[i][j].legalMoves[legalMovesCount][1] = j + 1;
//                         legalMovesCount++;
//                     }
//                 }
//                 else if (board[i][j].color == 0) // Black Pawn
//                 {
//                     if (i < 7 && board[i + 1][j].color == 888) // Move forward
//                     {
//                         board[i][j].legalMoves[legalMovesCount][0] = i + 1;
//                         board[i][j].legalMoves[legalMovesCount][1] = j;
//                         legalMovesCount++;
//                     }
//                     if (i == 1 && board[i + 2][j].color == 888 && board[i + 1][j].color == 888) // Two-step move
//                     {
//                         board[i][j].legalMoves[legalMovesCount][0] = i + 2;
//                         board[i][j].legalMoves[legalMovesCount][1] = j;
//                         legalMovesCount++;
//                     }
//                     if (i < 7 && j < 7 && board[i + 1][j + 1].color == 1) // Capture right
//                     {
//                         board[i][j].legalMoves[legalMovesCount][0] = i + 1;
//                         board[i][j].legalMoves[legalMovesCount][1] = j + 1;
//                         legalMovesCount++;
//                     }
//                     if (i < 7 && j > 0 && board[i + 1][j - 1].color == 1) // Capture left
//                     {
//                         board[i][j].legalMoves[legalMovesCount][0] = i + 1;
//                         board[i][j].legalMoves[legalMovesCount][1] = j - 1;
//                         legalMovesCount++;
//                     }
//                 }
//                 board[i][j].numberOfLegalMoves = legalMovesCount;
//             }
//             else if (board[i][j].type == "R") // Rook
//             {
//                 int legalMovesCount = 0;
//                 // Rook horizontal & vertical moves
//                 for (int k = i + 1; k < 8 && board[k][j].color != board[i][j].color; k++) // Down
//                 {
//                     board[i][j].legalMoves[legalMovesCount][0] = k;
//                     board[i][j].legalMoves[legalMovesCount][1] = j;
//                     legalMovesCount++;
//                     if (board[k][j].color != 888) break;
//                 }
//                 for (int k = i - 1; k >= 0 && board[k][j].color != board[i][j].color; k--) // Up
//                 {
//                     board[i][j].legalMoves[legalMovesCount][0] = k;
//                     board[i][j].legalMoves[legalMovesCount][1] = j;
//                     legalMovesCount++;
//                     if (board[k][j].color != 888) break;
//                 }
//                 for (int k = j + 1; k < 8 && board[i][k].color != board[i][j].color; k++) // Right
//                 {
//                     board[i][j].legalMoves[legalMovesCount][0] = i;
//                     board[i][j].legalMoves[legalMovesCount][1] = k;
//                     legalMovesCount++;
//                     if (board[i][k].color != 888) break;
//                 }
//                 for (int k = j - 1; k >= 0 && board[i][k].color != board[i][j].color; k--) // Left
//                 {
//                     board[i][j].legalMoves[legalMovesCount][0] = i;
//                     board[i][j].legalMoves[legalMovesCount][1] = k;
//                     legalMovesCount++;
//                     if (board[i][k].color != 888) break;
//                 }
//                 board[i][j].numberOfLegalMoves = legalMovesCount;
//             }
//             else if (board[i][j].type == "K") // King
//             {
//                 int legalMovesCount = 0;
//                 int kingMoves[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
//                 for (auto &move : kingMoves)
//                 {
//                     int newX = i + move[0];
//                     int newY = j + move[1];
//                     if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8 && board[newX][newY].color != board[i][j].color)
//                     {
//                         board[i][j].legalMoves[legalMovesCount][0] = newX;
//                         board[i][j].legalMoves[legalMovesCount][1] = newY;
//                         legalMovesCount++;
//                     }
//                 }
//                 board[i][j].numberOfLegalMoves = legalMovesCount;
//             }
//         }
//     }
// }


// int CalculateLegalMoves(Piece board[][8], bool color, int x, int y, int data[])
// {
//     cout << "\n";
//     if (board[x][y].type == "P")
//     {
//         if (board[x][y].color == 1)
//         {
//             int k = 0;
//             int m[4][2];
//             if (board[x - 1][y].color == 888)
//             {
//                 k++;
//                 cout << as.BOLD << k << ". " << YtoFiles(y + 1) << 8 - x + 1 << as.RESET << "    ";
//                 m[0][0] = x - 1;
//                 m[0][1] = y;
//             }
//             if (x == 6 && board[x - 2][y].color == 888 && board[x - 1][y].color == 888)
//             {
//                 k++;
//                 cout << as.BOLD << k << ". " << YtoFiles(y + 1) << 8 - x + 2 << as.RESET << "    ";
//                 m[1][0] = x - 2;
//                 m[1][1] = y;
//             }
//             if (y > 0 && board[x - 1][y - 1].color == 0)
//             {
//                 k++;
//                 cout << as.BOLD << k << ". " << YtoFiles(y) << 8 - x + 1 << as.RESET << "    ";
//                 m[2][0] = x - 1;
//                 m[2][1] = y - 1;
//             }
//             if (y < 7 && board[x - 1][y + 1].color == 0)
//             {
//                 k++;
//                 cout << as.BOLD << k << ". " << YtoFiles(y + 2) << 8 - x + 1 << as.RESET << "    ";
//                 m[3][0] = x - 1;
//                 m[3][1] = y + 1;
//             }
//             cout << "\nMove " << YtoFiles(y + 1) << 8 - x << " to (1 - " << k << "): ";
//             int move;
//             cin >> move;
//             if (cin.fail() || move < 1 || move > k)
//             {
//                 cin.clear();
//                 cin.ignore(INT_MAX, '\n');
//                 cout << as.B_RED << "Invalid input. Please enter a number between 1 and " << k << "." << as.RESET << "\n";
//                 return 0;
//             }
//             data[0] = m[move - 1][0];
//             data[1] = m[move - 1][1];
//             return k;
//         }
//         else if (board[x][y].color == 0)
//         {
//             int k = 0;
//             int m[4][2];
//             if (board[x + 1][y].color == 888)
//             {
//                 k++;
//                 cout << as.BOLD << k << ". " << YtoFiles(y + 1) << 8 - x - 1 << as.RESET << "    ";
//                 m[0][0] = x + 1;
//                 m[0][1] = y;
//             }
//             if (x == 1 && board[x + 2][y].color == 888 && board[x + 1][y].color == 888)
//             {
//                 k++;
//                 cout << as.BOLD << k << ". " << YtoFiles(y + 1) << 8 - x - 2 << as.RESET << "    ";
//                 m[1][0] = x + 2;
//                 m[1][1] = y;
//             }
//             if (y < 7 && board[x + 1][y + 1].color == 1)
//             {
//                 k++;
//                 cout << as.BOLD << k << ". " << YtoFiles(y + 2) << 8 - x - 1 << as.RESET << "    ";
//                 m[2][0] = x + 1;
//                 m[2][1] = y + 1;
//             }
//             if (y > 0 && board[x + 1][y - 1].color == 1)
//             {
//                 k++;
//                 cout << as.BOLD << k << ". " << YtoFiles(y) << 8 - x - 1 << as.RESET << "    ";
//                 m[3][0] = x + 1;
//                 m[3][1] = y - 1;
//             }
//             cout << "\nMove " << YtoFiles(y + 1) << 8 - x << " to (1 - " << k << "): ";
//             int move;
//             cin >> move;
//             if (cin.fail() || move < 1 || move > k)
//             {
//                 cin.clear();
//                 cin.ignore(INT_MAX, '\n');
//                 cout << as.B_RED << "Invalid input. Please enter a number between 1 and " << k << "." << as.RESET << "\n";
//                 return 0;
//             }
//             data[0] = m[move - 1][0];
//             data[1] = m[move - 1][1];
//             return k;
//         }
//     }
//     else if (board[x][y].type == "R")
//     {
//         /* code */
//     }
//     else if (board[x][y].type == "N")
//     {
//         /* code */
//     }
//     else if (board[x][y].type == "B")
//     {
//         /* code */
//     }
//     else if (board[x][y].type == "Q")
//     {
//         /* code */
//     }
//     else if (board[x][y].type == "K")
//     {
//         /* code */
//     }
//     return 0;
// }

void SwapPieces(Piece board[][8], int x1, int y1, int x2, int y2)
{
    Piece empty = {" ", " ", 888};
    board[x2][y2] = board[x1][y1];
    board[x1][y1] = empty;
}

// void Move(Piece board[][8], bool color = 1)
// {
//     int piece;
//     int totalPawnMoves = 0, totalRookMoves = 0, totalKnightMoves = 0, totalBishopMoves = 0, totalQueenMoves = 0, totalKingMoves = 0;
//     for (int i = 0; i < 8; i++)
//     {
//         for (int j = 0; j < 8; j++)
//         {
//             if (board[i][j].color == color)
//             {
//                 if (board[i][j].type == "P")
//                 {
//                     totalPawnMoves += board[i][j].numberOfLegalMoves;
//                 }
//                 else if (board[i][j].type == "R")
//                 {
//                     totalRookMoves += board[i][j].numberOfLegalMoves;
//                 }
//                 else if (board[i][j].type == "N")
//                 {
//                     totalKnightMoves += board[i][j].numberOfLegalMoves;
//                 }
//                 else if (board[i][j].type == "B")
//                 {
//                     totalBishopMoves += board[i][j].numberOfLegalMoves;
//                 }
//                 else if (board[i][j].type == "Q")
//                 {
//                     totalQueenMoves += board[i][j].numberOfLegalMoves;
//                 }
//                 else if (board[i][j].type == "K")
//                 {
//                     totalKingMoves += board[i][j].numberOfLegalMoves;
//                 }
//             }
//         }
//     }
//     bool hasPawnMoves = totalPawnMoves > 0;
//     bool hasRookMoves = totalRookMoves > 0;
//     bool hasKnightMoves = totalKnightMoves > 0;
//     bool hasBishopMoves = totalBishopMoves > 0;
//     bool hasQueenMoves = totalQueenMoves > 0;
//     bool hasKingMoves = totalKingMoves > 0;

//     // Shows list of pieces that can move so player can choose which piece to move
//     int pieceCount = 0;

//     if (hasPawnMoves)
//     {
//         pieceCount++;
//         cout << as.BOLD << pieceCount << ". Pawn    ";
//     }
//     if (hasRookMoves)
//     {
//         pieceCount++;
//         cout << as.BOLD << pieceCount << ". Rook    ";
//     }
//     if (hasKnightMoves)
//     {
//         pieceCount++;
//         cout << as.BOLD << pieceCount << ". Knight    ";
//     }
//     if (hasBishopMoves)
//     {
//         pieceCount++;
//         cout << as.BOLD << pieceCount << ". Bishop    ";
//     }
//     if (hasQueenMoves)
//     {
//         pieceCount++;
//         cout << as.BOLD << pieceCount << ". Queen    ";
//     }
//     if (hasKingMoves)
//     {
//         pieceCount++;
//         cout << as.BOLD << pieceCount << ". King    ";
//     }
//     cout << as.RESET << "\n";
//     // cout << as.BOLD << "1. Pawn    2. Rook    3. Knight    4. Bishop    5. Queen    6. King\n"
//     //      << as.RESET;
//     while (true)
//     {
//         if (pieceCount > 1)
//         {
//             cout << "Piece to move (1 - " << pieceCount << "): ";
//         }
//         else
//         {
//             cout << "Piece to move: ";
//         }
//         cin >> piece;
//         if (cin.fail() || piece < 1 || piece > pieceCount)
//         {
//             cin.clear();
//             cin.ignore(INT_MAX, '\n');
//             cout << as.B_RED << "Invalid input. Please enter a number between 1 and 6." << as.RESET << "\n";
//             continue;
//         }
//         break;
//     }
//     cout << "\n";

//     // FUTURE : Fix switch statement so it correctly points to the pieceCount

//     switch (piece)
//     {
//     case 1:
//         int pawnCount = 0;
//         for (int i = 0; i < 8; i++)
//         {
//             for (int j = 0; j < 8; j++)
//             {
//                 if (board[i][j].color == color && board[i][j].type == "P")
//                 {
//                     pawnCount++;
//                     cout << as.BOLD << pawnCount << ". " << YtoFiles(j + 1) << 8 - i << "    " << as.RESET;
//                 }
//             }
//         }
//         cout << "\n";
//         while (true)
//         {
//             cout << "Pawn to move (1 - " << pawnCount << "): ";
//             cin >> piece;
//             if (cin.fail() || piece < 1 || piece > pawnCount)
//             {
//                 cin.clear();
//                 cin.ignore(INT_MAX, '\n');
//                 cout << as.B_RED << "Invalid input. Please enter a number between 1 and " << pawnCount << "." << as.RESET << "\n";
//                 continue;
//             }
//             break;
//         }
//         // Display Legal Moves
//         int selectedPawn = 0;
//         for (int i = 0; i < 8; i++)
//         {
//             for (int j = 0; j < 8; j++)
//             {
//                 if (board[i][j].color == color && board[i][j].type == "P")
//                 {
//                     selectedPawn++;
//                     if (selectedPawn == piece)
//                     {
//                         int moveCount = 0;
//                         for (int k = 0; k < 25; k++)
//                         {
//                             if (board[i][j].legalMoves[k][0] != 888)
//                             {
//                                 moveCount++;
//                                 cout << as.BOLD << moveCount << ". " << YtoFiles(j + 1) << 8 - i << " to " << YtoFiles(board[i][j].legalMoves[k][1] + 1) << 8 - board[i][j].legalMoves[k][0] << "    " << as.RESET;
//                             }
//                         }
//                         cout << "\n";
//                         int move;
//                         while (true)
//                         {
//                             cout << "Move " << YtoFiles(j + 1) << 8 - i << " to (1 - " << moveCount << "): ";
//                             cin >> move;
//                             if (cin.fail() || move < 1 || move > moveCount)
//                             {
//                                 cin.clear();
//                                 cin.ignore(INT_MAX, '\n');
//                                 cout << as.B_RED << "Invalid input. Please enter a number between 1 and " << moveCount << "." << as.RESET << "\n";
//                                 continue;
//                             }
//                             break;
//                         }
//                         SwapPieces(board, i, j, board[i][j].legalMoves[move - 1][0], board[i][j].legalMoves[move - 1][1]);
//                         DrawBoard(board);
//                         return;
//                     }
//                 }
//             }
//         }

        // Move Piece

        // for (int i = 0; i < 8; i++)
        // {
        //     for (int j = 0; j < 8; j++)
        //     {
        //         if (board[i][j].color == color && board[i][j].type == "P")
        //         {
        //             piece--;
        //             if (piece == 0)
        //             {
        //                 int pawnToMove;
        //                 for (int k = 0; k < 25; k++)
        //                 {
        //                     if (board[i][j].legalMoves[k][0] != 888)
        //                     {
        //                         cout << as.BOLD << k + 1 << ". " << YtoFiles(j + 1) << 8 - i << " to " << YtoFiles(board[i][j].legalMoves[k][1] + 1) << 8 - board[i][j].legalMoves[k][0] << "    " << as.RESET;
        //                         pawnToMove = k;
        //                     }
        //                 }
        //                 cout << "Move " << YtoFiles(j + 1) << 8 - i << " to (1 - " << pawnToMove + 1 << "): ";
        //                 cin >> pawnToMove;
        //                 // SwapPieces(board, i, j, data[0], data[1]);
        //                 DrawBoard(board);
        //                 return;
        //             }
        //         }
        //     }
//         // }
//         break;
//     }
// }