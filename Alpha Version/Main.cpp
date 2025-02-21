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

void ResetBoard(string board[][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board[i][j] = " ";
        }
    }
}

void FENtoBoard(string board[][8], string fen)
{
    string pieceSymbols[128] = {};
    string white = as.BOLD + "\033[38;2;255;255;255m";
    string black = as.BOLD + "\033[38;2;0;0;0m";
    pieceSymbols['P'] = white + "P";
    pieceSymbols['N'] = white + "N";
    pieceSymbols['B'] = white + "B";
    pieceSymbols['R'] = white + "R";
    pieceSymbols['Q'] = white + "Q";
    pieceSymbols['K'] = white + "K"; // White pieces
    pieceSymbols['p'] = black + "P";
    pieceSymbols['n'] = black + "N";
    pieceSymbols['b'] = black + "B";
    pieceSymbols['r'] = black + "R";
    pieceSymbols['q'] = black + "Q";
    pieceSymbols['k'] = black + "K"; // Black pieces

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
            board[row][col] = pieceSymbols[ch];
            col++;
        }
        else
        {
            break;
        }
    }
}

void DrawBoard(string board[][8], int x, int y)
{
    board[8 - x][y - 1] = as.BOLD + "X";

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
                    cout << offX << borderBG + borderText << as.BOLD + " " << f1 << " " << as.RESET << as.DIM + sep + as.RESET << backDark << " " << board[i - 1][j - 1] << " " << as.RESET;
                    f1--;
                }
                else
                {
                    cout << offX << borderBG + borderText << as.BOLD + " " << f1 << " " << as.RESET << as.DIM + sep + as.RESET << backLight << " " << board[i - 1][j - 1] << " " << as.RESET;
                    f1--;
                }
            }
            else if (j == n)
            {
                if (i % 2 == 0)
                {
                    cout << "" + as.DIM + sep + as.RESET << backDark << " " << board[i - 1][j - 1] << " " + as.RESET << as.DIM << sep + as.RESET << as.RESET + borderBG + borderText << as.BOLD + " " << f2 << " " << as.RESET;
                    f2--;
                }
                else
                {
                    cout << "" + as.DIM + sep + as.RESET << backLight << " " << board[i - 1][j - 1] << " " + as.RESET << as.DIM << sep + as.RESET << as.RESET + borderBG + borderText << as.BOLD + " " << f2 << " " << as.RESET;
                    f2--;
                }
            }
            else
            {
                if (i % 2 == 0 && j % 2 == 0 || i % 2 != 0 && j % 2 != 0)
                {
                    cout << "" + as.DIM + sep + as.RESET << backDark + as.BOLD << " " << board[i - 1][j - 1] << " " << as.RESET;
                }
                else
                {
                    cout << "" + as.DIM + sep + as.RESET << backLight + as.BOLD << " " << board[i - 1][j - 1] << " " << as.RESET;
                }
            }
        }
        cout << "\n";
        // cout << offX << borderBG + borderText + as.BOLD + "   " + as.RESET << as.DIM << " --------------------------------- " << as.RESET << borderBG + borderText + as.BOLD << "   " << as.RESET << "\n";
    }
    cout << offX << borderBG + borderText << as.BOLD + " " << "   a  b  c  d  e  f  g  h    "<< as.RESET << offY << "\n";
}

int main()
{
    system("");
    
    string board[8][8];
    ResetBoard(board);
    string startFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    FENtoBoard(board, startFEN);
    DrawBoard(board, 1, 1);
    while (true)
    {
        int x, y;
        cin >> x >> y;
        system("cls");
        DrawBoard(board, x, y);
    }

    return 0;
}