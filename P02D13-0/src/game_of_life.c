#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
// #include <sys/select.h>
#include <time.h>
// #include <unistd.h>

int allot(int ***a, int n, int m);
void output(int **a, int n, int m, int age, int speed_counter);
void my_clear();
void fill(int **a, int n, int m);
// int my_sleep(int num);
void control(int *speed, const char *c, int *speed_counter, int *end_of_game);
void life_step(int **buffer1, int **buffer2, int n, int m, int *end_of_game);
void welcome();
void game_over();
void fill_random(int **buff, int n, int m);
void check_stdin(int **buff, int n, int m);
void my_swap(int **buffer1, int **buffer2, int n, int m);

int main() {
  // fd_set rfds;
  // struct timeval tv;
  // tv.tv_sec = 0;
  // tv.tv_usec = 0;

  int n = 25;
  int m = 80;
  // int speed = 37;
  int speed_counter = 3;
  int **buff1 = NULL;
  int **buff2 = NULL;
  int end_of_game = 0;
  // char c;

  // welcome();

  if (!allot(&buff1, n, m) && !allot(&buff2, n, m)) {
    int age = 1;

    check_stdin(buff1, n, m);

    // system("stty -icanon -echo");

    while (!end_of_game) {
      output(buff1, n, m, age, speed_counter);
      // c = 0;
      // FD_ZERO(&rfds);
      // FD_SET(0, &rfds);
      // int ready_for_reading = select(1, &rfds, NULL, NULL, &tv);
      // if (ready_for_reading) {
      //   c = getchar();
      // // }
      life_step(buff1, buff2, n, m, &end_of_game);
      // control(&speed, &c, &speed_counter, &end_of_game);
      Sleep(300);
      // if (age % 500 == 0) {
      //   printf("If you want to arrange an armageddon, press q\nBe mercy - any key\n");
      //   c = 0;
      //   if ((c = getchar()) == 'q')
      //     end_of_game = 1;
      // }
      // age++;
      my_clear();
    }
  }

  // game_over();

  for (int i = 0; i < n; i++)
    free(buff1[i]);
  free(buff1);

  for (int i = 0; i < n; i++)
    free(buff2[i]);
  free(buff2);

  return 0;
}

int allot(int ***a, int n, int m) {
  int exit = 0;

  (*a) = malloc(n * sizeof(int *));

  for (int i = 0; i < n; i++)
    (*a)[i] = malloc(m * sizeof(int));

  if (!(*a))
    exit = 1;

  return exit;
}

void output(int **a, int n, int m, int age, int speed_counter) {
  char space = ' ';

  printf("█");
  for (int i = 1; i <= m; i++)
    printf("█");
  printf("█");

  printf("\n");
  for (int i = 0; i < n; i++) {
    printf("█");

    for (int j = 0; j < m; j++) {
      if (a[i][j] == 0)
        printf("%c", space);
      else
        printf("*");
    }

    printf("█");
    putchar('\n');
  }

  printf("█");
  for (int i = 0; i < m; i++)
    printf("█");
  printf("█");

  printf("\ncurrent speed: ");
  if (speed_counter == 0)
    printf("very slow  ");
  else if (speed_counter == 1)
    printf("slow       ");
  else if (speed_counter == 2)
    printf("medium     ");
  else if (speed_counter == 3)
    printf("fast       ");
  else if (speed_counter == 4)
    printf("madness    ");
  else if (speed_counter == 5)
    printf("light quick");
  for (int i = 0; i < m - 35; i++)
    printf("%c", space);
  printf("age: %d", age);
  printf("\nUp speed: W\nDown speed: S\nPress Q to EXIT\n");
}

void fill(int **a, int n, int m) {
  char c = 0;

  for (int i = 0; i < n && c != EOF; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%d%c", &a[i][j], &c);
    }
  }
  my_clear();
}

void my_clear() { printf("\x1B[2J\x1B[H"); }

// int my_sleep(int num) {
//   if (num == 1 || num == 2)
//     return 1;
//   return my_sleep(num - 1) + my_sleep(num - 2);
// }

void control(int *speed, const char *c, int *speed_counter, int *end_of_game) {
  if (*speed > 35 && *speed < 40) {
    if (*c == 'w' || *c == 'W') {
      *speed -= 1;
      *speed_counter += 1;
    } else if (*c == 's' || *c == 'S') {
      *speed += 1;
      *speed_counter -= 1;
    }
  } else if (*speed == 35) {
    if (*c == 's' || *c == 'S') {
      *speed += 1;
      *speed_counter -= 1;
    }
  } else if (*speed == 40) {
    if (*c == 'w' || *c == 'W') {
      *speed -= 1;
      *speed_counter += 1;
    }
  }
  if (*c == 'q' || *c == 'Q') {
    *end_of_game = 1;
  }
}

