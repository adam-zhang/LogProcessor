#include "Daemon.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

Daemon::Daemon()
{
}

Daemon::~Daemon()
{
}

void Daemon::create(void)
{
	pid_t pid;
	pid = fork();
	if( pid == -1)
	{
		printf("fork error!\n");
		exit(EXIT_FAILURE);
	}
	else if(pid > 0)
	{ 
		//父进程退出，子进程由init进程接管
		exit(EXIT_SUCCESS);
	}
	{
		//子进程
		if(setsid() == -1)
		{  //创建新的会话,脱离终端的控制
			printf("setsid error!\n");
		}
		//子进程继承了父进程的工作目录，这里也要重置
		//chdir("/home/chenlinzhong/trunk/demo/linenoise"); 
		int i;
		for( i = 0; i < 3; ++i)
		{
			close(i); //关闭 stdin stdout stderror
		}
		umask(0);     //子进程继承了父进程文件掩码,需要重置
	}
	return;
} 
