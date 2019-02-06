#include <cmd.h>

 
int main()
{
    char cmd[MAX_COMMAND_LENGTH + 1];
    char* token;
    char* params[MAX_NUMBER_OF_PARAMS + 1];
    char command_type='#';

    while(1) {


        //prompt basıldı.
        printf(">");
	command_type='#';
	memset(cmd, '\0',MAX_COMMAND_LENGTH+1); // cmd dizi null yapıldı.

         //komut alındı.
      	 fgets(cmd, MAX_COMMAND_LENGTH + 1, stdin);
			
        // newline karakteri yerine null karakteri konuldu
        if(cmd[strlen(cmd)-1] == '\n') {
            cmd[strlen(cmd)-1] = '\0';
        }
	
	
	//komut türünün ne olduğu anlaşılması için
	input(cmd);

	//gelen komutlar kesilerek params'a adresleri yollandı
	parseCmd(cmd, params);

	//komutların çalıştırılması.
	action(params);

    }

    return 0;
}

