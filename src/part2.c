/**
 * ENGG1110 Problem Solving by Programming
 *
 * Course Project - Maze
 *
 * I declare that the project here submitted is original
 * except for source material explicitly acknowledged,
 * and that the same or closely related material has not been
 * previously submitted for another course.
 * I also acknowledge that I am aware of University policy and
 * regulations on honesty in academic work, and of the disciplinary
 * guidelines and procedures applicable to breaches of such
 * policy and regulations, as contained in the website.
 *
 * I have read and understood the University policy on
 * the use of AI for academic work. I confirm that I have complied
 * with the instructions given by my course teacher(s) regarding the
 * use of AI tools for this project work and consent to the
 * use of AI content detection software to review my submission.
 *

 * University Guideline on Academic Honesty:
 *   https://www.cuhk.edu.hk/policy/academichonesty/
 *
 * Student Name  : Cheng Wing Yan
 * Student ID    : 1155257516
 * Class/Section : ENGG1110E
 * Date          :
 */


/* Passing all test cases DOES NOT guarantee full marks.
   Please follow the specifications and test more cases on your own */


#include <stdio.h>
#include <stdlib.h>

/* NO other header files are allowed */

/* NO global variables are allowed
   Can declare your own local variable (inside functions) if needed */

/* Macros (symbolic constants) */
#define WIDTH 10
#define HEIGHT 10
#define ROW 0
#define COL 1


/* DO NOT change the functions below, including the return type and parameters.
   Any changes will result in mark deduction.

   You can define your own functions if needed. */

// Part one functions
void printMaze(char mazeGameBoard[HEIGHT][WIDTH], int player[2]);
int movePlayerOneStep(char mazeGameBoard[HEIGHT][WIDTH], int player[2], int input);
void mirrorMaze(char mazeGameBoard[HEIGHT][WIDTH], int player[2]);


// // Uncomment the later functions in part two
// // crl+L or cmd+L to comment/uncomment
// // Part two functions
// void initGameBoardFromFile(char mazeGameBoard[HEIGHT][WIDTH], int player[2]);
// void rotateMaze90(char mazeGameBoard[HEIGHT][WIDTH], int player[2]) ;
// int movePlayerMultiSteps(char mazeGameBoard[HEIGHT][WIDTH], int player[2], int input) ;


////////////////////Part One///////////////////////////////


/* Display the game board on the screen
   You are required to follow exactly the output format stated in the project specification
 */
void printMaze(char mazeGameBoard[HEIGHT][WIDTH], int player[2]) {
    /* Output Message */
    printf("Maze:\n");
    int i, j;
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            if (i == player[0] && j == player[1]) {
                printf("@@");
            } else if (mazeGameBoard[i][j] == 'W') {
                printf("[]");
            } else if (mazeGameBoard[i][j] == 'E') {
                printf("EX");
            } else if (mazeGameBoard[i][j] == 'M') {
                printf("mr");
            } else if (mazeGameBoard[i][j] == '.') {
                printf("  ");
            } else if (mazeGameBoard[i][j] == 'R') {
                printf("rc");
            }
        }
        printf("\n");
    }
}


/* Move the player one step in the input direction (2=down, 4=left, 6=right, 8=up)
   Return moved step, 1 if the move is successful, 0 otherwise
 */
int movePlayerOneStep(char mazeGameBoard[HEIGHT][WIDTH], int player[2], int input) {
    int tempX, tempY;
    tempX = player[0];
    tempY = player[1];
    if (input == 8) {
        tempX--;
    } else if (input == 2) {
        tempX++;
    } else if (input == 4) {
        tempY--;
    } else if (input == 6) {
        tempY++;
    }
    if (mazeGameBoard[tempX][tempY] == 'W') {
        printf("You hit a wall!\n");
        return 0;
    }
    player[0] = tempX;
    player[1] = tempY;
    return 1;
}


/* Mirror the maze horizontally (left-right)
   Update the player's position accordingly
 */
void mirrorMaze(char mazeGameBoard[HEIGHT][WIDTH], int player[2]) {
    int i, j;
    char temp;
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH / 2; j++) {
            temp = mazeGameBoard[i][j];
            mazeGameBoard[i][j] = mazeGameBoard[i][WIDTH - 1 - j];
            mazeGameBoard[i][WIDTH - 1 - j] = temp;
        }
    }
    player[1] = WIDTH - player[1] - 1;
    printf("You found a mirror item! Maze is now mirrored.\n");
}


////////////////////Part Two///////////////////////////////

//Uncomment the later functions in part two
// crl+L or cmd+L to comment/uncomment

/* Initialize the maze game board and player position from a file
   If failed, terminate the program immediantly
*/
void initGameBoardFromFile(char mazeGameBoard[HEIGHT][WIDTH], int player[2]) {
    FILE *fptr;
    fptr = fopen("gameboard.txt", "r");
    if (fptr == NULL) {
        printf("Error: Unable to open gameboard.txt\n");
        printf("=====Game Over=====");
        exit(1);
    }


    int i, j;
    char buffer[100];
    for (i = 0; i < HEIGHT; i++) {
        if (fgets(buffer, sizeof(buffer), fptr) != NULL) {
            for (j = 0; j < WIDTH && buffer[j] != '\n' && buffer[j] != '\0'; j++) {
                mazeGameBoard[i][j] = buffer[j];
            }
        }
    }

    fscanf(fptr, "%d%d", &player[0], &player[1]);
    fclose(fptr);
}


