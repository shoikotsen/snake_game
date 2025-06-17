/*
Author: Shoikot Sen
Program: Classic Snake Game in Console
Description:
    - A simple console-based Snake game in C++
    - Use W/A/S/D to control the snake
    - Eat the fruit to grow the tail and increase the score
    - Difficulty can be selected at the beginning
    - High score is saved and loaded from a file (score.txt)
*/

#include <iostream>
#include <conio.h>     // For _kbhit() and _getch()
#include <windows.h>   // For Sleep()
#include <fstream>     // For reading and writing high score

using namespace std;

// Game state variables
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score, highScore;
int tailX[100], tailY[100];  // Arrays to track tail positions
int nTail;                   // Current tail length
int delay = 100;             // Game speed (lower = faster)

// Direction enum
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

// Setup initial game state
void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 0;
}

// Draw the game board and display score
void Draw() {
    system("cls");  // Clear the screen

    // Top wall
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    // Grid with snake and fruit
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "#";  // Left wall

            if (i == y && j == x)
                cout << "O";  // Snake head
            else if (i == fruitY && j == fruitX)
                cout << "F";  // Fruit
            else {
                bool printTail = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";  // Snake tail
                        printTail = true;
                        break;
                    }
                }
                if (!printTail) cout << " ";
            }

            if (j == width - 1) cout << "#";  // Right wall
        }
        cout << endl;
    }

    // Bottom wall
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    // Score display
    cout << "Score: " << score << " | High Score: " << highScore << endl;
    cout << "Controls: W = Up, A = Left, S = Down, D = Right, X = Quit" << endl;
}

// Handle player key input
void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': dir = LEFT; break;
            case 'd': dir = RIGHT; break;
            case 'w': dir = UP; break;
            case 's': dir = DOWN; break;
            case 'x': gameOver = true; break;  // Quit game
        }
    }
}

// Game logic (movement, collision, scoring)
void Logic() {
    // Move the tail (each segment follows the one before it)
    int prevX = tailX[0], prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Move the snake head
    switch (dir) {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
    }

    // Wrap around walls
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    // Check collision with tail
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }

    // Check if fruit is eaten
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;  // Grow tail
    }
}

int main() {
    // Load saved high score from file
    ifstream infile("score.txt");
    if (infile.is_open()) {
        infile >> highScore;
        infile.close();
    } else {
        highScore = 0;
    }

    // Difficulty selection
    int level;
    cout << "Choose Difficulty Level:\n1. Easy\n2. Medium\n3. Hard\nEnter 1/2/3: ";
    cin >> level;
    switch (level) {
        case 1: delay = 150; break;
        case 2: delay = 100; break;
        case 3: delay = 50; break;
        default: delay = 100; break;
    }

    Setup();  // Initialize the game

    // Game loop
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(delay);  // Pause between frames
    }

    // Game Over screen
    system("cls");
    cout << "\n===== GAME OVER =====" << endl;
    cout << "Final Score: " << score << endl;

    // Save new high score if beaten
    if (score > highScore) {
        cout << "🎉 New High Score!" << endl;
        ofstream out("score.txt");
        out << score;
        out.close();
    } else {
        cout << "High Score: " << highScore << endl;
    }

    system("pause");  // Wait for user input before exit
    return 0;
}
