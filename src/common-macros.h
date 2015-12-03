/**
 * This file is part of Eisenbits Data Structures Library (libebds++).
 *
 * Copyright (C) 2009 Stanislaw T. Findeisen <sf181257@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Changes history:
 *
 * 2009-10-17 (STF) Initial version.
 */

#ifndef EISENBITS_LIBDS_COMMON_MACROS_H
#define EISENBITS_LIBDS_COMMON_MACROS_H

#include <iostream>
#include <string>
#include <sstream>

namespace eisenbits {
namespace libds {

#define EBDS_STRING(e) (((std::stringstream&)(((std::stringstream()).flush())<<e)).str())
#define EBDS_FILE_LOCATION      "["<<__FILE__<<":"<<__LINE__<<" "<<__FUNCTION__<<"] "

#define EBDS_ERROR(e)                     \
{                                         \
    std::cerr << "[ebds:error]    " << EBDS_FILE_LOCATION << e << std::endl;    \
    std::cerr.flush();                    \
}
#define EBDS_WARNING(e)                   \
{                                         \
    std::cerr << "[ebds:warning]  " << EBDS_FILE_LOCATION << e << std::endl;    \
    std::cerr.flush();                    \
}
#define EBDS_INFO(e)                      \
{                                         \
    std::cerr << "[ebds:info]     " << EBDS_FILE_LOCATION << e << std::endl;    \
    std::cerr.flush();                    \
}
#define EBDS_DEBUG(e)                     \
{                                         \
    std::cerr << "[ebds:debug]   " << EBDS_FILE_LOCATION << e << std::endl;    \
    std::cerr.flush();                    \
}

#define EBDS_TRACE                        \
{                                         \
    std::cerr << "[ebds:trace]   " << EBDS_FILE_LOCATION << std::endl; \
    std::cerr.flush();                    \
}

#define EBDS_TRACE_MSG(e)                 \
{                                         \
    std::cerr << "[ebds:trace]   " << EBDS_FILE_LOCATION << e << std::endl; \
    std::cerr.flush();                    \
}

#define EBDS_NEW(p,e)                     \
{                                         \
    MemoryManager::getInstance().registerNew(__FILE__, __LINE__); \
    p = new e;                            \
}

#define EBDS_NEW_ARRAY(p,e,sz)            \
{                                         \
    MemoryManager::getInstance().registerNewTab(__FILE__, __LINE__); \
    p = new e[sz];                        \
}

#define EBDS_DELETE(p)                    \
{                                         \
    MemoryManager::getInstance().registerDelete(__FILE__, __LINE__); \
    delete p;                             \
    p = NULL;                             \
}

#define EBDS_DELETE_VALUE(p)              \
{                                         \
    MemoryManager::getInstance().registerDelete(__FILE__, __LINE__); \
    delete p;                             \
}

#define EBDS_DELETE_ARRAY(p)              \
{                                         \
    MemoryManager::getInstance().registerDeleteTab(__FILE__, __LINE__); \
    delete [] p;                          \
    p = NULL;                             \
}

#define EBDS_THROW(e)                     \
{                                         \
    throw e;                              \
}

#define EBDS_THROW_ARGS(t,args)           \
{                                         \
    t e(args);                            \
    e.setFileName(__FILE__);              \
    e.setFunctionName(__FUNCTION__);      \
    e.setLineNumber(__LINE__);            \
    throw e;                              \
}

#define EBDS_THROW_MSG(t,s)               \
{                                         \
    TStringStream ss;                     \
    ss << s;                              \
    EBDS_THROW_ARGS(t,ss.str());          \
}

#define EBDS_MEMCPY(dest,src,sz)          \
{                                         \
    memcpy(dest,src,sz);                  \
}

};
};

#endif
