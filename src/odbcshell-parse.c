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
 *  @file src/odbcshell-parse.c ODBC Shell command parser
 */
#include "odbcshell-parse.h"

///////////////
//           //
//  Headers  //
//           //
///////////////
#pragma mark Headers

#include "odbcshell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "odbcshell-commands.h"
#include "odbcshell-variables.h"


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
#pragma mark -
#pragma mark Prototypes


/////////////////
//             //
//  Variables  //
//             //
/////////////////
#pragma mark -
#pragma mark Variables


/////////////////
//             //
//  Functions  //
//             //
/////////////////
#pragma mark -
#pragma mark Functions

/// interprets the string buffer
int odbcshell_interpret_buffer(ODBCShell * cnf, char * buff, size_t len,
   size_t * offsetp)
{
   int           code;
   int           argc;
   char       ** argv;
   size_t        pos;
   size_t        offset;

   argc     = 0;
   argv     = NULL;
   len      = strlen(buff);
   pos      = 0L;
   *offsetp = 0L;

   while(pos < len)
   {
      if (odbcshell_parse_line(&buff[pos], &argc, &argv, &offset))
         return(-1);
      if (!(offset))
         return(2);
      if (!(argc))
         return(0);

      *offsetp += offset;

      switch((code = odbcshell_interpret_line(cnf, argc, argv)))
      {
         case 1:
            return(code);
         case -1:
            if ( (!(code)) || (!(cnf->continues)) )
               return(code);
         default:
            break;
      };

      pos += offset+1;
   };
   return(0);
}

/// interprets the arguments from a command line
/// @param[in]  cnf      pointer to configuration struct
/// @param[out] argcp
/// @param[out] argvp
int odbcshell_interpret_line(ODBCShell * cnf, int argc, char ** argv)
{
   int               code;
   ODBCShellOption * cmd;

   if (!(argc))
      return(0);

   if (!(cmd = odbcshell_lookup_opt_by_name(odbcshell_cmd_strings, argv[0])))
   {
      printf("%s: %s: unknown command\n", PROGRAM_NAME, argv[0]);
      return(0);
   };

   if (cmd->min_arg > argc)
   {
      printf("%s: missing required arguments.\n", argv[0]);
      printf("try `help %s;' for more information.\n", argv[0]);
      return(0);
   };
   if ( (cmd->max_arg < argc) && (cmd->max_arg != -1) )
   {
      printf("%s: unknown arguments\n", argv[0]);
      printf("try `help %s;' for more information.\n", argv[0]);
      return(0);
   };

   switch(cmd->val)
   {
      case ODBCSHELL_CMD_ALIAS:      code = odbcshell_cmd_incomplete(cnf, argc, argv); break;
      case ODBCSHELL_CMD_CLEAR:      code = odbcshell_cmd_clear(); break;
      case ODBCSHELL_CMD_CONNECT:    code = odbcshell_cmd_incomplete(cnf, argc, argv); break;
      case ODBCSHELL_CMD_DISCONNECT: code = odbcshell_cmd_incomplete(cnf, argc, argv); break;
      case ODBCSHELL_CMD_ECHO:       code = odbcshell_cmd_echo(cnf, argc, argv); break;
      case ODBCSHELL_CMD_LOADCONF:   code = odbcshell_cmd_incomplete(cnf, argc, argv); break;
      case ODBCSHELL_CMD_HELP:       code = odbcshell_cmd_help(cnf, argc, argv); break;
      case ODBCSHELL_CMD_QUIT:       code = odbcshell_cmd_quit(cnf); break;
      case ODBCSHELL_CMD_RECONNECT:  code = odbcshell_cmd_incomplete(cnf, argc, argv); break;
      case ODBCSHELL_CMD_RESETCONF:  code = odbcshell_cmd_resetconf(cnf); break;
      case ODBCSHELL_CMD_SAVECONF:   code = odbcshell_cmd_incomplete(cnf, argc, argv); break;
      case ODBCSHELL_CMD_SET:        code = odbcshell_cmd_set(cnf, argc, argv); break;
      case ODBCSHELL_CMD_SILENT:     code = odbcshell_cmd_incomplete(cnf, argc, argv); break;
      case ODBCSHELL_CMD_UNALIAS:    code = odbcshell_cmd_incomplete(cnf, argc, argv); break;
      case ODBCSHELL_CMD_UNSET:      code = odbcshell_cmd_unset(cnf, argv); break;
      case ODBCSHELL_CMD_VERBOSE:    code = odbcshell_cmd_incomplete(cnf, argc, argv); break;
      case ODBCSHELL_CMD_VERSION:    code = odbcshell_cmd_version(cnf); break;
      default:                       code = odbcshell_cmd_incomplete(cnf, argc, argv); break;
   };

   return(code);
}


