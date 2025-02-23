#include <iostream>

using namespace std;

// ANSI escape code format: \033[38;2;<r>;<g>;<b>m (text color) and \033[48;2;<r>;<g>;<b>m (background color)
void printColoredText(int r, int g, int b, const string& label) {
    cout << "\033[48;2;" << r << ";" << g << ";" << b << "m"; // Background color

    // White text
    cout << "\033[38;2;255;255;255m White Text on " << label << " ";
    
    // Black text
    cout << "\033[38;2;0;0;0m Black Text on " << label << " ";
    
    cout << "\033[0m" << endl; // Reset colors
}

int main() {
    cout << "Comparing black & white text on different backgrounds:\n\n";

    // ♟️ Classic Chessboard Colors
    // printColoredText(240, 217, 181, "Beige (Chess Light)");
    printColoredText(125, 135, 150, "Slate Gray (Chess Dark)");

    // 🔳 Neutral Grays (Common for UI)
    printColoredText(230, 230, 230, "Very Light Gray");
    printColoredText(200, 200, 200, "Light Gray");
    printColoredText(150, 150, 150, "Medium Gray");
    printColoredText(100, 100, 100, "Dark Gray");
    printColoredText(50, 50, 50, "Very Dark Gray");

    // 🔵 Blue Variants
    printColoredText(200, 225, 255, "Soft Blue");
    printColoredText(25, 80, 140, "Deep Blue");
    printColoredText(135, 206, 250, "Sky Blue");
    printColoredText(0, 191, 255, "Deep Sky Blue");
    printColoredText(0, 0, 139, "Midnight Blue");
    printColoredText(70, 130, 180, "Steel Blue");
    printColoredText(176, 224, 230, "Powder Blue");

    // 🟢 Green Variants
    printColoredText(202, 225, 194, "Pastel Green");
    printColoredText(86, 125, 70, "Dark Green");
    printColoredText(144, 238, 144, "Light Green");
    printColoredText(34, 139, 34, "Forest Green");
    printColoredText(0, 128, 0, "Classic Green");
    printColoredText(152, 251, 152, "Pale Green");

    // 🟤 Brown/Wooden Tones
    printColoredText(230, 190, 140, "Light Tan");
    printColoredText(150, 75, 0, "Dark Brown");
    printColoredText(210, 180, 140, "Tan");
    printColoredText(139, 69, 19, "Saddle Brown");
    printColoredText(160, 82, 45, "Sienna");

    // 🟣 Purple Variants
    printColoredText(220, 200, 255, "Lavender");
    printColoredText(80, 40, 120, "Deep Purple");
    printColoredText(147, 112, 219, "Medium Purple");
    printColoredText(138, 43, 226, "Blue Violet");
    printColoredText(75, 0, 130, "Indigo");

    // 🟡 Yellow & Gold Variants
    printColoredText(255, 255, 204, "Light Yellow");
    printColoredText(255, 215, 0, "Gold");
    printColoredText(255, 165, 0, "Orange");
    printColoredText(218, 165, 32, "Goldenrod");

    // 🔴 Red Variants
    printColoredText(255, 182, 193, "Light Pink");
    printColoredText(220, 20, 60, "Crimson");
    printColoredText(255, 69, 0, "Red-Orange");
    printColoredText(139, 0, 0, "Dark Red");
    printColoredText(178, 34, 34, "Firebrick");

    // 🎨 Special Colors
    printColoredText(192, 192, 192, "Silver");
    printColoredText(255, 250, 250, "Snow White");
    printColoredText(240, 128, 128, "Salmon");
    printColoredText(32, 32, 32, "Almost Black");

    // Reset colors at the end
    cout << "\n\033[0mEnd of comparison.\n";

    return 0;
}
