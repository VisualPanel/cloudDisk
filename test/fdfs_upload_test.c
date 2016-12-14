#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "make_log.h"

#define FILE_ID_LEN (256)

#define LOG_TEST_MUDULE "test"
#define LOG_TEST_PROC "fdfs"

int main(int argc, char *argv[])
{
    pid_t pid;
    int pfd[2];
    char file_id[FILE_ID_LEN] = {0};

    if (argc < 2) {
        printf("usage: ./a.out filepath\n");
        exit(1);
    }

    if (pipe(pfd) <0) {
        perror("pipe error");
        exit(1);
    }

    //创建一个子进程
    pid = fork();
    if (pid==0) {
        //child
        //关闭读端
        close(pfd[0]);

        //将标准输出 重定向 到 管道中
        dup2(pfd[1], STDOUT_FILENO);

        //exec --》fdfs_upload_file
        execlp("fdfs_upload_file", "fdfs_upload_file", "./conf/client.conf", argv[1],NULL);

        perror("exec error");
    }
    else {
        //parent
        //关闭写段
        close(pfd[1]);

        wait(NULL);

        //从管道读数据 --- file-id
        read(pfd[0], file_id, FILE_ID_LEN);

        //将file-id 记录到log中

        LOG(LOG_TEST_MUDULE, LOG_TEST_PROC, "file_id=[%s]", file_id);
    }

	return 0;
}
