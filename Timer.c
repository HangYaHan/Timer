#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>
#include <process.h>
#include <time.h>

volatile bool should_exit = false;  // Global variable to signal program termination

// the time given below is milliseconds
#define MEASURE_DELAY 1000//for the delay between measurements
#define GENERAL_DELAY 1500//for the program delay

//3 types of run-mode for the timer
#define SHORT_INTERVAL 200
#define MEDIUM_INTERVAL 500
#define LONG_INTERVAL 800

void ShowMenu();
void GetMousePosition();
void MeasureLocation();
void SimulateClick(int x, int y);
int AskForInterval();
int Wait4Start(); 
void MonitorKeyboardInput(void *arg);
int Redirect_OK_Position(int *x, int *y);

//---Functions for the timers
void Timer4Zolix_AND_Vimbaviewer();
void Timer4USBCamera_Ocean_ISC();

int main() {
    int choice;

    _beginthread(MonitorKeyboardInput, 0, NULL);
    Sleep(GENERAL_DELAY);
    ShowMenu();

    while (!should_exit) {
        if (scanf("%d", &choice) == 1) {
            switch (choice) {
                case 1: MeasureLocation(); break;
                case 2: Timer4Zolix_AND_Vimbaviewer(); break;
                case 3: Timer4USBCamera_Ocean_ISC(); break;
                default: printf("Invalid choice\n"); break;
            }
            if (!should_exit) {
                ShowMenu();
            }
        }
    }

    printf("Exiting program...\n");
    return 0;
}

// Function to get the current mouse position
void GetMousePosition() {
    POINT p;
    if (GetCursorPos(&p)) {
        printf("Mouse Position: X = %ld, Y = %ld\n", p.x, p.y);
    } else {
        printf("Error retrieving mouse position.\n");
    }
}

// Function to show the mouse location at regular intervals
void MeasureLocation(){
    char ch;
    printf("Press 'q' or 'Q' to quit: ");

    while(1)
    {
        GetMousePosition(0);
        if (_kbhit()) {
            ch = _getch();
            if (ch == 'q' || ch == 'Q') {
            break;
            }
        }
        Sleep(MEASURE_DELAY);
    }
}

// Function to show the menu
void ShowMenu() {
    printf("----------------------------------------------------\n");
    printf("Menu:\n");
    printf("1. Start measuring mouse location\n");
    printf("2. Open timer for Zolix && Vimbaviewer (For 1 PC)\n");
    printf("3. Open timer for USBCamera_Ocean_ISC\n");
    printf("4. test\n");
    printf("5. Exit\n");
    printf("Enter your choice: \n");
    printf("----------------------------------------------------\n");
}

