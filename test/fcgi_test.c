/*
 * echo.c --
 *
 *	Produce a page containing all FastCGI inputs
 *
 *
 * Copyright (c) 1996 Open Market, Inc.
 *
 * See the file "LICENSE.TERMS" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 */
#ifndef lint
static const char rcsid[] = "$Id: echo.c,v 1.5 1999/07/28 00:29:37 roberts Exp $";
#endif /* not lint */

#include "fcgi_config.h"

#include <stdlib.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef _WIN32
#include <process.h>
#else
extern char **environ;
#endif

#include "fcgi_stdio.h"


static void PrintEnv(char *label, char **envp)
{
    printf("%s:<br>\n<pre>\n", label);
    for ( ; *envp != NULL; envp++) {
        printf("%s\n", *envp);
    }
    printf("</pre><p>\n");
}

int main ()
{
    char **initialEnv = environ;//当前的环境变量 备份了到initialEnv
    int count = 0;

    while (FCGI_Accept() >= 0) {
        //数据---post数据 http://192.168.23.250:/demo?cmd=123&name=zhang3  [post数据]
        char *contentLength = getenv("CONTENT_LENGTH");
        //表示post数据的长度
        int len;

        printf("Content-type: text/html\r\n"
                "\r\n"
                "<title>FastCGI echo</title>"
                "<h1>FastCGI echo</h1>\n"
                "Request number %d,  Process ID: %d<p>\n", ++count, getpid());

        if (contentLength != NULL) {
            len = strtol(contentLength, NULL, 10);
        }
        else {
            len = 0;
        }

        if (len <= 0) {
            printf("No data from standard input.<p>\n");
        }
        else {
            //回显示 用户的post数据
            int i, ch;

            printf("Standard input:<br>\n<pre>\n");
            for (i = 0; i < len; i++) {
                //就相当于从浏览器客户端cfd, 读一个字节到程序中
                if ((ch = getchar()) < 0) {
                    printf("Error: Not enough bytes received on standard input<p>\n");
                    break;
                }
                putchar(ch);
            }
            printf("\n</pre><p>\n");
        }

        PrintEnv("Request environment", environ);//environ 应该是当前cgi程序的环境变量
        PrintEnv("Initial environment", initialEnv);//initialEnv应该是 之前程序的默认环境变量
    } /* while */

    return 0;
}
