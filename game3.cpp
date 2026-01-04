#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <fstream> 
#include <string>

using namespace std;

struct Entity {
    int x, y;
    char symbol;
    int color;
};

// --- Function Prototypes ---
void gotoxy(int x, int y);
void setColor(int color);
void drawBorder(int w, int h);
void draw(Entity e);
void erase(Entity e);
void saveHighScore(string name, int score);
int loadHighScore(string name);
void drawBigTitle();

int main() {
    srand(time(0)); 
    const int WIDTH = 60;
    const int HEIGHT = 25; // Adjusted height for better visibility
    string playerName;

    system("cls");
    drawBigTitle();

    // Login UI
    setColor(14); 
    gotoxy(25, 14); cout << "-----------------------------------";
    gotoxy(25, 15); cout << "|       NEWTON'S X LOGIN          |";
    gotoxy(25, 16); cout << "-----------------------------------";

    setColor(15);
    gotoxy(25, 18); cout << "Enter Your Name: ";
    cin >> playerName;

    // --- LOAD DATA ---
    int previousHigh = loadHighScore(playerName);
    
    setColor(13); // Purple/Pink Welcome
    gotoxy(25, 20); cout << "Hello, " << playerName << "!";
    gotoxy(25, 21); cout << "Your Previous High Score: " << previousHigh << " points";
    
    setColor(7); 
    gotoxy(25, 23); cout << "Press any key to enter the Orchard...";
    _getch();

    // --- INITIALIZE GAME ---
    Entity newton = { WIDTH / 2, HEIGHT - 1, 'N', 11 }; 
    Entity apple = { rand() % (WIDTH - 2) + 1, 1, 'A', 12 };
    Entity thunder = { rand() % (WIDTH - 2) + 1, 1, 'T', 14 };
    Entity bomb = { rand() % (WIDTH - 2) + 1, 1, 'B', 8 };

    int score = 0, lives = 3, energy = 50;
    bool isRunning = true;

    system("cls");
    drawBorder(WIDTH, HEIGHT);

    while (isRunning && lives > 0 && energy > 0) {
        // FIXED HUD POSITION: This prevents the "scrolling" error
        gotoxy(0, HEIGHT + 1);
        setColor(15);
        cout << "Player: " << playerName << " | Score: " << score 
             << " | Lives: " << lives << " | Energy: " << energy << "     ";

        // Draw entities at current positions
        draw(newton); draw(apple); draw(thunder); draw(bomb);

        // RESPONSIVE MOVEMENT (Polled multiple times for smoothness)
        for (int i = 0; i < 10; i++) {
            if (_kbhit()) {
                char key = _getch();
                erase(newton);
                if (key == 75 && newton.x > 1) newton.x--;         // Left
                if (key == 77 && newton.x < WIDTH - 2) newton.x++; // Right
                draw(newton);
            }
            Sleep(10); // Smooth movement delay
        }

        // FALLING LOGIC: Erase before moving down
        erase(apple); erase(thunder); erase(bomb);
        apple.y++; thunder.y++; bomb.y++;

        // --- COLLISION LOGIC ---
        // Catching an apple: +10 score, +5 energy [cite: 22, 32]
        if (apple.x == newton.x && apple.y == newton.y) {
            score += 10; energy += 5; 
            apple.y = 1; apple.x = rand() % (WIDTH - 2) + 1;
        }
        // Thunder Strike: Life drops to 1, energy drains [cite: 24, 28]
        if (thunder.x == newton.x && thunder.y == newton.y) {
            lives = 1; energy -= 10; 
            thunder.y = 1; thunder.x = rand() % (WIDTH - 2) + 1;
        }
        // Bomb: Instant Death [cite: 26, 34]
        if (bomb.x == newton.x && bomb.y == newton.y) {
            lives = 0; isRunning = false;
        }

        // GROUND CHECK (Reset objects)
        if (apple.y >= HEIGHT) { apple.y = 1; apple.x = rand() % (WIDTH - 2) + 1; energy--; }
        if (thunder.y >= HEIGHT) { thunder.y = 1; thunder.x = rand() % (WIDTH - 2) + 1; }
        if (bomb.y >= HEIGHT) { bomb.y = 1; bomb.x = rand() % (WIDTH - 2) + 1; }
    }

    // --- SAVE AND CLOSE ---
    system("cls");
    setColor(12);
    cout << "GAME OVER!" << endl;
    cout << "Final Score: " << score << endl;
    saveHighScore(playerName, score);

    return 0;
}

// --- ALL REQUIRED FUNCTIONS ---
void drawBigTitle() {
    int x = 10, y = 3;
    setColor(11);
    string art[] = {
        " _   _  _____  _    _  _____  _____  _   _    __   __",
        "| \\ | ||  ___|| |  | ||_   _||  _  || \\ | |   \\ \\ / /",
        "|  \\| || |__  | |  | |  | |  | | | ||  \\| |    \\ V / ",
        "| . ` ||  __| | |/\\| |  | |  | | | || . ` |     / ^ \\ ",
        "| |\\  || |___ \\  /\\  /  | |  \\ \\_/ /| |\\  |    /_/ \\_\\",
        "\\_| \\_/\\____/  \\/  \\/   \\_/   \\___/ \\_| \\_/           "
    };
    for(int i=0; i<6; i++) { gotoxy(x, y+i); cout << art[i]; }
}

void gotoxy(int x, int y) {
    COORD c = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void drawBorder(int w, int h) {
    setColor(10); 
    for (int i = 0; i < w; i++) {
        gotoxy(i, 0); cout << char(219);
        gotoxy(i, h); cout << char(219);
    }
    for (int i = 0; i <= h; i++) {
        gotoxy(0, i); cout << char(219);
        gotoxy(w - 1, i); cout << char(219);
    }
}

void draw(Entity e) { gotoxy(e.x, e.y); setColor(e.color); cout << e.symbol; }
void erase(Entity e) { gotoxy(e.x, e.y); cout << " "; }

int loadHighScore(string name) {
    ifstream inFile(name + ".txt");
    int high = 0;
    if (inFile >> high) inFile.close();
    return high;
}

void saveHighScore(string name, int currentScore) {
    int lastHigh = loadHighScore(name);
    if (currentScore > lastHigh) {
        ofstream outFile(name + ".txt");
        outFile << currentScore;
        outFile.close();
    }
}