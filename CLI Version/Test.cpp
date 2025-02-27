
#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <cctype>
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

//
// Helper: Convert a (1-indexed) file number to a letter.
// For example, passing 1 returns 'a', 2 returns 'b', etc.
//
inline char YtoFiles(int y)
{
    return y + 96; // 1 -> 'a'
}

//
// Clears the board by marking every square as empty.
//
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

//
// FENtoBoard: Parses a FEN string and populates the board.
// Only the piece placement part is considered here.
//
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

//
// DrawBoard: Renders the board on screen using ANSI escape codes.
// It also prints ranks and files along the edges.
//
void DrawBoard(Piece board[][8])
{
    // Define text colors for white and black pieces.
    string white = as.BOLD + "\033[38;2;255;255;255m";
    string black = as.BOLD + "\033[38;2;0;0;0m";

    // Update piece strings with color escapes.
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j].representation == "p" || board[i][j].representation == "r" || board[i][j].representation == "n" ||
                board[i][j].representation == "b" || board[i][j].representation == "q" || board[i][j].representation == "k")
            {
                // Convert to uppercase for display and mark as black.
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
            else if (board[i][j].representation == "P" || board[i][j].representation == "R" || board[i][j].representation == "N" ||
                     board[i][j].representation == "B" || board[i][j].representation == "Q" || board[i][j].representation == "K")
            {
                board[i][j].representation = white + board[i][j].representation;
                board[i][j].color = 1;
            }
        }
    }

    // Define background colors and border style.
    string backDark = "\033[48;2;240;128;128m";
    string backLight = "\033[48;2;255;182;193m";
    string borderBG = "\033[48;2;32;32;32m";
    string borderText = as.DIM + "\033[38;2;255;255;255m";
    string sep = "";
    int n = 8, f1 = 8, f2 = 8;
    string offX = "      ", offY = "\n\n"; 
    cout << offY << offX << borderBG + borderText << as.BOLD << "   a  b  c  d  e  f  g  h    " << as.RESET << "\n";

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (j == 1)
            {
                if (i % 2 != 0)
                {
                    cout << offX << borderBG + borderText << as.BOLD << " " << f1 << " " << as.RESET
                         << backDark << as.BOLD << " " << board[i - 1][j - 1].representation << " " << as.RESET;
                    f1--;
                }
                else
                {
                    cout << offX << borderBG + borderText << as.BOLD << " " << f1 << " " << as.RESET
                         << backLight << as.BOLD << " " << board[i - 1][j - 1].representation << " " << as.RESET;
                    f1--;
                }
            }
            else if (j == n)
            {
                if (i % 2 == 0)
                {
                    cout << backDark << as.BOLD << " " << board[i - 1][j - 1].representation << " " << as.RESET
                         << borderBG + borderText << as.BOLD << " " << f2 << " " << as.RESET;
                    f2--;
                }
                else
                {
                    cout << backLight << as.BOLD << " " << board[i - 1][j - 1].representation << " " << as.RESET
                         << borderBG + borderText << as.BOLD << " " << f2 << " " << as.RESET;
                    f2--;
                }
            }
            else
            {
                if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0))
                {
                    cout << backDark << as.BOLD << " " << board[i - 1][j - 1].representation << " " << as.RESET;
                }
                else
                {
                    cout << backLight << as.BOLD << " " << board[i - 1][j - 1].representation << " " << as.RESET;
                }
            }
        }
        cout << "\n";
    }
    cout << offX << borderBG + borderText << as.BOLD << "   a  b  c  d  e  f  g  h    " << as.RESET << offY << "\n";
}

