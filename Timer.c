#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>
#include <process.h>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

volatile bool should_exit = false;  // Global variable to signal program termination

// the time given below is milliseconds
#define MEASURE_DELAY 1000//for the delay between measurements
#define GENERAL_DELAY 1500//for the program delay

#define DEBUG_PATH "."

//3 types of run-mode for the timer
#define SHORT_INTERVAL 200
#define MEDIUM_INTERVAL 500
#define LONG_INTERVAL 800

void ShowMenu();
void GetMousePosition();
void MeasureLocation();
void Timer4Zolix_AND_Vimbaviewer();
void Timer4CustomizeCamera();
void Test4files_counter();
void SimulateClick(int x, int y);
int AskForInterval();
int Wait4Start(); 
void MonitorKeyboardInput(void *arg);
int Redirect_OK_Position(int *x, int *y);
void Timer4HC_Camera_AND_ISC();
void Timer4HC_Camera_AND_Zolix();
void Timer4_06_11();
int get_n_files_in_directory(const char *path);
void get_path(char *path_spec, char *path_image);
void delete_last_file(const char *path);

int main() {
    int choice;

    // char* path_spec = (char *)malloc(MAX_PATH * sizeof(char));
    // char* path_image = (char *)malloc(MAX_PATH * sizeof(char));
    // get_path(path_spec, path_image);
    // printf("files in path_spec: %d\n", get_n_files_in_directory(path_spec));
    // printf("files in path_image: %d\n", get_n_files_in_directory(path_image));

    // delete_last_file(path_spec);

    // printf("files in path_spec: %d\n", get_n_files_in_directory(path_spec));
    // printf("files in path_image: %d\n", get_n_files_in_directory(path_image));


    _beginthread(MonitorKeyboardInput, 0, NULL);
    Sleep(GENERAL_DELAY);
    ShowMenu();

    while (!should_exit) {
        if (scanf("%d", &choice) == 1) {
            switch (choice) {
                case 0: Test4files_counter(); break;
                case 1: MeasureLocation(); break;
                // case 2: Timer4Zolix();      break;
                // case 3: Timer4Vimbaviewer();break;
                // case 4: Timer4Morph();      break;
                case 2: Timer4Zolix_AND_Vimbaviewer(); break;
                case 3: Timer4HC_Camera_AND_ISC(); break;
                case 4: Timer4_06_11(); break;
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
    printf("Rules NO.01: NO Chinese in everywhere, please!!!\n");
    printf("----------------------------------------------------\n");
    printf("Menu:\n");
    printf("0. Test for files counter\n");
    printf("1. Start measuring mouse location\n");
    printf("2. Open timer for Zolix && Vimbaviewer (For 1 PC)\n");
    printf("3. Open timer for HC_Camera && ISC\n");
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

void Timer4CustomizeCamera()
{
    system("cls");
    printf("Timer for Customize Camera\n");
    int loops, intervals;
    time_t start_time, end_time;

    // Get arguments from the user
    printf("Enter the number of loops: ");
    scanf("%d", &loops);
    intervals = AskForInterval();
    fflush(stdin);
    system("cls");

    printf("----------------------------------------------------\n");
    printf("Checklist: \n");
    printf("----------------------------------------------------\n");
    printf("Number of loops: %d\n", loops);
    printf("It will probably take %d seconds per loop\n", (intervals * 6 + GENERAL_DELAY) / 1000);
    printf("----------------------------------------------------\n");
    printf("Make sure the path to save files is correct. \n");
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

        SimulateClick(377, 35);
        Sleep(intervals);
        keybd_event('W', 0, 0, 0);
        keybd_event('W', 0, KEYEVENTF_KEYUP, 0);
        Sleep(intervals);
        SimulateClick(1409, 401);
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

void Timer4HC_Camera_AND_ISC() {
    system("cls");
    printf("-----------------------------------------------------\n");
    printf("Timer for HC_Camera_AND_ISC\n");
    int loops;
    int intervals;

    printf("Enter the number of loops: ");
    scanf("%d", &loops);
    fflush(stdin);
    printf("Enter the interval for photos(ms) : ");
    scanf("%d", &intervals);
    fflush(stdin);

    system("cls");

    printf("----------------------------------------------------\n");
    printf("Checklist: \n");
    printf("----------------------------------------------------\n");
    printf("Number of loops: %d\n", loops);
    printf("It will probably take %d seconds per loop\n", (intervals * 2 + GENERAL_DELAY) / 1000);
    printf("----------------------------------------------------\n");
    printf("Make sure the path to save files is correct. \n");
    printf("Make sure the start wavelength in Vimbaviewer is correct. \n");
    printf("Make sure the layout of windows follows the standard layout. \n");
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

    for (int i = 0; i < loops; i++) {
        SimulateClick(649, 111);
        Sleep(intervals);
        SimulateClick(221, 414);
        Sleep(SHORT_INTERVAL);
        SimulateClick(307, 421);
        Sleep(SHORT_INTERVAL);
    }
    printf("Completed %d clicks.\n", loops);
    printf("----------------------------------------------------\n");
    printf("Press any key to continue...\n");
    _getch();
    fflush(stdin);
}

void Timer4HC_Camera_AND_Zolix(){
    system("cls");
    printf("-----------------------------------------------------\n");
    printf("Timer for HC_Camera_AND_ISC\n");
    int loops;
    int intervals;

    printf("Enter the number of loops: ");
    scanf("%d", &loops);
    fflush(stdin);
    printf("Enter the interval for photos(ms) : ");
    scanf("%d", &intervals);
    fflush(stdin);

    system("cls");

    for (int i = 10; i > 0; i--) {
        printf("Start in %d seconds...\n", i);
        Sleep(1000);
    }

    for (int i = 0; i < loops; i++) {
        SimulateClick(146, 129);
        Sleep(intervals);
        SimulateClick(1402, 401);
        Sleep(SHORT_INTERVAL);
    }
    printf("Completed %d clicks.\n", loops);
    printf("----------------------------------------------------\n");
    printf("Press any key to continue...\n");
    _getch();
    fflush(stdin);
}

void Timer4_06_11(){
    
    int loops;
    int n_specs = 0;
    int n_images = 0;
    char path_spec[MAX_PATH];
    char path_image[MAX_PATH];

    printf("-----------------------------------------------------\n");
    printf("Timer for 06_11\n");
    printf("Enter the number of loops: ");
    scanf("%d", &loops);
    fflush(stdin);
    system("cls");
    get_path(path_spec, path_image);



    printf("----------------------------------------------------\n");
    printf("Checklist: \n");
    printf("----------------------------------------------------\n");
    printf("Number of loops: %d\n", loops);
    printf("It will probably take %d seconds per loop\n", (LONG_INTERVAL * 3 + GENERAL_DELAY) / 1000);
    printf("spec path: %s, and it has %d files now.\n", path_spec, get_n_files_in_directory(path_spec));
    printf("image path: %s, and it has %d files now.\n", path_image, get_n_files_in_directory(path_image));
    printf("----------------------------------------------------\n");
    printf("Press any key to start the timer...\n");
    _getch();
    fflush(stdin);

    //Countdown 10 seconds
    for (int i = 10; i > 0; i--) {
        printf("Start in %d seconds...\n", i);
        Sleep(1000);
    }

    for (int i = 0; i < loops; i++) {
        n_images = get_n_files_in_directory(path_image);
        n_specs = get_n_files_in_directory(path_spec);
        if (n_images != n_specs) {
            system("cls");
            printf("----------------------------------------------------\n");
            printf("Error!\n");
            printf("The number of files in the path_image (%d) and path_spec (%d) is not equal.\n", n_images, n_specs);
            printf("Current loop: %d\n", i + 1);
            printf("----------------------------------------------------\n");
            printf("Calling auto delete function...\n");
            if (n_images > n_specs) {
                delete_last_file(path_image);
                n_images = get_n_files_in_directory(path_image);
            } else {
                delete_last_file(path_spec);
                n_specs = get_n_files_in_directory(path_spec);
            }

            if (n_images != n_specs) {
                printf("The number of files in the path_image (%d) and path_spec (%d) is still not equal.\n", n_images, n_specs);
                printf("Fatal error! The program will exit now.\n");
                return; 
            } else {
                printf("The number of files in the path_image (%d) and path_spec (%d) is now equal.\n", n_images, n_specs);
                printf("Continuing the timer...\n");
            }
        }   

        Sleep(SHORT_INTERVAL);
        SimulateClick(838, 276);
        Sleep(SHORT_INTERVAL);
        SimulateClick(277, 119);
        Sleep(SHORT_INTERVAL);
        SimulateClick(918, 465);
        Sleep(3000);
    }

    printf("Completed %d clicks.\n", loops);
    printf("----------------------------------------------------\n");
    printf("Press any key to continue...\n");
    _getch();
    fflush(stdin);
}

int get_n_files_in_directory(const char *path) {
    DIR *dir;
    struct dirent *entry;
    int fileCount = 0;
    char fullpath[MAX_PATH];
    struct _stat st;

    dir = opendir(path);
    if (dir == NULL) {
        perror("Failed to open directory");
        return -1;
    }
    while ((entry = readdir(dir)) != NULL) {
        // Skip . and ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        snprintf(fullpath, sizeof(fullpath), "%s\\%s", path, entry->d_name);
        if (_stat(fullpath, &st) == 0 && (st.st_mode & _S_IFREG)) {
            fileCount++;
        }
    }
    closedir(dir);
    return fileCount;
}

void get_path(char *path_spec, char *path_image) {
    const char * path = ".\\Config.txt";
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        printf("Failed to open config file: %s\n", path);
        return;
    }
    if (fgets(path_spec, MAX_PATH, fp) == NULL) {
        printf("Failed to read path_spec\n");
        fclose(fp);
        return;
    }
    if (fgets(path_image, MAX_PATH, fp) == NULL) {
        printf("Failed to read path_image\n");
        fclose(fp);
        return;
    }
    // Remove newline characters
    path_spec[strcspn(path_spec, "\r\n")] = 0;
    path_image[strcspn(path_image, "\r\n")] = 0;
    printf("Read path_spec: %s\n", path_spec);
    printf("Read path_image: %s\n", path_image);
    fclose(fp);
}

void Test4files_counter() {
    system("cls");
    printf("----------------------------------------------------\n");
    printf("Testing file counter...\n");

    char path_spec[MAX_PATH];
    char path_image[MAX_PATH];
    get_path(path_spec, path_image);
    printf("Files in path_spec: %d\n", get_n_files_in_directory(path_spec));
    printf("Files in path_image: %d\n", get_n_files_in_directory(path_image));
    printf("----------------------------------------------------\n");
    printf("Press any key to continue...\n");
    _getch();
    fflush(stdin);
    system("cls");
}
// Delete the most recently created (last modified) file in the directory
void delete_last_file(const char *path) {
    DIR *dir;
    struct dirent *entry;
    struct _stat fileStat;
    char filePath[1024];
    time_t latestTime = 0;
    char latestFile[1024] = {0};

    dir = opendir(path);
    if (dir == NULL) {
        perror("Failed to open directory");
        return;
    }
    while ((entry = readdir(dir)) != NULL) {
        // Skip . and ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        snprintf(filePath, sizeof(filePath), "%s\\%s", path, entry->d_name);
        if (_stat(filePath, &fileStat) < 0) {
            perror("Failed to get file info");
            continue;
        }
        if ((fileStat.st_mode & _S_IFREG)) {
            if (fileStat.st_mtime > latestTime) {
                latestTime = fileStat.st_mtime;
                strncpy(latestFile, entry->d_name, sizeof(latestFile) - 1);
                latestFile[sizeof(latestFile) - 1] = '\0';
            }
        }
    }
    closedir(dir);
    if (latestFile[0] != '\0') {
        snprintf(filePath, sizeof(filePath), "%s\\%s", path, latestFile);
        if (remove(filePath) == 0) {
            printf("Deleted file: %s\n", filePath);
        } else {
            perror("Failed to delete file");
        }
    } else {
        printf("No file to delete in the directory.\n");
    }
}
