class Command {
  private:
    char command;

  public:
    char validCommands[6] = {'a', 'r', 'g', 'b', 'c'};
  
    Command(char c) {
      this->command = c;
    }

    Command() {}

    bool isValid() {
      for (int i = 0; i < sizeof(validCommands); i++) {
        if (command == validCommands[i]) {
          return true;
        }
      }
      return false;
    }

    char value() {
      return command;
    }
};