//
// CalculateLegalMoves: Returns a vector of legal destination squares for a piece at (x, y).
// This implementation handles pawn (P), knight (N), rook (R), bishop (B),
// queen (Q), and king (K). (For rook, bishop, queen, and king the move generation
// is basic and does not cover special rules.)
//
vector<pair<int,int>> CalculateLegalMoves(Piece board[][8], bool color, int x, int y)
{
    vector<pair<int,int>> moves;
    string pieceType = board[x][y].type;
    
    if(pieceType == "P")
    {
        if(color == 1)  // White pawn moves upward (decreasing row index)
        {
            if(x - 1 >= 0 && board[x-1][y].color == 888)
                moves.push_back({x-1, y});
            if(x == 6 && x - 2 >= 0 && board[x-1][y].color == 888 && board[x-2][y].color == 888)
                moves.push_back({x-2, y});
            if(x - 1 >= 0 && y - 1 >= 0 && board[x-1][y-1].color != 888 && board[x-1][y-1].color != color)
                moves.push_back({x-1, y-1});
            if(x - 1 >= 0 && y + 1 < 8 && board[x-1][y+1].color != 888 && board[x-1][y+1].color != color)
                moves.push_back({x-1, y+1});
        }
        else  // Black pawn moves downward (increasing row index)
        {
            if(x + 1 < 8 && board[x+1][y].color == 888)
                moves.push_back({x+1, y});
            if(x == 1 && x + 2 < 8 && board[x+1][y].color == 888 && board[x+2][y].color == 888)
                moves.push_back({x+2, y});
            if(x + 1 < 8 && y - 1 >= 0 && board[x+1][y-1].color != 888 && board[x+1][y-1].color != color)
                moves.push_back({x+1, y-1});
            if(x + 1 < 8 && y + 1 < 8 && board[x+1][y+1].color != 888 && board[x+1][y+1].color != color)
                moves.push_back({x+1, y+1});
        }
    }
    else if(pieceType == "N")
    {
        vector<pair<int,int>> offsets = {{2,1},{2,-1},{-2,1},{-2,-1},{1,2},{1,-2},{-1,2},{-1,-2}};
        for(auto off : offsets)
        {
            int nx = x + off.first, ny = y + off.second;
            if(nx >= 0 && nx < 8 && ny >= 0 && ny < 8)
            {
                if(board[nx][ny].color == 888 || board[nx][ny].color != color)
                    moves.push_back({nx, ny});
            }
        }
    }
    else if(pieceType == "R")
    {
        int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
        for(auto &d : dirs)
        {
            int nx = x, ny = y;
            while(true)
            {
                nx += d[0];
                ny += d[1];
                if(nx < 0 || nx >= 8 || ny < 0 || ny >= 8) break;
                if(board[nx][ny].color == 888)
                    moves.push_back({nx, ny});
                else
                {
                    if(board[nx][ny].color != color)
                        moves.push_back({nx, ny});
                    break;
                }
            }
        }
    }
    else if(pieceType == "B")
    {
        int dirs[4][2] = {{1,1},{1,-1},{-1,1},{-1,-1}};
        for(auto &d : dirs)
        {
            int nx = x, ny = y;
            while(true)
            {
                nx += d[0];
                ny += d[1];
                if(nx < 0 || nx >= 8 || ny < 0 || ny >= 8) break;
                if(board[nx][ny].color == 888)
                    moves.push_back({nx, ny});
                else
                {
                    if(board[nx][ny].color != color)
                        moves.push_back({nx, ny});
                    break;
                }
            }
        }
    }
    else if(pieceType == "Q")
    {
        // Combine rook and bishop moves
        int dirs1[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
        for(auto &d : dirs1)
        {
            int nx = x, ny = y;
            while(true)
            {
                nx += d[0];
                ny += d[1];
                if(nx < 0 || nx >= 8 || ny < 0 || ny >= 8) break;
                if(board[nx][ny].color == 888)
                    moves.push_back({nx, ny});
                else
                {
                    if(board[nx][ny].color != color)
                        moves.push_back({nx, ny});
                    break;
                }
            }
        }
        int dirs2[4][2] = {{1,1},{1,-1},{-1,1},{-1,-1}};
        for(auto &d : dirs2)
        {
            int nx = x, ny = y;
            while(true)
            {
                nx += d[0];
                ny += d[1];
                if(nx < 0 || nx >= 8 || ny < 0 || ny >= 8) break;
                if(board[nx][ny].color == 888)
                    moves.push_back({nx, ny});
                else
                {
                    if(board[nx][ny].color != color)
                        moves.push_back({nx, ny});
                    break;
                }
            }
        }
    }
    else if(pieceType == "K")
    {
        for(int dx = -1; dx <= 1; dx++){
            for(int dy = -1; dy <= 1; dy++){
                if(dx == 0 && dy == 0) continue;
                int nx = x + dx, ny = y + dy;
                if(nx >= 0 && nx < 8 && ny >= 0 && ny < 8){
                    if(board[nx][ny].color == 888 || board[nx][ny].color != color)
                        moves.push_back({nx, ny});
                }
            }
        }
    }
    
    return moves;
}

//
// Move: Allows the player to select a piece (by type) and then choose one of its legal moves.
// Currently, only Pawn (case 1) and Knight (case 3) moves are implemented;
// the other cases display a “not implemented” message.
//
void Move(Piece board[][8], bool color = 1)
{
    int piece;
    cout << as.BOLD << "1. Pawn    2. Rook    3. Knight    4. Bishop    5. Queen    6. King\n" << as.RESET;
    
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
    case 1:  // Pawn
    {
        vector<pair<int,int>> pawnPositions;
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                if(board[i][j].color == color && board[i][j].type == "P")
                    pawnPositions.push_back({i,j});
            }
        }
        if(pawnPositions.empty()){
            cout << as.RED << "No pawns available to move." << as.RESET << "\n";
            break;
        }
        for (int k = 0; k < pawnPositions.size(); k++){
            int x = pawnPositions[k].first, y = pawnPositions[k].second;
            cout << as.BOLD << k+1 << ". " << YtoFiles(y+1) << (8 - x) << "    " << as.RESET;
        }
        cout << "\n";
        int selection;
        while(true){
            cout << "Pawn to move (1 - " << pawnPositions.size() << "): ";
            cin >> selection;
            if(cin.fail() || selection < 1 || selection > pawnPositions.size()){
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << as.B_RED << "Invalid input. Please enter a number between 1 and " << pawnPositions.size() << "." << as.RESET << "\n";
                continue;
            }
            break;
        }
        int fromX = pawnPositions[selection - 1].first;
        int fromY = pawnPositions[selection - 1].second;
        auto moves = CalculateLegalMoves(board, color, fromX, fromY);
        if(moves.empty()){
            cout << as.RED << "No legal moves for the selected pawn." << as.RESET << "\n";
            break;
        }
        cout << "Legal moves:\n";
        for (int k = 0; k < moves.size(); k++){
            int nx = moves[k].first, ny = moves[k].second;
            cout << as.BOLD << k+1 << ". " << YtoFiles(ny+1) << (8 - nx) << as.RESET << "    ";
        }
        cout << "\n";
        int moveSelection;
        while(true){
            cout << "Select move (1 - " << moves.size() << "): ";
            cin >> moveSelection;
            if(cin.fail() || moveSelection < 1 || moveSelection > moves.size()){
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << as.B_RED << "Invalid input. Please enter a number between 1 and " << moves.size() << "." << as.RESET << "\n";
                continue;
            }
            break;
        }
        int toX = moves[moveSelection - 1].first;
        int toY = moves[moveSelection - 1].second;
        // Apply move
        board[toX][toY] = board[fromX][fromY];
        board[fromX][fromY].representation = " ";
        board[fromX][fromY].color = 888;
        cout << as.GREEN << "Move applied: " << YtoFiles(fromY+1) << (8 - fromX) << " to " 
             << YtoFiles(toY+1) << (8 - toX) << as.RESET << "\n";
        DrawBoard(board);
        break;
    }
    case 3:  // Knight
    {
        vector<pair<int,int>> knightPositions;
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                if(board[i][j].color == color && board[i][j].type == "N")
                    knightPositions.push_back({i,j});
            }
        }
        if(knightPositions.empty()){
            cout << as.RED << "No knights available to move." << as.RESET << "\n";
            break;
        }
        for (int k = 0; k < knightPositions.size(); k++){
            int x = knightPositions[k].first, y = knightPositions[k].second;
            cout << as.BOLD << k+1 << ". " << YtoFiles(y+1) << (8 - x) << as.RESET << "    ";
        }
        cout << "\n";
        int selection;
        while(true){
            cout << "Knight to move (1 - " << knightPositions.size() << "): ";
            cin >> selection;
            if(cin.fail() || selection < 1 || selection > knightPositions.size()){
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << as.B_RED << "Invalid input. Please enter a number between 1 and " << knightPositions.size() << "." << as.RESET << "\n";
                continue;
            }
            break;
        }
        int fromX = knightPositions[selection - 1].first;
        int fromY = knightPositions[selection - 1].second;
        auto moves = CalculateLegalMoves(board, color, fromX, fromY);
        if(moves.empty()){
            cout << as.RED << "No legal moves for the selected knight." << as.RESET << "\n";
            break;
        }
        cout << "Legal moves:\n";
        for (int k = 0; k < moves.size(); k++){
            int nx = moves[k].first, ny = moves[k].second;
            cout << as.BOLD << k+1 << ". " << YtoFiles(ny+1) << (8 - nx) << as.RESET << "    ";
        }
        cout << "\n";
        int moveSelection;
        while(true){
            cout << "Select move (1 - " << moves.size() << "): ";
            cin >> moveSelection;
            if(cin.fail() || moveSelection < 1 || moveSelection > moves.size()){
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << as.B_RED << "Invalid input. Please enter a number between 1 and " << moves.size() << "." << as.RESET << "\n";
                continue;
            }
            break;
        }
        int toX = moves[moveSelection - 1].first;
        int toY = moves[moveSelection - 1].second;
        board[toX][toY] = board[fromX][fromY];
        board[fromX][fromY].representation = " ";
        board[fromX][fromY].color = 888;
        cout << as.GREEN << "Move applied: " << YtoFiles(fromY+1) << (8 - fromX) << " to " 
             << YtoFiles(toY+1) << (8 - toX) << as.RESET << "\n";
        DrawBoard(board);
        break;
    }
    default:
        cout << as.YELLOW << "Move generation for this piece is not yet implemented." << as.RESET << "\n";
        break;
    }
}

int main()
{
    // Enable ANSI escape sequences on some systems.
    system("");
    
    Piece board[8][8];
    ResetBoard(board);
    
    // Standard starting position in FEN notation.
    string startFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    FENtoBoard(board, startFEN);
    
    DrawBoard(board);
    
    // Play one move for white.
    Move(board, 1);
    
    return 0;
}