void Timer4Zolix_AND_Vimbaviewer(){
    system("cls");
    printf("-----------------------------------------------------\n");
    printf("Timer for Zolix_AND_Vimbaviewer\n");
    int start_wavelength, step, loops, intervals;
    int ok_pos_x = -1, ok_pos_y = -1;
    char wavelength_str[10];
    time_t start_time, end_time;

    // Get arguments from the user
    printf("Enter the origin wavelength: ");
    scanf("%d", &start_wavelength);
    printf("Enter the step: ");
    scanf("%d", &step);
    printf("Enter the number of loops: ");
    scanf("%d", &loops);
    intervals = AskForInterval();
    Redirect_OK_Position(&ok_pos_x, &ok_pos_y);
    fflush(stdin);
    system("cls");

    printf("----------------------------------------------------\n");
    printf("Checklist: \n");
    printf("----------------------------------------------------\n");
    printf("Origin wavelength: %d\n", start_wavelength);
    printf("Step: %d\n", step);
    printf("Number of loops: %d\n", loops);
    printf("It will probably take %d seconds per loop\n", (intervals * 6 + GENERAL_DELAY) / 1000);
    printf("The 'OK' position is: %d %d\n", ok_pos_x, ok_pos_y);
    printf("The default 'OK' position is: 528 463\n");
    printf("----------------------------------------------------\n");
    printf("Make sure the path to save files is correct. \n");
    printf("Make sure the start wavelength in Vimbaviewer is correct. \n");
    printf("Make sure the layout of windows follows the standard layout. \n");
    printf("--The standard layout is on the top right corner of the desktop. \n");
    printf("It would be better to run this program for 5 loops to test the function. \n");
    printf("--Because the emergency stop function is not available now. \n");
    printf("----------------------------------------------------\n");
    printf("Press any key to start the timer...\n");
    _getch();
    fflush(stdin);

    //Countdown 10 seconds
    for (int i = 10; i > 0; i--) {
        printf("Start in %d seconds...\n", i);
        Sleep(1000);
    }

    printf("Start time reached. \n Starting clicks...\n");
    Sleep(intervals);
    system("cls");

    HWND hWnd = GetConsoleWindow(); 
    ShowWindow(hWnd, SW_MINIMIZE);
    time(&start_time);
    for (int i = 0; i < loops; i++) {
        Sleep(GENERAL_DELAY);

        SetCursorPos(410, 386);
        mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, 410, 386, 0, 0);  // Simulate right click]

        Sleep(intervals);
        SimulateClick(424, 394);
        Sleep(intervals);
        SimulateClick(199, 594);

        sprintf(wavelength_str, "%d", start_wavelength);
        for (int j = 0; j < strlen(wavelength_str); j++) {
            keybd_event(wavelength_str[j], 0, 0, 0);
            keybd_event(wavelength_str[j], 0, KEYEVENTF_KEYUP, 0);
        }

        Sleep(intervals);
        SimulateClick(692, 591);
        Sleep(intervals);
        SimulateClick(ok_pos_x, ok_pos_y);
        Sleep(intervals);
        SimulateClick(1409, 401);

        start_wavelength += step;
    }
    time(&end_time);
    printf("Completed %d clicks.\n", loops);
    printf("Total time taken: %d minutes %d seconds\n", (int)difftime(end_time, start_time) / 60, (int)difftime(end_time, start_time) % 60);
    ShowWindow(hWnd, SW_RESTORE);
    printf("----------------------------------------------------\n");
    printf("Press any key to continue...\n");
    _getch();
    fflush(stdin);
}

void Timer4USBCamera_Ocean_ISC()
{
    system("cls");
    printf("-----------------------------------------------------\n");
    printf("Timer for USBCamera_Ocean_ISC\n");
    int loops, intervals;
    time_t start_time, end_time;

    printf("Enter the number of loops: ");
    scanf("%d", &loops);
    printf("Enter the interval after save  in milliseconds: \n");
    printf("It is strongly recommended to use 5000 ms at least. \n");
    scanf("%d", &intervals);
    fflush(stdin);
    system("cls");

    printf("----------------------------------------------------\n");
    printf("Checklist: \n");
    printf("----------------------------------------------------\n");
    printf("Number of loops: %d\n", loops);
    printf("It will probably take %d seconds per loop\n", (MEDIUM_INTERVAL + intervals + SHORT_INTERVAL + GENERAL_DELAY) / 1000);
    printf("----------------------------------------------------\n");
    printf("Make sure the path to save files is correct. \n");
    printf("Make sure the layout of the 3 windows follows the standard layout. \n");
    printf("It would be better to run this program for 5 loops to test the function. \n");
    printf("--Because the emergency stop function is not available now. \n");
    printf("----------------------------------------------------\n");
    printf("Press any key to start the timer...\n");
    _getch();
    fflush(stdin);

    //Countdown 10 seconds
    for (int i = 10; i > 0; i--) {
        printf("Start in %d seconds...\n", i);
        Sleep(1000);
    }

    printf("Start time reached. \n Starting clicks...\n");
    Sleep(intervals);
    system("cls");

    HWND hWnd = GetConsoleWindow(); 
    ShowWindow(hWnd, SW_MINIMIZE);
    time(&start_time);
    for (int i = 0; i < loops; i++) {
        Sleep(MEDIUM_INTERVAL);
        // Save Spectrum
        SimulateClick(280, 119);
        Sleep(intervals);

        // Save Image
        SimulateClick(953, 15);
        Sleep(SHORT_INTERVAL);
        keybd_event(VK_RETURN, 0, 0, 0);
        keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
        Sleep(GENERAL_DELAY);

        // Change Light
        SimulateClick(842, 653);
        
    }
    time(&end_time);
    printf("Completed %d clicks.\n", loops);
    printf("Total time taken: %d minutes %d seconds\n", (int)difftime(end_time, start_time) / 60, (int)difftime(end_time, start_time) % 60);
    ShowWindow(hWnd, SW_RESTORE);
    printf("----------------------------------------------------\n");
    printf("Press any key to continue...\n");
    _getch();
    fflush(stdin);
}