void life_step(int **buffer1, int **buffer2, int n, int m, int *end_of_game) {
  int neighbours;
  int exit = 0;

  exit = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (buffer1[i][j] == 1) {
        exit = 1;
        break;
      }
    }
    if (exit)
      break;
  }

  if (!exit)
    *end_of_game = 1;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      neighbours = 0;
      for (int x = -1; x < 2; x++) {
        for (int y = -1; y < 2; y++) {
          if (x != 0 || y != 0) {
            neighbours += buffer1[(i + x + n) % n][((j + y + m) % m)];
          }
        }
      }

      if ((neighbours == 3)) {
        buffer2[i][j] = 1;
      } else if (neighbours == 2) {
        buffer2[i][j] = buffer1[i][j];
      } else {
        buffer2[i][j] = 0;
      }
    }
  }
  my_swap(buffer1, buffer2, n, m);
}

void fill_random(int **buff, int n, int m) {
  srand(time(NULL));

  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      buff[i][j] = rand() % 2;
}

void check_stdin(int **buff, int n, int m) {
  // if (!isatty(fileno(stdin))) {
  //   fill(buff, n, m);
  //   if (freopen("/dev/tty", "r", stdin))
  //     perror("/dev/tty");
  // } else {
    fill_random(buff, n, m);
  // }
}

void my_swap(int **buffer1, int **buffer2, int n, int m) {
  int tmp;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      tmp = buffer1[i][j];
      buffer1[i][j] = buffer2[i][j];
      buffer2[i][j] = tmp;
    }
  }
}

void welcome() {
  Sleep(1000);
  my_clear();
  printf("╔╗╔╗╔╦═══╦╗ ╔══╦══╦╗  ╔╦═══╗╔════╦══╗\n");
  Sleep(1000);
  printf("║║║║║║╔══╣║ ║╔═╣╔╗║║  ║║╔══╝╚═╗╔═╣╔╗║\n");
  Sleep(1000);
  printf("║║║║║║╚══╣║ ║║ ║║║║╚╗╔╝║╚══╗  ║║ ║║║║\n");
  Sleep(1000);
  printf("║║║║║║╔══╣║ ║║ ║║║║╔╗╔╗║╔══╝  ║║ ║║║║\n");
  Sleep(1000);
  printf("║╚╝╚╝║╚══╣╚═╣╚═╣╚╝║║╚╝║║╚══╗  ║║ ║╚╝║\n");
  Sleep(1000);
  printf("╚═╝╚═╩═══╩══╩══╩══╩╝  ╚╩═══╝  ╚╝ ╚══╝\n");
  Sleep(1000);
  printf("╔════╦╗╔╦═══╗ ╔╗ ╔══╦══╦═══╗\n");
  Sleep(1000);
  printf("╚═╗╔═╣║║║╔══╝ ║║ ╚╗╔╣╔═╣╔══╝\n");
  Sleep(1000);
  printf("  ║║ ║╚╝║╚══╗ ║║  ║║║╚═╣╚══╗\n");
  Sleep(1000);
  printf("  ║║ ║╔╗║╔══╝ ║║  ║║║╔═╣╔══╝\n");
  Sleep(1000);
  printf("  ║║ ║║║║╚══╗ ║╚═╦╝╚╣║ ║╚══╗\n");
  Sleep(1000);
  printf("  ╚╝ ╚╝╚╩═══╝ ╚══╩══╩╝ ╚═══╝\n");
  Sleep(1000);
  // my_Sleep(43);
}

void game_over() {
  my_clear();
  printf("╔═══╦══╦╗  ╔╦═══╗   ╔══╦╗╔╦═══╦═══╗\n");
  Sleep(1000);
  printf("║╔══╣╔╗║║  ║║╔══╝   ║╔╗║║║║╔══╣╔═╗║\n");
  Sleep(1000);
  printf("║║╔═╣╚╝║╚╗╔╝║╚══╗   ║║║║║║║╚══╣╚═╝║\n");
  Sleep(1000);
  printf("║║╚╗║╔╗║╔╗╔╗║╔══╝   ║║║║╚╝║╔══╣╔╗╔╝\n");
  Sleep(1000);
  printf("║╚═╝║║║║║╚╝║║╚══╗   ║╚╝╠╗╔╣╚══╣║║║\n");
  Sleep(1000);
  printf("╚═══╩╝╚╩╝  ╚╩═══╝   ╚══╝╚╝╚═══╩╝╚╝\n");
  Sleep(1000);
}
