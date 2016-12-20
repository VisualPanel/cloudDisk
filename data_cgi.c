#include "fcgi_config.h"

#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>

#include "fcgi_stdio.h"
#include "util_cgi.h"


#define LOG_CGI_MODULE "cgi"
#define LOG_DATA_PROC  "data"

#define JSON_STR ""

int main ()
{


    while (FCGI_Accept() >= 0) {

        printf("Content-type: text/html\r\n"
                "\r\n");

        char buf[4096] = {0};

        //1 获取 前段的参数
        LOG(LOG_CGI_MODULE, LOG_DATA_PROC,  "url: %s", getenv("QUERY_STRING"));
        //  cmd=newFile&fromId=0&count=8&user=
        //进程lrange 查询FILE_ID_LIST 得到fileid 

        //全部文件已经租床称了一个json字符串

        
        //test
        FILE *fp = NULL;
        fp = fopen("json_test_data.json", "r");
        fread(buf, 4096, 1, fp);
        //LOG(LOG_CGI_MODULE, LOG_DATA_PROC,  "%s\n", buf);
        fclose(fp);

        printf("%s\n", buf);

    } /* while */

    return 0;
}
