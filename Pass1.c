#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char label[10], opcode[10], operand[10], code[10], mnemonic[10], symb[10], addr[10];
FILE *f1, *f2, *f3, *f4, *f5;

void xit() {
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    fclose(f5);
    exit(1);
}

void pass1() {
    int loc_ctr = 0, start = 0, length, found = 0, err = 0;

    fscanf(f1, "%s\t%s\t%s", label, opcode, operand);

    if (strcasecmp(opcode, "start") == 0) {
        start = (int)strtol(operand, NULL, 16);
        fprintf(f3, "\t%s\t%s\t%s\n", label, opcode, operand);
        loc_ctr = start;
        fscanf(f1, "%s\t%s\t%s", label, opcode, operand);
    }

    while (strcasecmp(opcode, "end") != 0) {
        fprintf(f3, "%X\t%s\t%s\t%s\n", loc_ctr, label, opcode, operand);

        if (strcasecmp(label, "**") != 0) {
            fseek(f4, 0, SEEK_SET);
            err = 0;
            while (fscanf(f4, "%s\t%s", symb, addr) != EOF) {
                if (strcasecmp(symb, label) == 0) {
                    err = 1;
                    break;
                }
            }
            fseek(f4, 0, SEEK_END);
            if (!err) {
                fprintf(f4, "%s\t%X\n", label, loc_ctr);
            } else {
                printf("ERROR: Duplicate symbol\n");
                fprintf(f4, "error: duplicate symbol\n");
            }
        }

        fscanf(f2, "%s\t%s", code, mnemonic);
        found = 0;

        while (strcasecmp(code, "end") != 0) {
            if (strcasecmp(opcode, code) == 0) {
                loc_ctr += 3;
                found = 1;
                break;
            }
            fscanf(f2, "%s\t%s", code, mnemonic);
        }

        if (!found) {
            if (strcasecmp(opcode, "RESW") == 0) {
                loc_ctr += 3 * atoi(operand);
            } else if (strcasecmp(opcode, "RESB") == 0) {
                loc_ctr += atoi(operand);
            } else if (strcasecmp(opcode, "BYTE") == 0) {
                loc_ctr += (strlen(operand) - 3);
            }else if(strcasecmp(opcode,"WORD")==0) {
                loc_ctr +=3;
            }
           
        }

        fscanf(f1, "%s\t%s\t%s", label, opcode, operand);
    }

    fprintf(f3, "\t%s\t%s\t%s\n", label, opcode, operand);
    length = loc_ctr - start;
    printf("Length of program = %d\n", length);
    fprintf(f5, "%d\n", length);
}

int main() {
    FILE *temp;

    f1 = fopen("input.txt", "r");
    f2 = fopen("optab.txt", "r");
    f3 = fopen("intermediate.txt", "w");

    temp = fopen("symtab.txt", "w");
    fclose(temp);

    f4 = fopen("symtab.txt", "rb+");
    f5 = fopen("length.txt", "w");

    pass1();

    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    fclose(f5);

    return 0;
}
