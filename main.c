#include <ncurses.h>

int main() {
    int ch;
    int y = 0, x = 0;
    int x_max, y_max;
    char buff[1024][1024] = {0};

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    getmaxyx(stdscr, y_max, x_max);

    while ((ch = getch()) != 27) {
        if (ch > 32 && ch < 123) {
            buff[y][x] = ch;
            addch(ch);
            if (x < x_max - 1) {
                x++;
            } else if (y < y_max - 1) {
                x = 0;
                y++;
            }
            move(y, x);
        } else if (ch == KEY_BACKSPACE || ch == 127) {
            if (x > 0) {
                x--;
            } else if (y > 0) {
                y--;
                x = x_max - 1;
            }
            move(y, x);
            delch();
            buff[y][x] = '\0';
        } else if (ch == KEY_ENTER || ch == 10) {
            if (y < y_max - 1) {
                y++;
                x = 0;
                move(y, x);
            }
        } else if (ch == KEY_UP) {
            if (y > 0) {
                y--;
                move(y, x);
            }
        } else if (ch == KEY_DOWN) {
            if (y < y_max - 1) {
                y++;
                move(y, x);
            }
        } else if (ch == KEY_LEFT) {
            if (x > 0) {
                x--;
                move(y, x);
            } else if (y > 0) {
                y--;
                x = x_max - 1;
                move(y, x);
            }
        } else if (ch == KEY_RIGHT) {
            if (x < x_max - 1) {
                x++;
                move(y, x);
            } else if (y < y_max - 1) {
                x = 0;
                y++;
                move(y, x);
            }
        } else if (ch == 19) {
            FILE *file = fopen("test.txt", "w");
            if (file == NULL) {
                perror("Error opening file");
                return 1;
            }

            for (int i = 0; i < y_max; i++) {
                for (int j = 0; j < x_max; j++) {
                    if (buff[i][j] != '\0') {
                        fprintf(file, "%c", buff[i][j]);
                    } else {
                        fprintf(file, " ");
                    }
                }
                fprintf(file, "\n");
            }

            fclose(file);
            printw("Array saved to test.txt\n");
            refresh();
        }
    }

    endwin();
    return 0;
}

