#ifndef EISENBITS_LIBDS_COMMON_H
#define EISENBITS_LIBDS_COMMON_H

#include <iostream>
#include <string>
#include <sstream>

namespace eisenbits {
namespace libds {

// Ordinary string type, to be used throughout the library.
typedef std::string       TString;
typedef std::stringstream TStringStream;

typedef unsigned long ulong;
typedef     long long bigint;

// tindex type is used for element indexes in container, container sizes etc.
// This type should be signed!
typedef signed long index_t

/*
extern void debug(const TString& msg);
extern void debug(const char * msg);
extern void debugTrace(const char *fnName, const char *fileName, int line);
extern void debugTrace(const char *fnName, const char *fileName, int line, const TString& msg);
extern void debugTrace(const char *fnName, const char *fileName, int line, const char *msg);
*/

/*
// converts int to a string
extern TString itos(int i);

inline int max(int a, int b) {
    return (a <= b) ? b : a;
}
inline t_index max(t_index a, t_index b) {
    return (a <= b) ? b : a;
}
*/

#ifndef FALSE
#define FALSE (0)
#endif

#ifndef TRUE
#define TRUE  (1)
#endif

#ifndef NULL
#define NULL (0)
#endif

#ifndef CALL_MEMBER_FN
#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))
#endif

};
};

#include "common-macros.h"
#include "utils/MemoryManager.h"

#endif
