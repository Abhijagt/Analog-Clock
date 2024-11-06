#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <ctime>

#define PI 3.14159265

// Function to draw the clock's circle (clock face)
void drawClockFace(int centerX, int centerY, int radius) {
    setcolor(WHITE);
    circle(centerX, centerY, radius);  // Draw the outer clock circle

    // Draw the numbers around the clock (12, 3, 6, 9)
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 2);
    outtextxy(centerX - 10, centerY - radius + 10, "12");
    outtextxy(centerX + radius - 30, centerY - 10, "3");
    outtextxy(centerX - 10, centerY + radius - 30, "6");
    outtextxy(centerX - radius + 10, centerY - 10, "9");
}

// Function to draw clock hands
void drawClockHands(int centerX, int centerY, int hour, int minute, int second, int radius) {
    // Calculate angle for hour hand (360 degrees / 12 hours)
    float hourAngle = (hour % 12 + minute / 60.0) * 30.0;  // 30 degrees per hour

    // Calculate angle for minute hand (360 degrees / 60 minutes)
    float minuteAngle = (minute + second / 60.0) * 6.0;  // 6 degrees per minute

    // Calculate angle for second hand (360 degrees / 60 seconds)
    float secondAngle = second * 6.0;  // 6 degrees per second

    // Hour hand (shorter)
    int hourHandLength = radius - 40;
    int hourX = centerX + hourHandLength * cos((90 - hourAngle) * PI / 180);
    int hourY = centerY - hourHandLength * sin((90 - hourAngle) * PI / 180);
    setcolor(YELLOW);
    line(centerX, centerY, hourX, hourY);

    // Minute hand (longer)
    int minuteHandLength = radius - 20;
    int minuteX = centerX + minuteHandLength * cos((90 - minuteAngle) * PI / 180);
    int minuteY = centerY - minuteHandLength * sin((90 - minuteAngle) * PI / 180);
    setcolor(GREEN);
    line(centerX, centerY, minuteX, minuteY);

    // Second hand (longest)
    int secondHandLength = radius - 10;
    int secondX = centerX + secondHandLength * cos((90 - secondAngle) * PI / 180);
    int secondY = centerY - secondHandLength * sin((90 - secondAngle) * PI / 180);
    setcolor(RED);
    line(centerX, centerY, secondX, secondY);
}

int main() {
    // Initialize graphics
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Get the center of the window and the radius for the clock face
    int centerX = getmaxx() / 2;
    int centerY = getmaxy() / 2;
    int radius = 150;

    while (!kbhit()) {  // Loop until a key is pressed
        cleardevice();  // Clear the previous frame

        // Get the current time
        time_t t = time(0);
        struct tm* currentTime = localtime(&t);

        // Draw the clock face
        drawClockFace(centerX, centerY, radius);

        // Draw the clock hands
        drawClockHands(centerX, centerY, currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec, radius);

        delay(1000);  // Delay for 1 second to update the clock
    }

    // Close the graphics window
    closegraph();
    return 0;
}