enum Token {
        tok_eof = -1,


        // commands
        tok_def = -2,
        tok_extern = -3,

        // primary
        tok_identifier = -4,
        tok_number = -5,
};


static std::string IdentifierStr;
static double NumVal;


/// gettok - Return the next token from standard input
static int gettok() {
        static int LastChar = ' ';

        // Skip any whitespace
        while (isspace(LastChar))
                LastChar = getchar();

        if (isalpha(LastChar)) {
                IdentifierStr = LastChar;


~
