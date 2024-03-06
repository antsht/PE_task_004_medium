#ifndef ERRORS_H
#define ERRORS_H

typedef enum { OK, IO_ERROR, NO_DATA, INVALID_DATA, INVALID_INPUT } ErrorCode;

void try(ErrorCode error);
void puckxit();
void print_no_data_message();
#endif