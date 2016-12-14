#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "redis_op.h"

int main(int argc, char *argv[])
{
    int ret = 0;
    redisContext *conn = NULL;

    conn = rop_connectdb_nopwd("127.0.0.1", "6379");
    if (conn == NULL) {
        printf("connect error\n");
        exit(1);
    }

    
    ret = rop_list_push(conn, "my_list", "gailun");
    if (ret != 0) {
        printf("lpush error\n");
        exit(1);
    }

    printf("lpush succ\n");



    if (conn!=NULL) {
        rop_disconnect(conn);
    }

	return 0;
}
