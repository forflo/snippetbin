/* Main include for call-tool */

#define LANG_CC 1
#define LANG_CS 2
#define LANG_HS 3
#define LANG_CPP 4

#define MODE_MAKE 10
#define MODE_CALL 11
#define MODE_EDIT 12
#define MODE_SHOW 14

const char *CREATE = "create table bin_bucket (id varchar(32) not null, bin blob not null, primary key(id));";
const char *T_NAME = "bin_bucket";

#define NUM_LANGS 4
char *allowed_langs[4] = {"c", "c#", "haskell", "c++"};
