CC=gcc
CPPFLAGS= -I./include   -I/usr/local/include/hiredis/
CFLAGS=-Wall 
LIBS= -lfcgi

#找到当前目录下所有的.c文件
src = $(wildcard *.c)
#将当前目录下所有的.c  转换成.o给obj
obj = $(patsubst %.c, %.o, $(src))

echo = echo
fdfs_upload_test=fdfs_test
data_cgi = data

target=$(fdfs_upload_test) $(echo) $(data_cgi)

ALL:$(target)

#利用规则生成所有的.o文件
%.o:%.c
	$(CC) -c $< -o $@ $(CPPFLAGS) $(CFLAGS) 

#echo程序
$(echo):echo.o make_log.o
	$(CC) $^ -o $@ $(LIBS)

#fdfs_upload_test程序
$(fdfs_upload_test):./test/fdfs_upload_test.o make_log.o 
	$(CC) $^ -o $@ $(LIBS)

#data程序
$(data_cgi):data_cgi.o make_log.o 
	$(CC) $^ -o $@ $(LIBS)

#将clean,ALL和distclean设置为伪目标
.PHONY: clean ALL distclean
#clean指令
clean:
	-rm -rf $(obj) $(target) ./test/*.o

distclean:
	-rm -rf $(obj) $(target) ./test/*.o
