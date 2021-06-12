/**
 * Inspired and copy-pasted https://gist.github.com/ilovetogetspamed/f64b72a274794600f0ad63b6d6b7c7eb
 */
#ifdef ENABLE_CLI

#include <string.h>
#include <stdlib.h>

#define CLI_CR '\r'
#define CLI_LF '\n'
#define CLI_BS '\b'
#define CLI_NULLCHAR '\0'
#define CLI_SPACE ' '

const char *CLI_delimiters = " \n"; 

#ifndef CLI_BUFFER_LENGTH
  #define CLI_BUFFER_LENGTH 128
#endif

char CLI_BUFFER[CLI_BUFFER_LENGTH + 1];
uint8_t CLI_params = 0;

typedef double (*cliFunction)();

const typedef struct cliCommand_t {
  char *commandName;
  cliFunction func;
  uint8_t params;
} cliCommand;

#endif
