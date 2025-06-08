#include <unistd.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <sys/wait.h>


FILE *stderr_fp;

int compare2outputs(FILE *fp_expected, FILE *fp_returned){
	
    char *line_expected = NULL;    
    size_t len_expected = 0;
    ssize_t read_expected;
    
    char *line_returned = NULL;    
    size_t len_returned = 0;
    ssize_t read_returned;
    
    int lineno = 1;
    
    fprintf(stderr_fp, "\n");    
	
    while ((read_expected = getline(&line_expected, &len_expected, fp_expected)) != -1) {
    
        fprintf(stderr_fp, "\n[EXPECTED] (len %zu ) %s", read_expected, line_expected);
        
        read_returned = getline(&line_returned, &len_returned, fp_returned);
        
        if ( read_returned == -1 ){
        	fprintf(stdout, "\n[ERROR] Returned file exited before Expected ended!");
        	
		    free( line_expected );        
        	return -1;
        }
        
        fprintf(stderr_fp, "[returned] (len %zu ) %s", read_returned, line_returned);
        
        if ( ! strcmp( line_expected, line_returned ) ) {
        
        	// fprintf(stderr_fp, "ok");
        	
        } else {

        	fprintf(stdout, "\n[ERROR] Returned file is different from Expected output at line %d!", 
        		lineno);
        	
		    free( line_expected );
        	free( line_returned );		    
        	return -1;        
        }
        
        // Ressetting variables
        lineno ++;
        free( line_expected );
        free( line_returned );
        len_expected = len_returned = 0;    
        line_expected = line_returned = NULL;
    }
    
    read_returned = getline(&line_returned, &len_returned, fp_returned);
    
    if ( read_returned != -1 ){
    	free( line_returned );
    	
        fprintf(stderr, "\n[ERROR] Returned output is bigger than Expected output ( line = %d )!",
        	lineno);    	
    	
    	return -1;
    
    }
    
    return 0;

}

int exec_and_compare( char *cmd, char* filename){

    FILE *fp_returned, *fp_expected;
    
    int retval;
    
    int pontos = 0;

    fp_expected = popen(cmd, "r");    
    if (! fp_expected ){
    	fprintf(stderr, "incorrect parameters or too many files.\n");
    	return 0;
    }
    
    fp_returned = fopen(filename, "r");    
    if (! fp_returned ){
    
    	fprintf(stderr, "Error: file '%s' not encountered! .\n", filename);
    	
    	return 0;

    } else {
    
	    retval = compare2outputs( fp_expected , fp_returned );    
    
        if ( retval == 0 ){
    		pontos = 1 ;
    		fprintf(stdout, "ok");
    	} else {

	    }
    }
    
    pclose( fp_expected );
    fclose( fp_returned );
    
    return pontos;
}


