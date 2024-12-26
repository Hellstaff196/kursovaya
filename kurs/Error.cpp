#include "Error.h"

Error::Error(const string &message, const string &func)
    : runtime_error(message + " in function: " + func) {}
