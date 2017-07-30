#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <fcntl.h>

typedef struct instrucao {
	int op; //flag para o opção do switch case no prompt_line
	int qtd_args; //quntidade de argumentos do comando;
	char** tab_argumentos; //tabela de argumentos recebidos
} Instrucao;

char ** aloca(int linhas, int col, char **str) {
	str = (char **)malloc(linhas*sizeof(char *));
	int i;
	for (i = 0; i<linhas; i++)
		*(str + i) = (char *)malloc(col*sizeof(char));

	return str;
}

void libera(int linhas, char **str, Instrucao* comando) {
	int i;
	for (i = 0; i<linhas; i++)
		free(*(str + i));
	free(str);
	free(comando);
}

int traduzir(char* cmd) {
	if(strcmp(cmd,"sair") == 0) //sair retorna 0
		return 0;
	else if(strcmp("date",cmd) == 0) // date retorna 1
		return 1;
	else if(strcmp(cmd,"fork") == 0) // fork retorna 2
		return 2;
	else if(strcmp(cmd,"ls") == 0) // ls retorna 3
		return 3;
	else if(strcmp(cmd,"pwd") == 0) // pwd retorna 4
		return 4;
	else if(strcmp(cmd,"cat") == 0) // cat(execl) retorna 5
		return 5;
	else if(strcmp(cmd,"mkdir") == 0) // mkdir retorna 6
		return 6;
	else if(strcmp(cmd,"rm") == 0) //rm retorna 7
		return 7;
	else 
		return -1;
}

Instrucao* tratamento(char* cmd) {
	Instrucao* comando = (Instrucao*) malloc(sizeof(Instrucao));
	int cont,i,j,aux;
	cont = 1;
	/*contagem dos argumentos*/
	for(i=0;cmd[i]!='\0';i++) {
		if(cmd[i] == ' ')
			cont++;
	}
	comando->qtd_args = cont;
	comando->tab_argumentos = aloca(cont,20,comando->tab_argumentos);
	i = aux = j = 0;
	comando->tab_argumentos[1][aux] = cmd[i];
	for(i=0;cmd[i]!='\0';i++) {
		if(cmd[i] == ' '){
			comando->tab_argumentos[j][aux] = '\0';
			//printf("%s\n", comando->tab_argumentos[j]);
			j++;
			aux = -1;
		}
		else
			comando->tab_argumentos[j][aux] = cmd[i];
		aux++;

	}
	comando->tab_argumentos[j][aux] = '\0';
	comando->op = traduzir(comando->tab_argumentos[0]);

	return comando;
}

void data() {
	pid_t filho = fork();
	if (filho < 0){ //erro ao criar novo processo
		printf("Nao foi possivel criar outro processo!\n");
		perror("fork()error");
	}
	if(filho > 0) { //Execução do processo pai
		wait(NULL);//Espera o filho desse processo retorna para ele(join)
	}
	else { // Execução do processo filho
		execl("/bin/date","date",NULL);
	}
}

void cria_processo() {
	pid_t filho = fork();
	if (filho < 0){ //erro ao criar novo processo
		printf("Nao foi possivel criar outro processo!\n");
		perror("fork()error");
	}
	if(filho > 0) { //Execução do processo pai
		printf("Execucao atual do processo pai de PID %d e o filho desse processo eh de PID %d.\n",getpid(),filho);
		wait(NULL);//Espera o filho desse processo retorna para ele(join)
	}
	else { // Execução do processo filho
		printf("Execucao atual do processo filho de PID %d e o pai desse processo eh  de PID%d.\n",getpid(),getppid());
	}
}

void ls() {
	pid_t filho = fork();
	if (filho < 0){ //erro ao criar novo processo
		printf("Nao foi possivel criar outro processo!\n");
		perror("fork()error");
	}
	if(filho > 0) { //Execução do processo pai
		wait(NULL);//Espera o filho desse processo retorna para ele(join)
	}
	else { // Execução do processo filho
		struct dirent **namelist;
	    int n;
	    char* dir = get_current_dir_name();
	    struct stat sb;
	    stat(dir, &sb);
	    n = scandirat(sb.st_ino, dir, &namelist, NULL, alphasort);
	    //perror("scandirat");
	    while (n--) {
	        printf("%s\n", namelist[n]->d_name);
	        free(namelist[n]);
	    }
	}	
}

void pwd() {
	pid_t filho = fork();
	if (filho < 0){ //erro ao criar novo processo
		printf("Nao foi possivel criar outro processo!\n");
		perror("fork()error");
	}
	if(filho > 0) { //Execução do processo pai
		wait(NULL);//Espera o filho desse processo retorna para ele(join)
	}
	else { // Execução do processo filho
		char* dir = get_current_dir_name();
		printf("%s\n", dir);
		free(dir);
	}
	
}

void cat(char* arq) {
	pid_t filho = fork();
	if (filho < 0){ //erro ao criar novo processo
		printf("Nao foi possivel criar outro processo!\n");
		perror("fork()error");
	}
	if(filho > 0) { //Execução do processo pai
		wait(NULL);//Espera o filho desse processo retorna para ele(join)
	}
	else { // Execução do processo filho
		execl("/bin/cat","cat",arq,NULL);
	}

}

void mkdir(char* nome) {
	pid_t filho = fork();
	if (filho < 0){ //erro ao criar novo processo
		printf("Nao foi possivel criar outro processo!\n");
		perror("fork()error");
	}
	if(filho > 0) { //Execução do processo pai
		wait(NULL);//Espera o filho desse processo retorna para ele(join)
	}
	else {
		struct dirent **namelist;
	    int n;
	    struct stat sb;
	    char* dir = get_current_dir_name();
	    stat(dir, &sb);
	    printf("%d\n", sb.st_ino);
	    strcat(dir,"/");
	    strcat(dir,nome);
	    printf("%d\n",mkdirat(sb.st_ino, dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH));
	    //perror("mkdirat");
	    free(dir);
	}
}

void rm(char* str) {

}

void prompt_line() {
		char cmd[100];
		while (1) {
			setbuf(stdin,NULL);
			printf("\ncomando: ");
			scanf("%[^\n]s",cmd);
			Instrucao* comando;
			comando = tratamento(cmd);
			//printf("%d\n",comando->op );
			switch(comando->op) {
				case 0:
					libera(comando->qtd_args,comando->tab_argumentos,comando);
					exit(1);
					break;
				case 1 :
					/*
					printf("qtd_args %d\n",comando->qtd_args);
					int i;
					for(i=0;i<comando->qtd_args;i++)
						printf("tab_argumentos %s\n",comando->tab_argumentos[i]);*/
					data();
					libera(comando->qtd_args,comando->tab_argumentos,comando);
					break;
				case 2:
					cria_processo();
					libera(comando->qtd_args,comando->tab_argumentos,comando);
					break;
				case 3:
					ls();
					libera(comando->qtd_args,comando->tab_argumentos,comando);
					break;
				case 4:
					pwd();
					libera(comando->qtd_args,comando->tab_argumentos,comando);
					break;
				case 5:
					cat(comando->tab_argumentos[1]);
					libera(comando->qtd_args,comando->tab_argumentos,comando);
					break;
				case 6:
					mkdir(comando->tab_argumentos[1]);
					libera(comando->qtd_args,comando->tab_argumentos,comando);
					break;
				default:
					printf("comando nao suportado\n");
					libera(comando->qtd_args,comando->tab_argumentos,comando);
					break;
			}
		}
}

int main() {
	prompt_line();
	return 0;
};