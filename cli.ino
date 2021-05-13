#ifdef ENABLE_CLI

#define CLI_COMMANDS 2

const cliCommand cliCommands[CLI_COMMANDS] = {
  { "help",      cliHelp     , 0},
  { "i2cscan",   cliI2cScan  , 0}
};

bool CLI_get(char * CLI_BUFFER)
{
  static uint8_t CLI_charsRead = 0;
  CLI_params = 0;
  while (cliSerial->available()) {
    char CLI_c = cliSerial->read();
    switch (CLI_c) {
      case CLI_CR:      //likely have full command in buffer now, commands are terminated by CR and/or LS
      case CLI_LF:
        CLI_BUFFER[CLI_charsRead] = CLI_NULLCHAR;       //null terminate our command char array
        if (CLI_charsRead > 0)  {
          CLI_charsRead = 0;                           //charsRead is static, so have to reset
          cliSerial->println(CLI_BUFFER);
          return true;
        }
        break;
      default:
        if (CLI_c == ' ') {
          CLI_params++;
        }
        if (CLI_charsRead < CLI_BUFFER_LENGTH) {
          CLI_BUFFER[CLI_charsRead++] = CLI_c;
        }
        CLI_BUFFER[CLI_charsRead] = CLI_NULLCHAR;     //just in case
        break;
    }
  }
  return false;
}

int CLI_readInt() {
  char * numTextPtr = strtok(NULL, CLI_delimiters);   //K&R string.h  pg. 250
  return atoi(numTextPtr);                            //K&R string.h  pg. 251
}

float CLI_readFloat(){
  char * floatTextPtr = strtok(NULL, CLI_delimiters);
  return atof(floatTextPtr);
}

char * CLI_readWord() {
  char * word = strtok(NULL, CLI_delimiters);         //K&R string.h  pg. 250
  return word;
}

void CLI_doCommand() {
  char * commandName = strtok(CLI_BUFFER, CLI_delimiters);
  for (int i = 0; i < CLI_COMMANDS; i++) {
    if (strcmp(commandName, cliCommands[i].commandName) == 0) {
      if (cliCommands[i].params != CLI_params) {
        cliSerial->println("ERROR: incorrect params number.");
        return;
      }
      cliCommands[i].func();
      return;
    }
  }
}

#endif
