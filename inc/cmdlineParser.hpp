namespace cmdlineParser {
static int _isCompInexisted = 0;
static int _isCompDuplicated = 0;
static int _isHelpMessage = 0;
int parse(int argc, char* argv[]);
int getInex();
int getDup();
int getHelp();
} // namespace cmdlineParser