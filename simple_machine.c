#include<stdio.h>
#include<string.h>

#define TAPE_SIZE 256

int tape[TAPE_SIZE];
int head = 0;
int accumunaltor = 0;

#define COMM_SIZE 9

char * commands[COMM_SIZE] = {
    "MOVL",     // Moves the head left
    "MOVR",     // Moves the head right
    "READ",     // Reads value of head into accumulator
    "WRITE",    // Write value in accumulator to head
    "ADD",      // Add value at tape head to accumulator       
    "SUB",      // Subtract value at tape head from accumulator
    "LOAD",     // Load given value in accumulator
    "NOP",      // End of command sequence
    "PMST",     // Print machine state
};

int print_state() {
    printf("Head at: %d\n", head);
    printf("Value in accumulator: %d\n", accumunaltor);
    for (int i = -2; i <= 2; i++) {
        if (head + i >= 0 && head + i < 256) {
            printf(" %d ", head + i);
        }
    }
    printf("\n");
    for (int i = -2; i <= 2; i++) {
        if (head + i >= 0 && head + i < 256) {
            printf(" %d ", tape[(head + i) % TAPE_SIZE]);
        }
    }
    printf("\n");
    return 0;
}

int read() {
    accumunaltor = tape[head];
    return accumunaltor;
}

int write() {
    tape[head] = accumunaltor;
    return tape[head];
}

int movr(int amt) {
    if (head < TAPE_SIZE - amt) {
        head += amt;
    } else {
        head = TAPE_SIZE;
    }
    return head;
}

int movl(int amt) {
    if (head >= amt) {
        head -= amt;
    } else {
        head = 0;
    }
    return head;
}

int add() {
    accumunaltor += tape[head];
    return accumunaltor;
}

int main() {
    print_state();
    int quit = 0;
    while(!quit) {
        char comm[6];
        int comm_id = -1;
        scanf("%s", comm);
        for (int i = 0; i < COMM_SIZE; i++) {
            int cmpres = strcmp(commands[i], comm);
            if (cmpres == 0) {
                comm_id = i;
                break;
            }
        }
        switch(comm_id) {
            case 0: {
                int arg;
                scanf("%d", &arg);
                movl(arg);
                break;
            }
            case 1: {
                int arg;
                scanf("%d", &arg);
                movr(arg);
                break;
            }
            case 2: {
                accumunaltor = tape[head];
                break;
            }
            case 3: {
                tape[head] = accumunaltor;
                break;
            }
            case 4: {
                accumunaltor += tape[head];
                break;
            }
            case 5: {
                accumunaltor -= tape[head];
                break;
            }
            case 6: {
                int arg;
                scanf("%d", &arg);
                accumunaltor = arg;
                break;
            }
            case 7: {
                quit = 1;
                break;
            }
            case 8: {
                print_state();
                break;
            }
            default: {
                printf("INVALID COMMAND...\n");
                printf("CURRENT MACHINE STATE...\n");
                print_state();
                printf("EXITING\n");
                quit = 1;
                break;
            }
        }
    }
}