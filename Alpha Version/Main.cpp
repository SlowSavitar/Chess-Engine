// Matrix Engine

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
    // Previous position
    // Legal moves
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
    // board[8 - x][y - 1].representation = as.BOLD + "X";

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

int CalculateLegalMoves(Piece board[][8], bool color, int x, int y, int data[])
{
    cout << "\n";
    if (board[x][y].type == "P")
    {
        int k = 0;
        if (board[x - 1][y].color == 888)
        {
            k++;
            cout << as.BOLD << k << ". " << YtoFiles(y + 1) << 8 - x + 1 << as.RESET << "    ";
        }
        if (board[x - 2][y].color == 888)
        {
            k++;
            cout << as.BOLD << k << ". " << YtoFiles(y + 1) << 8 - x + 2 << as.RESET << "    ";
        }
        if (board[x - 1][y - 1].color == !color)
        {
            k++;
            cout << as.BOLD << k << ". " << YtoFiles(y + 1 - 1) << 8 - x + 1 << as.RESET << "    ";
        }
        cout << "\nMove " << YtoFiles(y + 1) << 8 - x << " to (1 - " << k << "): ";
        return k;
    }
    else if (board[x][y].type == "R")
    {
        /* code */
    }
    else if (board[x][y].type == "N")
    {
        /* code */
    }
    else if (board[x][y].type == "B")
    {
        /* code */
    }
    else if (board[x][y].type == "Q")
    {
        /* code */
    }
    else if (board[x][y].type == "K")
    {
        /* code */
    }
}

void Move(Piece board[][8], bool color = 1)
{
    int piece;
    cout << as.BOLD << "1. Pawn    2. Rook    3. Knight    4. Bishop    5. Queen    6. King\n"
         << as.RESET;
    while (true)
    {
        cout << "Piece to move (1 - 6): ";
        cin >> piece;
        if (cin.fail() || piece < 1 || piece > 6)
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << as.B_RED << "Invalid input. Please enter a number between 1 and 6." << as.RESET << "\n";
            continue;
        }
        break;
    }
    cout << "\n";
    switch (piece)
    {
    case 1:
        int pawn;
        int pawnCount = 0;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (board[i][j].color == color)
                {
                    if (board[i][j].type == "P")
                    {
                        pawnCount++;
                        cout << as.BOLD << pawnCount << ". " << YtoFiles(j + 1) << 8 - i << "    " << as.RESET;
                    }
                }
            }
        }
        cout << "\n";
        while (true)
        {
            cout << "Pawn to move (1 - " << pawnCount << "): ";
            cin >> piece;
            if (cin.fail() || piece < 1 || piece > pawnCount)
            {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << as.B_RED << "Invalid input. Please enter a number between 1 and " << pawnCount << "." << as.RESET << "\n";
                continue;
            }
            break;
        }
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (board[i][j].color == color)
                {
                    if (board[i][j].type == "P")
                    {
                        piece--;
                        if (piece == 0)
                        {
                            int data[2] = {};
                            int legalMoves = CalculateLegalMoves(board, color, i, j, data);
                            string move;
                            cin >> move;
                            cout << "\n";
                            break;
                        }
                    }
                }
            }
        }
        break;
    }
}

int main()
{
    system("");

    Piece board[8][8];
    ResetBoard(board);

    string startFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    FENtoBoard(board, startFEN);

    DrawBoard(board);
    Move(board, 1);
    return 0;
}