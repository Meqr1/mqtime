#include <conio.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <winuser.h>

#define ROW 5
#define COL 10
#define CHAR_INDEX_MAX 13

enum alph_enum {
  ZERO,
  ONE,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  AM,
  PM,
  COLON
};

typedef struct _alphabets {
  char *line[ROW];
} alphabet;

struct screen_type {
  int rows, columns;
};

alphabet chars[CHAR_INDEX_MAX];

void init_a(enum alph_enum letter) {
  for (int i = 0; i < ROW; i++) {
    chars[letter].line[i] = (char *)malloc(COL);
    if (chars[letter].line[i] == NULL) {
      printf("Memory allocation failed\n");
      exit(1);
    }
  }

  switch (letter) {
  case ZERO:
    strcpy(chars[letter].line[0], " ###### ");
    strcpy(chars[letter].line[1], "##  ####");
    strcpy(chars[letter].line[2], "## ## ##");
    strcpy(chars[letter].line[3], "####  ##");
    strcpy(chars[letter].line[4], " ###### ");
    break;
  // Define digit 1
  case ONE:
    strcpy(chars[letter].line[0], "   ##   ");
    strcpy(chars[letter].line[1], "  ###   ");
    strcpy(chars[letter].line[2], "   ##   ");
    strcpy(chars[letter].line[3], "   ##   ");
    strcpy(chars[letter].line[4], " ###### ");
    break;
  // Define digit 2
  case TWO:
    strcpy(chars[letter].line[0], " ###### ");
    strcpy(chars[letter].line[1], "     ## ");
    strcpy(chars[letter].line[2], " ###### ");
    strcpy(chars[letter].line[3], "##      ");
    strcpy(chars[letter].line[4], " ###### ");
    break;
  // Define digit 3
  case THREE:
    strcpy(chars[letter].line[0], " ###### ");
    strcpy(chars[letter].line[1], "     ## ");
    strcpy(chars[letter].line[2], " ###### ");
    strcpy(chars[letter].line[3], "     ## ");
    strcpy(chars[letter].line[4], " ###### ");
    break;
  // Define digit 4
  case FOUR:
    strcpy(chars[letter].line[0], "##   ## ");
    strcpy(chars[letter].line[1], "##   ## ");
    strcpy(chars[letter].line[2], "####### ");
    strcpy(chars[letter].line[3], "     ## ");
    strcpy(chars[letter].line[4], "     ## ");
    break;
  // Define digit 5
  case FIVE:
    strcpy(chars[letter].line[0], " ###### ");
    strcpy(chars[letter].line[1], "##      ");
    strcpy(chars[letter].line[2], " ###### ");
    strcpy(chars[letter].line[3], "     ## ");
    strcpy(chars[letter].line[4], " ###### ");
    break;
  // Define digit 6
  case SIX:
    strcpy(chars[letter].line[0], " ###### ");
    strcpy(chars[letter].line[1], "##      ");
    strcpy(chars[letter].line[2], "####### ");
    strcpy(chars[letter].line[3], "##   ## ");
    strcpy(chars[letter].line[4], " ###### ");
    break;
  // Define digit 7
  case SEVEN:
    strcpy(chars[letter].line[0], " ###### ");
    strcpy(chars[letter].line[1], "     ## ");
    strcpy(chars[letter].line[2], "    ##  ");
    strcpy(chars[letter].line[3], "   ##   ");
    strcpy(chars[letter].line[4], "   ##   ");
    break;
  // Define digit 8
  case EIGHT:
    strcpy(chars[letter].line[0], " ###### ");
    strcpy(chars[letter].line[1], "##   ## ");
    strcpy(chars[letter].line[2], " ###### ");
    strcpy(chars[letter].line[3], "##   ## ");
    strcpy(chars[letter].line[4], " ###### ");
    break;
  // Define digit 9
  case NINE:
    strcpy(chars[letter].line[0], " ###### ");
    strcpy(chars[letter].line[1], "##   ## ");
    strcpy(chars[letter].line[2], " ###### ");
    strcpy(chars[letter].line[3], "     ## ");
    strcpy(chars[letter].line[4], " ###### ");
    break;
  // Define AM
  case AM:
    strcpy(chars[letter].line[0], "       ");
    strcpy(chars[letter].line[1], "   A   ");
    strcpy(chars[letter].line[2], "   M   ");
    strcpy(chars[letter].line[3], "       ");
    strcpy(chars[letter].line[4], "       ");
    break;
  // Define PM
  case PM:
    strcpy(chars[letter].line[0], "       ");
    strcpy(chars[letter].line[1], "   P   ");
    strcpy(chars[letter].line[2], "   M   ");
    strcpy(chars[letter].line[3], "       ");
    strcpy(chars[letter].line[4], "       ");
    break;
  // Define colon
  case COLON:
    strcpy(chars[letter].line[0], "        ");
    strcpy(chars[letter].line[1], "   ##   ");
    strcpy(chars[letter].line[2], "        ");
    strcpy(chars[letter].line[3], "   ##   ");
    strcpy(chars[letter].line[4], "        ");
    break;
  }
}

struct screen_type get_screen() {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  int columns, rows;

  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
  rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

  struct screen_type screen;

  screen.rows = rows;
  screen.columns = columns;

  return screen;
}

void print_str(const char *word) {
  int i, j;

  struct screen_type screen = get_screen();

  for (int margin = 0; margin < (screen.rows - ROW) / 2; margin++) {
    printf("\n");
  }

  int word_width = (strlen(word) * (4 + 1));
  int horizontal_padding = (screen.columns - word_width) / 2;

  // Print the time in ASCII art
  for (i = 0; i < ROW; i++) {
    for (int pad = 0; pad < horizontal_padding; pad++) {
      printf(" ");
    }

    for (j = 0; j < strlen(word); j++) {
      char ch = word[j];
      if (ch >= '0' && ch <= '9') {
        printf("%s", chars[ch - '0'].line[i]);
      } else if (ch == 'A') {
        printf("%s", chars[AM].line[i]);
      } else if (ch == 'P') {
        printf("%s", chars[PM].line[i]);
      } else if (ch == ':') {
        printf("%s", chars[COLON].line[i]);
      }
      printf(" ");
    }
    printf("\n");
  }
  printf("\n");
}

const char *get_time() {
  static char buffer[80];
  time_t rawtime;
  struct tm *time_info;

  time(&rawtime);
  time_info = localtime(&rawtime);
  strftime(buffer, sizeof(buffer), "%I:%M%p", time_info);

  return buffer;
}

int main() {
  for (int i = ZERO; i <= NINE; i++) {
    init_a(i);
  }
  init_a(AM);
  init_a(PM);
  init_a(COLON);

  while (1) {
    system("cls");

    const char *time_str = get_time();
    print_str(time_str);

    if (kbhit()) {
      char ch = _getch();
      if (ch == 'q' || ch == 'Q') {
        break;
      }
    }

    Sleep(1000);
  }

  for (int i = 0; i < CHAR_INDEX_MAX; i++) {
    for (int j = 0; j < ROW; j++) {
      free(chars[i].line[j]);
    }
  }

  system("cls");

  return 0;
}