/// splits a line into multiple arguments
/// @param[in]  line
/// @param[out] argcp
/// @param[out] argvp
/// @param[out] eolp
int odbcshell_parse_line(char * line, int * argcp, char *** argvp,
   size_t * eolp)
{
   int       i;
   char    * arg;
   void    * ptr;
   size_t    len;    // line length
   size_t    pos;    // position within line
   size_t    start;  // start of argument within line
   size_t    arglen; // length of argument

   if ( (!(line)) || (!(argcp)) || (!(argvp)) || (!(eolp)) )
   {
      fprintf(stderr, "%s: internal error\n", PROGRAM_NAME);
      return(-1);
   };

   // frees old argc/argv data
   for(i = 0; i < *argcp; i++)
      free((*argvp)[i]);
   *argcp = 0;
   *eolp  = 0;

   if (!(len = strlen(line)))
      return(0);

   for(pos = 0; pos < len+1; pos++)
   {
      arg = NULL;
      switch(line[pos])
      {
         // exit if end of command is found
         case '\n':
         case '\0':
         case ';':
            *eolp = pos;
            return(0);

         case '\\':
            line[pos] = ' ';
            if ((line[pos+1] != '\n') && (line[pos+1] != '\0'))
               continue;
            if (line[pos+1] == '\n')
               line[pos+1] = ' ';
            if (line[pos+1] == '\0')
               return(0);
            break;

         // skip white space between arguments
         case ' ':
         case '\t':
            break;

         case '\r':
            line[pos] = ' ';
            break;

         // skip comments
         case '#':
            while((line[pos] != '\n') && (line[pos] != '\r') && (pos < len))
               pos++;
            if (pos >= len)
            {
               *eolp = pos;
               return(0);
            };
            break;

         // processes arguments contained within single quotes
         case '\'':
            start = pos + 1;
            pos += 2;
            while((line[pos] != '\'') && (pos < len))
               pos++;
            if (pos >= len)
               return(0);
            arglen = pos - start;
            if (!(arg = malloc(arglen)))
            {
               fprintf(stderr, "%s: out of virtual memory\n", PROGRAM_NAME);
               return(-1);
            };
            memset(arg, 0, arglen);
            strncat(arg, &line[start], arglen);
            break;

         // processes arguments contained within double quotes
         case '"':
            start = pos + 1;
            pos += 2;
            while((line[pos] != '"') && (pos < len))
               pos++;
            if (pos >= len)
               return(0);
            arglen = pos - start;
            if (!(arg = malloc(arglen)))
            {
               fprintf(stderr, "%s: out of virtual memory\n", PROGRAM_NAME);
               return(-1);
            };
            memset(arg, 0, arglen);
            strncat(arg, &line[start], arglen);
            break;

         // processes unquoted arguments
         default:
            start = pos;
            while ( ((pos+1) < len) &&
                    (line[pos+1] != ';') &&
                    (line[pos+1] != '#') &&
                    (line[pos+1] != ' ') &&
                    (line[pos+1] != '\t') &&
                    (line[pos+1] != '\\') &&
                    (line[pos+1] != '\n') &&
                    (line[pos+1] != '\r') )
               pos++;
            arglen = 1 + pos - start;
            if (!(arg = malloc(arglen)))
            {
               fprintf(stderr, "%s: out of virtual memory\n", PROGRAM_NAME);
               return(-1);
            };
            memset(arg, 0, arglen);
            strncat(arg, &line[start], arglen);
            break;
      };

      // if an argument is not defined, skip to next character in string.
      if (!(arg))
         continue;

      // stores argument in array
      if (!(ptr = realloc(*argvp, sizeof(char *) * ((*argcp)+1))))
      {
         fprintf(stderr, "%s: out of virtual memory\n", PROGRAM_NAME);
         return(-1);
      };
      *argvp = ptr;
      (*argvp)[(*argcp)] = arg;
      (*argcp)++;
   };

   return(0);
}


/* end of source */
