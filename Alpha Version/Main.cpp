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

void DrawBoard(string board[][8], int x, int y)
{
    board[8 - x][y - 1] = "X";

    int n = 8, f1 = 8, f2 = 8;
    string offX = "      ", offY = "\n\n"; // 3:1
    cout << offY << offX << as.REVERSED << as.BOLD + " " << "     A   B   C   D   E   F   G   H      \n"
         << as.RESET;
    cout << offX << as.REVERSED + as.BOLD + "   " + as.RESET << " --------------------------------- " << as.REVERSED + as.BOLD << "   " << as.RESET << "\n";

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (j == 1)
            {
                cout << offX << as.REVERSED << as.BOLD + " " << f1 << " " << as.RESET << " | " << board[i - 1][j - 1] << " ";
                f1--;
            }
            else if (j == n)
            {
                cout << "| " << board[i - 1][j - 1] << " | " << as.REVERSED << as.BOLD + " " << f2 << " " << as.RESET;
                f2--;
            }
            else
            {
                if (i % 2 == 0 && j % 2 == 0 || i % 2 != 0 && j % 2 != 0)
                {
                    cout << "|" << as.BG_BLUE + as.BOLD << " " << board[i - 1][j - 1] << " " << as.RESET;
                }
                else
                {
                    cout << "|" << as.BG_B_BLUE + as.BOLD << " " << board[i - 1][j - 1] << " " << as.RESET;
                }
            }
        }
        cout << "\n";
        cout << offX << as.REVERSED + as.BOLD + "   " + as.RESET << " --------------------------------- " << as.REVERSED + as.BOLD << "   " << as.RESET << "\n";
    }
    cout << offX << as.REVERSED << as.BOLD + " " << "     A   B   C   D   E   F   G   H      \n"
         << as.RESET << offY;
}

int main()
{
    system("");
    AnsiiCodeEscapes ansi;

    std::cout << ansi.BOLD << "Text Styles Demo" << ansi.RESET << "\n";
    std::cout << ansi.BOLD << "Bold Text" << ansi.RESET << "\n";
    std::cout << ansi.DIM << "Dim Text" << ansi.RESET << "\n";
    std::cout << ansi.ITALIC << "Italic Text" << ansi.RESET << "\n";
    std::cout << ansi.UNDERLINE << "Underlined Text" << ansi.RESET << "\n";
    std::cout << ansi.BLINK << "Blinking Text" << ansi.RESET << "\n";
    std::cout << ansi.REVERSED << "Reversed Text" << ansi.RESET << "\n";
    std::cout << ansi.STRIKETHROUGH << "Strikethrough Text" << ansi.RESET << "\n";

    std::cout << "\nColor Demo:\n";
    std::cout << ansi.RED << "Red Text" << ansi.RESET << "\n";
    std::cout << ansi.GREEN << "Green Text" << ansi.RESET << "\n";
    std::cout << ansi.BLUE << "Blue Text" << ansi.RESET << "\n";
    std::cout << ansi.MAGENTA << "Magenta Text" << ansi.RESET << "\n";

    std::cout << "\nBright Color Demo:\n";
    std::cout << ansi.B_RED << "Bright Red Text" << ansi.RESET << "\n";
    std::cout << ansi.B_GREEN << "Bright Green Text" << ansi.RESET << "\n";
    std::cout << ansi.B_BLUE << "Bright Blue Text" << ansi.RESET << "\n";

    std::cout << "\nBackground Color Demo:\n";
    std::cout << ansi.BG_RED + as.BLACK + as.BOLD << "Red Background" << ansi.RESET << "\n";
    std::cout << ansi.BG_GREEN << "Green Background" << ansi.RESET << "\n";
    std::cout << ansi.BG_B_GREEN << "Blue Background" << ansi.RESET << "\n";
    std::cout << ansi.BG_B_WHITE << "Green Background" << ansi.RESET << "\n";
    std::cout << ansi.BG_B_BLACK << "Blue Background" << ansi.RESET << "\n";
    std::cout << ansi.BG_B_WHITE + as.B_BLACK << "Green Background" << ansi.RESET << "\n";
    std::cout << ansi.BG_B_BLACK + as.B_WHITE << "Blue Background" << ansi.RESET << "\n";
    std::cout << ansi.BG_B_WHITE + as.WHITE + as.BOLD + as.DIM<< "Green Background" << ansi.RESET << "\n";
    std::cout << ansi.BG_B_BLACK + as.BLACK + as.BOLD + as.DIM<< "Blue Background" << ansi.RESET << "\n";
    std::cout << ansi.B_WHITE + as.B_BLACK << "Green affafasfaBackground" << ansi.RESET << "\n";
    std::cout << ansi.B_BLACK + as.B_WHITE << "Blue Background" << ansi.RESET << "\n";
    std::cout << ansi.BG_B_RED + as.BLACK << "Blue Background" << ansi.RESET << "\n";
    std::cout << ansi.BG_B_YELLOW + as.BLACK << "Blue Background" << ansi.RESET << "\n";
    std::cout << ansi.BG_YELLOW + as.BLACK << "Blue Background" << ansi.RESET << "\n";
    std::cout << ansi.BG_B_YELLOW + as.BOLD + as.B_WHITE << "Blue Background" << ansi.RESET << "\n";
    std::cout << ansi.BG_YELLOW + as.BOLD + as.B_WHITE << "Blue Background" << ansi.RESET << "\n";
    std::cout << ansi.BG_B_BLUE + as.BOLD + as.B_WHITE << "Blue Background" << ansi.RESET << "\n";
    std::cout << ansi.BG_BLUE + as.BOLD + as.B_WHITE << "Blue Background" << ansi.RESET << "\n";
    std::cout << ansi.BG_B_BLUE + as.BOLD + as.BLACK << "Blue Background" << ansi.RESET << "\n";
    std::cout << ansi.BG_BLUE + as.BOLD + as.BLACK << "Blue Background" << ansi.RESET << "\n";
    

    // string board[8][8];
    // ResetBoard(board);
    string board[8][8] = {
        {"R", "N", "B", "Q", "K", "B", "N", "R"},
        {"P", "P", "P", "P", "P", "P", "P", "P"},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {"p", "p", "p", "p", "p", "p", "p", "p"},
        {"r", "n", "b", "q", "k", "b", "n", "r"}
    };
    
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