int main(int argc, char ** argv, char *envp[]){

    pid_t pid;
    FILE *fp_returned, *fp_expected;
    
    int retval;
    
#ifdef __DEBUG__
	stderr_fp = stderr;
#else 
	stderr_fp = fopen("/dev/null", "w");
#endif
    
    int pontos = 0, maximo = 0, QUESTAO = 1;
    
    char LETRA = 'a';

    int status;
    
    fprintf(stdout, "\nINICIANDO CORREÇÃO ... ");

    // 1a: Todas as strings contendo 0’s ou 1’s 
    fprintf(stdout, "\n%d%c: Todas as strings contendo 0’s ou 1’s ... ", QUESTAO, LETRA);
    fflush(stdout);
    
    pontos += exec_and_compare( "bash egrep -o '[01]+' ./bruxarias.dat",
	    "1a.txt");
	    
    maximo ++;
    LETRA ++;
    
    // 1b: Todas as strings representando números binários de 8 bits
    fprintf(stdout, "\n%d%c: Todas as strings representando números binários de 8 bits ... ", QUESTAO, LETRA);
    fflush(stdout);    
    
    pontos += exec_and_compare( "bash egrep -o '1[01]{,7}' ./bruxarias.dat",
	    "1b.txt");    	   
    
    maximo ++;
    LETRA ++;
        
    // 1c: Todas as linhas que contém exatamente 1 número binário.
    fprintf(stdout, "\n%d%c: Todas as linhas que contém exatamente 1 número binários ... ", QUESTAO, LETRA);
    fflush(stdout);
    
    pontos += exec_and_compare( "bash egrep -o '^1[01]{,7}$' ./bruxarias.dat",
	    "1c.txt");
	    
    fflush(stdout);    	    
    
    maximo ++;
    LETRA ++;
       
    // 1d: Todos os números decimais.
    fprintf(stdout, "\n%d%c: Todos os números decimais ... ", QUESTAO, LETRA);
    fflush(stdout);    

    pontos += exec_and_compare( "bash egrep -wo '([1-9][0-9]+|[0-9]{1,1})' ./bruxarias.dat",
	    "1d.txt");
	    
    fflush(stdout);    	    
    
    maximo ++;
    LETRA ++;
        
    // 1e: Todas as ocorrências das letras ‘u’ ou ‘e’ seguidas da sequencia de letras ‘tt’
    fprintf(stdout, 
    	"\n%d%c: Todas as ocorrências das letras ‘u’ ou ‘e’ seguidas da sequencia de letras ‘tt’ ... ", 
    	QUESTAO, 
    	LETRA);
    	
    fflush(stdout);    	
    
    pontos += exec_and_compare( "bash egrep -o '[ue]tt' ./bruxarias.dat",
	    "1e.txt");    
	    
    fflush(stdout);    	    

    maximo ++;
    LETRA ++;
	    
    // 1f: Uma palavra da língua inglesa. Considere que uma palavra da língua inglesa:
    fprintf(stdout, 
    	"\n%d%c: Palavras da língua inglesa ...", 
    	QUESTAO, 
    	LETRA);  
    fflush(stdout);    	  
    
    pontos += exec_and_compare( "egrep -o '[A-Za-z][a-z]{2,}' ./bruxarias.dat",
	    "1f.txt");	    
	    
    fflush(stdout);    	    

    maximo ++;
    LETRA ++;
    
    // 1g: Variáveis em uma linguagem de programação.
    fprintf(stdout, 
    	"\n%d%c: Variáveis em uma linguagem de programação ...", 
    	QUESTAO, 
    	LETRA);
    fflush(stdout);    	
    
    pontos += exec_and_compare( "egrep -wo '[A-Za-z]+[a-zA-Z0-9_]{,}' ./bruxarias.dat",
	    "1g.txt");	    
	    
    fflush(stdout);    	    

    maximo ++;
    LETRA ++;
    
    // 1h: Endereco IPv4
    fprintf(stdout, 
    	"\n%d%c: Enderecos IPv4 ... ", 
    	QUESTAO, 
    	LETRA);
    fflush(stdout);    	
    
    pontos += exec_and_compare( "egrep -wo '(([0-9])|([1-9][0-9])|(1[0-9][0-9])|(2[0-4][0-9])|(25[0-5]))\\.(([0-9])|([1-9][0-9])|(1[0-9][0-9])|(2[0-4][0-9])|(25[0-5]))\\.(([0-9])|([1-9][0-9])|(1[0-9][0-9])|(2[0-4][0-9])|(25[0-5]))\\.(([0-9])|([1-9][0-9])|(1[0-9][0-9])|(2[0-4][0-9])|(25[0-5]))' ./bruxarias.dat",
	    "1h.txt");	    
	    
    fflush(stdout);    	    

    maximo ++;
    LETRA ++;    
    
    /*********
    QUESTAO 2
    *********/
    QUESTAO++ ;
    LETRA = 'a';
    
    // 2a: Diretorios de /etc
    fprintf(stdout, 
    	"\n%d%c: Diretorios em /etc ...", 
    	QUESTAO, 
    	LETRA);
    fflush(stdout);  
    
    pontos += exec_and_compare( "find /etc -type d",
	    "2a.txt");	    
	    
    fflush(stdout);    	    

    maximo ++;
    LETRA ++;
    
    // 2b: Diretorios de /etc sem subdiretorios
    fprintf(stdout, 
    	"\n%d%c: Diretorios em /etc sem subdiretorios ... ", 
    	QUESTAO, 
    	LETRA);
    fflush(stdout);  
    
    pontos += exec_and_compare( "find /etc -maxdepth 1 -type d",
	    "2b.txt");	    
	    
    fflush(stdout);    	    

    maximo ++;
    LETRA ++; 
    
    // 2c: Arquivos em  /etc com mais de 1KiB
    fprintf(stdout, 
    	"\n%d%c: Arquivos em /etc com mais de 1 KiB ... ", 
    	QUESTAO, 
    	LETRA);
    fflush(stdout);  
    
    pontos += exec_and_compare( "find /etc -size +1k -type f",
	    "2c.txt");	    
	    
    fflush(stdout);    	    

    maximo ++;
    LETRA ++;
    
    // 2d: Arquivos em home modificados no ultimos 7 dias
    fprintf(stdout, 
    	"\n%d%c: Arquivos modificados na última semana na pasta /var  ...", 
    	QUESTAO, 
    	LETRA);
    fflush(stdout);  
    
    pontos += exec_and_compare( "find /var -mtime -7",
	    "2d.txt");
	    
    fflush(stdout);    	    

    maximo ++;
    LETRA ++;
     
    /*********
    QUESTAO 3
    *********/
    QUESTAO++ ;
    LETRA = 'a';    
    
    // 3a: printar usuarios
    fprintf(stdout, 
    	"\n%d%c: Printar usuarios do sistema ...", 
    	QUESTAO, 
    	LETRA);
    fflush(stdout);  
    
    pontos += exec_and_compare( "awk -F':' '{ print $1 }' /etc/passwd",
	    "3a.txt");
	    
    fflush(stdout);    	    

    maximo ++;
    LETRA ++;
    
    // 3bs: printar usuarios entre as linhas 10 e 20
    fprintf(stdout, 
    	"\n%d%c: Printar usuarios entre as linhas 10 e 20 ...", 
    	QUESTAO, 
    	LETRA);
    fflush(stdout);  
    
    pontos += exec_and_compare( "awk -F':' '{ if (NR>10 && NR<20) print $1 }' /etc/passwd",
	    "3b.txt");
	    
    fflush(stdout);    	    

    maximo ++;
    LETRA ++;    
    
    /**********
    QUESTAO 4
    ***********/
    QUESTAO ++;
    LETRA = 'a';
        
    // 4a: Substituir usernaname
    fprintf(stdout, 
    	"\n%d%c: Substituir nome do usuario corrente por 'exercicio' em /etc/passwd ...", 
    	QUESTAO, 
    	LETRA);
    fflush(stdout);
    
    pontos += exec_and_compare( "sed \"s/`whoami`/exercicio/\" /etc/passwd",
	    "4a.txt");
	    
    fflush(stdout);    	    

    maximo ++;
    LETRA ++;
    
    // 4b: Remover linha com username
    fprintf(stdout, 
    	"\n%d%c: Remover linha com username 'exercicio' de /etc/passwd ...", 
    	QUESTAO, 
    	LETRA);
    fflush(stdout);
    
    pontos += exec_and_compare( "sed \"/`whoami`/d\" /etc/passwd",
	    "4b.txt");
	    
    fflush(stdout);    	    

    maximo ++;
    LETRA ++;    
    
    
/*    
    if (  pid = fork() ){

        QUESTAO ++ ;

        waitpid( pid , &status, 0);

        maximo ++;

        if (status == 0){

            pontos ++;
            fprintf(stdout, "ok");

        } else {
            fprintf(stdout, "\nERRO (retval = %d)", status);
        }

    } else {

        int ret = execv( "./.tests/criacao_grupos.sh" , argv);
        exit( ret );
                
    }
    
*/    
           
            
    fprintf(stdout, "\nTOTAL: %d/%d", pontos, maximo);
    
    float nota = 10 * ( (float)pontos)/( (float)maximo);
    
    fprintf(stdout, "\nNOTA: %.1f\n", nota);
    
#if __DEBUG__

#else 
	fclose( stderr_fp );
#endif    

    return 0;
}
