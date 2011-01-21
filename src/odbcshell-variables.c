/*
 *  ODBC Shell
 *  Copyright (C) 2011 Bindle Binaries <syzdek@bindlebinaries.com>.
 *
 *  @BINDLE_BINARIES_BSD_LICENSE_START@
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Bindle Binaries nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 *  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL BINDLE BINARIES BE LIABLE FOR
 *  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 *  SUCH DAMAGE.
 *
 *  @BINDLE_BINARIES_BSD_LICENSE_END@
 */
/**
 *  @file src/odbcshell-variables.c ODBC Shell global variables
 */
#include "odbcshell-variables.h"

///////////////
//           //
//  Headers  //
//           //
///////////////
#pragma mark Headers

#include "odbcshell.h"

#include <stdio.h>
#include <strings.h>


/////////////////
//             //
//  Variables  //
//             //
/////////////////
#pragma mark -
#pragma mark Variables

/// numeric values for command names
ODBCShellOption odbcshell_cmd_strings[] =
{
   { ODBCSHELL_CMD_CONNECT,     2,  2, "connect",    "connects to a database",        NULL },
   { ODBCSHELL_CMD_DISCONNECT,  1,  1, "disconnect", "disconnects from a database",   NULL },
   { ODBCSHELL_CMD_HELP,        1,  2, "help",       "displays help information",     NULL },
   { ODBCSHELL_CMD_QUIT,        1,  1, "quit",       "exits ODBC Shell",              NULL },
   { ODBCSHELL_CMD_RECONNECT,   1,  1, "reconnect",  "reconnects to a database",      NULL },
   { ODBCSHELL_CMD_SET,         1,  3, "set",        "sets configuration option",     NULL },
   { ODBCSHELL_CMD_UNSET,       2,  2, "unset",      "unsets configuration option",   NULL },
   { ODBCSHELL_CMD_VERSION,     1,  1, "version",    "displays version information",  NULL },
   { -1, -1, -1, NULL, NULL, NULL }
};


/////////////////
//             //
//  Functions  //
//             //
/////////////////
#pragma mark -
#pragma mark Functions

/// looks up option by name
/// @param[in]  opts   array of optins to search
/// @param[in]  name   name to use as lookup key
ODBCShellOption * odbcshell_lookup_opt_by_name(ODBCShellOption * opts,
   const char * name)
{
   unsigned u;
   if (!(opts))
      return(NULL);
   for(u = 0; opts[u].name; u++)
      if (!(strcasecmp(name, opts[u].name)))
         return(&opts[u]);
   return(&opts[u]);
}


/// looks up option by value
/// @param[in]  opts   array of optins to search
/// @param[in]  val    value to use as lookup key
ODBCShellOption * odbcshell_lookup_opt_by_value(ODBCShellOption * opts,
   int val)
{
   unsigned u;
   if (!(opts))
      return(NULL);
   for(u = 0; opts[u].name; u++)
      if (val == opts[u].val)
         return(&opts[u]);
   return(&opts[u]);
}

/* end of source */