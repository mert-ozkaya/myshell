#include <cmd.h>
char command_type='#';


void input(char* cmd){
		command_type='#';
		for(int i=0;i<strlen(cmd)+1;i++) // burada hangi komut geldiğini anlayıp komut yerine boşluk yerleştiriciyoruz. komut tipini global değişkene aktarıyoruz.
		{
			if (cmd[i]=='>') // çıkış yönlendirme gelmişse
			{
				cmd[i]=' ';
				command_type='>';
			}
			else if(cmd[i]=='<') // giris yönlendirme gelmişse
			{
				cmd[i]=' ';
				command_type='<';
			}
			else if(cmd[i]=='&' && i==strlen(cmd)-1) // arkapalan komudu gelmişse
			{
				cmd[i]='\0';
				command_type='&';
			}

		}
		
		
		if(command_type=='#') // tekli komut gelmiş ise komut t yapıyoruz
			command_type='t';
	
		int sayac=0,j=0;
		for(int i=0; i<strlen(cmd); i++) // komutta fazla boşluklar bırakılmışsa hatayı önlemek için boşlukları bire indiriyoruz
		{
			if(cmd[i]==' ' && cmd[i+1]!=' ')
			{
				continue;	
			}else if(cmd[i]==' ' && cmd[i+1]==' '){
				for(j=i;j<strlen(cmd); j++)
				{
					cmd[j+1]=cmd[j+2];		
				}
				cmd[j]='\0';
				i--;
			}
	
		}

	
}

// cmd ile gelen komudun parçalanması
void parseCmd(char* cmd, char** params)
{       
    for(int i = 0; i < MAX_NUMBER_OF_PARAMS; i++) 
    {
        params[i] = strsep(&cmd, " ");
        if(params[i] == NULL) break;
    }

	
}

// komutlara göre ayrıştırılıp çoklu komutların çalıştığı fonksiyon
void action(char** params){
	
	// quit komutu gelmişse 	
        if(strcmp(params[0], "quit") == 0){
		int status;
		while (!waitpid(-1,&status,WNOHANG)){}
		exit(0);
	}



	// komut < Giris yonlendir
	if(command_type=='<'){

		if (!(access (params[1],F_OK) != -1))
		{	
			printf("MAS_Shell: %s adinda bir dosya bulunamadi\n",params[1]);
			return;
		}
		// Fork process
		    int pid = fork();
		    // Error
		    if (pid < 0) {
			char* error = strerror(errno);
			printf("fork: %s\n", error);
		    }

		    // Child process
		    else if (pid == 0) {
			int in = open(params[1],O_RDONLY);
			dup2(in,STDIN_FILENO);
			close(in);
			// Execute command
			execvp(params[0], params);  
		    }
	

		    // Parent process
		   // child process bitmesi bekleniyor
		    else {
			int childStatus;
			waitpid(pid,NULL,0); 
		
		    }
		
	}


	// komut > Cikis yonlendir
	if(command_type=='>'){

		    pid_t pid = fork();

		    // Error
		    if (pid < 0) {
			char* error = strerror(errno);
			printf("fork: %s\n", error);
		    }

		    // Child process
		    else if (pid == 0) {

			int out = open(params[2], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);	
			dup2(out,1);
			close(out);
			

			// Execute command
			execvp(params[0], params);  

			// Error occurred
			char* error = strerror(errno);
			printf("MAS_Shell: %s: %s\n", params[0], error);
		    }
	

		    // Parent process
		   // child process bitmesi bekleniyor
			
			waitpid(pid,NULL,0);
		
	
	}
		

	 if(command_type=='t' || command_type=='&') {executeCmd(params);} // tekli veya arkaplanda çalışacak komut gelmişse executeCmd fonksiyonuna yönlendirme
		
}
	


int executeCmd(char** params)
{
		if(command_type=='t'){
		    
		    // Fork process
		    pid_t pid = fork();

		    // Error
		    if (pid < 0) {
			char* error = strerror(errno);
			printf("fork: %s\n", error);
		    }

		    // Child process
		    else if (pid == 0) {
			// Execute command
			execvp(params[0], params);  
		    }
	

		    // Parent process
		    else {
			waitpid(pid,NULL,0);
		    }
		}
		if(command_type=='&'){ // arkaplan komudu gelmişse background fonksiyonuna yönlendir
			background(params);
		
		}

}

int background(char **params)
{
	pid_t pid;
	int status;

	struct sigaction mysig;
	mysig.sa_handler = sigChild;
	sigemptyset(&mysig.sa_mask);
	mysig.sa_flags = SA_NOCLDSTOP;
	if (sigaction(SIGCHLD,&mysig,NULL)<0)
	{
		fprintf(stderr,"sigaction failed\n");
		return 1;
	}

	pid=fork();
	if (pid == 0)
	{
		if (execvp(params[0],params) == -1)
		{
			printf("Command not found");
			kill(getpid(),SIGTERM);
		}
	
	}
	else if (pid < 0)
	{
		perror("MAS_Sheel");
	}
	else
	{
		printf("Process PID:%d degeriyle olusturuldu.\n",pid);
	}
	return 1; 
}


void sigChild(int signalNo) 
{
    int status, childDeger,childPid;
	childPid = waitpid(-1, &status, WNOHANG);
	if (childPid > 0)//Arkaplanda çalışmayan processler için bu kontrol yapılmıştır.
	{
	    if (WIFEXITED(status))	//Child normal bir şekilde sonlandı mı?
	    {
	        childDeger = WEXITSTATUS(status); // Çocuğun durumu alındı.
	        printf("[%d] retval : %d \n",childPid, childDeger); //Çocuğun pid'i ve durumu ekrana yazdırılır.
	    }
	}
}
