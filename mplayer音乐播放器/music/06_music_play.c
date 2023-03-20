/*
	按钮被按下的时候会产生一个pressed的信号
*/
#include <gtk/gtk.h>
//包含头文件
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

void do_pressed()
{
	printf("爽外外\n");
}
void do_cliked()
{
	printf("惨兮兮\n");
}
//使用gtk时需要删除const
int main(int argc, char *argv[])
{
	//开进程
	//创建进程号
	pid_t pid;

	//开进程
	pid = fork();

	//父进程
	if (pid > 0)
	{
		//第一步：gtk环境初始化
		gtk_init(&argc,&argv);

		//第二步：创建一个新的窗口
		GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		//控件类型  变量		创建新的窗口     自带标题栏
		gtk_widget_set_size_request(window,800,480);

		//第三步：创建固定布局
		GtkWidget* fixed = gtk_fixed_new();

		//第四步：将布局放入到窗口中
		gtk_container_add(GTK_CONTAINER(window),fixed);

		//第五步：添加新控件
		GtkWidget* btn = gtk_button_new_with_label("按钮");
		gtk_widget_set_size_request(btn,50,50);
		GtkWidget* btn1 = gtk_button_new_with_label("按钮1");
		gtk_widget_set_size_request(btn1,50,50);

		//第六步：将控件包含进布局
		gtk_fixed_put(GTK_FIXED(fixed),btn,375,410);
		gtk_fixed_put(GTK_FIXED(fixed),btn1,305,410);

		//第七步：显示窗口
		gtk_widget_show_all(window);

		//第八步：信号连接函数
		g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
		g_signal_connect(btn,"pressed",G_CALLBACK(do_pressed),NULL);
		g_signal_connect(btn1,"pressed",G_CALLBACK(do_cliked),NULL);

		//第九步：主事件循环
		gtk_main();
	}
	//子进程
	else if (pid == 0)
	{
		execlp("mplayer","mplayer","-slave","-idle","-quiet","coffe.mp3",NULL);
		exit(0);
	}
	else
	{
		perror("pid");
	}




	return 0;
}

//编译
//gcc  01_first_window.c  -o demo `pkg-config --cflags --libs gtk+-2.0`
