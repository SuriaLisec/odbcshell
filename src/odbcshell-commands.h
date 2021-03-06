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
 *  @file src/odbcshell-commands.h ODBC Shell commands
 */
#ifndef _ODBCSHELL_SRC_ODBCSHELL_COMMANDS_H
#define _ODBCSHELL_SRC_ODBCSHELL_COMMANDS_H 1

///////////////
//           //
//  Headers  //
//           //
///////////////
#ifdef PMARK
#pragma mark Headers
#endif

#include "odbcshell.h"


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
#ifdef PMARK
#pragma mark -
#pragma mark Prototypes
#endif

// clears the screen
int odbcshell_cmd_clear(void);

// closes output file
int odbcshell_cmd_close(ODBCShell * cnf);

// prints strings to screen
int odbcshell_cmd_connect(ODBCShell * cnf, int argc, char ** argv);

// disconnects from database
int odbcshell_cmd_disconnect(ODBCShell * cnf, int argc, char ** argv);

// prints strings to screen
int odbcshell_cmd_echo(ODBCShell * cnf, int argc, char ** argv);

// executes SQL statement
int odbcshell_cmd_exec(ODBCShell * cnf, char * sql, int skip);

// displays usage information
int odbcshell_cmd_help(ODBCShell * cnf, int argc, char ** argv);

// displays information stating the function is incomplete
int odbcshell_cmd_incomplete(ODBCShell * cnf, int argc, char ** argv);

// opens file for writing results
int odbcshell_cmd_open(ODBCShell * cnf, int argc, char ** argv);

// exits from shell
int odbcshell_cmd_quit(ODBCShell * cnf);

// reconnects to a database
int odbcshell_cmd_reconnect(ODBCShell * cnf, int argc, char ** argv);

// resets internal configuration
int odbcshell_cmd_reset(ODBCShell * cnf);

// sets internal value of configuration parameter
int odbcshell_cmd_set(ODBCShell * cnf, int argc, char ** argv);

// sets the value of an environment variable
int odbcshell_cmd_setenv(ODBCShell * cnf, int argc, char ** argv);

// shows database information
int odbcshell_cmd_show(ODBCShell * cnf, const char * data);

// imports script into session
int odbcshell_cmd_source(ODBCShell * cnf, const char * file);

// unsets internal value of configuration parameter
int odbcshell_cmd_unset(ODBCShell * cnf, char ** argv);

// sets the value of an environment variable
int odbcshell_cmd_unsetenv(int argc, char ** argv);

// switches active database connection
int odbcshell_cmd_use(ODBCShell * cnf, int argc, char ** argv);

// displays version information
int odbcshell_cmd_version(ODBCShell * cnf);


#endif
/* end of header */