// Function to simulate a mouse click at a specific position
void SimulateClick(int x, int y) {
    SetCursorPos(x, y);  // Move the cursor to the specified position
    //printf("Click at: X = %d, Y = %d\n", x, y);
    mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, x, y, 0, 0);  // Simulate left click
}

// Function to get the interval type from the user
int AskForInterval() {
    int intervalChoice;
    printf("----------------------------------------------------\n");
    printf("Select interval type:\n");
    printf("1. Short Interval (%d ms) -- It works but have no chance to shutdown \n", SHORT_INTERVAL);
    printf("2. Middle Interval (%d ms)\n", MEDIUM_INTERVAL);
    printf("3. Long Interval (%d ms) -- Tested and Well Performed \n", LONG_INTERVAL);
    printf("----------------------------------------------------\n");
    printf("Enter your choice: ");
    scanf("%d", &intervalChoice);

    switch (intervalChoice) {
        case 1: return SHORT_INTERVAL;
        case 2: return MEDIUM_INTERVAL;
        case 3: return LONG_INTERVAL;
        default:
            printf("Invalid choice. Defaulting to medium Interval.\n");
            return MEDIUM_INTERVAL;
    }
}

// Function to wait for the specified start time
int Wait4Start() {
    int start_hour, start_minute, click_count;

    printf("Enter the start time (HH MM): ");
    scanf("%d %d", &start_hour, &start_minute);

    printf("Enter the number of loops: ");
    scanf("%d", &click_count);

    printf("Waiting for the start time...\n");
    printf("Press 'q' or 'Q' to quit at any time.\n");

    // Wait until the specified start time
    while (1) {
        time_t now = time(NULL);
        struct tm *local = localtime(&now);

        if (local->tm_hour == start_hour && local->tm_min == start_minute) {   
            break;
        }
        Sleep(200);  // Check every 0.2 seconds
    }
    return click_count;
}

// Thread function to monitor keyboard input
void MonitorKeyboardInput(void *arg) {
    while (!should_exit) {
        if (_kbhit()) {  // Check if a key has been pressed
            char ch = _getch();
            if (ch == 'q' || ch == 'Q') {  // If 'q' is pressed, set the exit flag
                should_exit = true;
                printf("Detected 'q'. Exiting...\n");
                exit(-2);
            }
        }
        Sleep(100);  // Poll the keyboard every 100ms
    }
}

int Redirect_OK_Position(int *x, int *y) {
    system("cls");
    printf("-----------------------------------------------------\n");
    printf("Please redirect the position of 'OK' button. \n"); 
    printf("--When the save path is too long, it will make the program fail. \n");
    printf("Press 'Enter' to use the default position. \n");
    printf("--Or enter the new position in the format 'x y'. \n");
    printf("-----------------------------------------------------\n");
    printf("Press 'Enter' to use the default position or enter the new position in the format 'x y':\n");
    // Clear input buffer
    while (getchar() != '\n');
    // Attempt to read user input
    int input_x, input_y;
    int result = scanf("%d %d", &input_x, &input_y);
    if (result == 2) {  // If successfully read two integers
        *x = input_x;
        *y = input_y;
        printf("New position set: X = %d, Y = %d\n", *x, *y);
    } else if (result == 0) {  // If user presses Enter directly
        *x = 528;  // Default X position
        *y = 463;  // Default Y position
        printf("Using default position: X = %d, Y = %d\n", *x, *y);
    } else {  // If input is invalid
        printf("Invalid input. Using default position: X = %d, Y = %d\n", 528, 463);
        *x = 528;
        *y = 463;
    }
    // Clear input buffer to prevent interference with subsequent input
    while (getchar() != '\n');
    return 0;
}