/* Rotate the maze 90 degrees clockwise
   Update the player's position (rotate as well)
 */
void rotateMaze90(char mazeGameBoard[HEIGHT][WIDTH], int player[2]){
    char rotated[HEIGHT][WIDTH];
    int i, j, tempX;
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            rotated[j][WIDTH-1-i]=mazeGameBoard[i][j];
        }
    }
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            mazeGameBoard[i][j]=rotated[i][j];
        }
    }
    tempX = player[0];
    player[0] = player[1];
    player[1] = HEIGHT-1-tempX;
    printf("You found a rotation item! Maze is now rotated.\n");

}


/* Move the player continuously in the input direction until the condition met given by the project specification
   Return moved steps
 */
int movePlayerMultiSteps(char mazeGameBoard[HEIGHT][WIDTH], int player[2], int input) {
    int tempY, tempX, step = 0, wall;
    tempY = player[0];
    tempX = player[1];
    while (1) {
        if (input == 8) tempY--;
        else if (input == 2) tempY++;
        else if (input == 4) tempX--;
        else if (input == 6) tempX++;
        if (mazeGameBoard[tempY][tempX] == 'W') {
            if (step == 0) {
                printf("You hit a wall!\n");
            }
            break;
        }
        if (mazeGameBoard[tempY][tempX] == 'M' || mazeGameBoard[tempY][tempX] =='R') {
            if (step == 0) {
                player[0] = tempY;
                player[1] = tempX;
                step++;
                break;
            }
            break;
        }
        step++;
        player[0] = tempY;
        player[1] = tempX;
        wall = 0;
        if (mazeGameBoard[tempY - 1][tempX] == 'W') wall++;
        if (mazeGameBoard[tempY + 1][tempX] == 'W') wall++;
        if (mazeGameBoard[tempY][tempX - 1] == 'W') wall++;
        if (mazeGameBoard[tempY][tempX + 1] == 'W') wall++;
        if (wall <= 1) {
            break;
        }
    }

    return step;
}


////////////////////////////////////////////////////////////////////////


/* The main function */


int main() {
    // /* Local variables */
    // char mazeGameBoard[HEIGHT][WIDTH] = {
    //     {'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'},
    //     {'W', '.', '.', 'M', 'W', '.', '.', '.', '.', 'W'},
    //     {'W', '.', 'W', '.', 'W', '.', 'W', 'W', '.', 'W'},
    //     {'W', '.', 'W', '.', '.', '.', '.', 'W', '.', 'W'},
    //     {'W', '.', 'W', 'W', 'E', 'W', '.', 'W', '.', 'W'},
    //     {'W', '.', '.', '.', '.', 'W', '.', 'W', '.', 'W'},
    //     {'W', 'W', 'W', 'W', '.', 'W', '.', 'W', '.', 'W'},
    //     {'W', '.', '.', 'W', '.', 'W', 'W', 'W', '.', 'W'},
    //     {'W', '.', '.', '.', '.', '.', '.', '.', '.', 'W'},
    //     {'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'E', 'W'}
    // };

    char mazeGameBoard[HEIGHT][WIDTH];
    // Player position and step counter
    int player[2] = {1, 1}, steps = 0;

    // Demonstrate the using of Macros ROW and COL
    player[ROW] = 1;
    player[COL] = 1;


    //Can declare your own local variable if needed


    int input, temp;
    initGameBoardFromFile(mazeGameBoard, player);

    printf("Welcome to the Maze Game!\n");
    printf("Use 8(up) 2(down) 4(left) 6(right) to move or -1 to quit the game. \nReach 'EX' to win.\n");


    printMaze(mazeGameBoard, player); // call functions


    /* Output Message */
    while (1) {
        printf("Steps: %d\n", steps);

        printf("Enter move direction (8/2/4/6) or -1 to quit the game: ");

        scanf("%d", &input);
        if (input == -1) {
            printf("You chose to quit the maze.\n");
            printf("=====Game Over=====");
            break;
        }
        if (input != 8 && input != 2 && input != 4 && input != 6) {
            printf("Invalid input!\nPlease use 8(up) 2(down) 4(left) 6(right) or -1(quit).\n");
        } else if (temp = movePlayerMultiSteps(mazeGameBoard, player, input)) {
            steps += temp;
            if (mazeGameBoard[player[0]][player[1]] == 'E') {
                printf("You reached the exit in %d steps.\n", steps);
                printf("=====Congratulations=====");
                break;
            }
            if (mazeGameBoard[player[0]][player[1]] == 'M') {
                mirrorMaze(mazeGameBoard, player);
            }
            if (mazeGameBoard[player[0]][player[1]] == 'R') {
                rotateMaze90(mazeGameBoard, player);
            }

        }
        printMaze(mazeGameBoard, player);
    }


 return 0;
}
