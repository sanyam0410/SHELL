#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>                   // ssize_t
#include<string.h>                  // for library function strtok, it seperates the string into tokens which helps in
                                   // in differentiating between the command and argument
void execmd(char **argv){
    char *cmd = NULL;

    if(argv){

        cmd=argv[0];   //get command

        if(execve(cmd, argv, NULL)==-1) {    ///execution of the command
           perror("Error: ");
    };
    }
}

int main(int argc, char **argv){              /* parameters are used in main() for taking input from 
                                                  command-line*/
    char *l_ptr=NULL, *title="Shell$ ", *l_ptrc=NULL, *token;
    size_t n=0;                                // stores allocated size in bytes
    int n_t=0, i;
    ssize_t e_char;
    const char *lim=" \n";                        // constant char value
    
    (void)argc;

    while(1){                     // loop for the shell
        printf("%s",title);

        e_char=getline(&l_ptr, &n, stdin);   // exit stores the input of getline, stdin is used as input is taken from standard input
       
        if(e_char==-1){                       // checks if the getline fn failed or user used ctrl+d
            printf("exit.............\n");
            return -1;
        }

        l_ptrc=malloc(sizeof(char) * e_char);
       
        if(l_ptrc==NULL){
            perror("memory allocation error");
            return -1;
        }

        strcpy(l_ptrc, l_ptr);

        // tokenisation of the string
        // counting of the tokens
        token = strtok(l_ptr, lim);           
        while (token!=NULL)
        {
            n_t++;
            token = strtok(NULL, lim);
        }
        n_t++;
        
        // memory allocation for the tokens
        argv = malloc(sizeof(char *) * n_t);

        // storing in argv array
        token = strtok(l_ptrc, lim);

        for(i=0;token!=NULL;i++){
            argv[i] = malloc(sizeof(char) * strlen(token));
            strcpy(argv[i], token);

            token = strtok(NULL, lim);
        }
            argv[i]=NULL;

            // execution
            execmd(argv);                     
    }      

    // freeing allocated memory  
        free(l_ptr);
        free(l_ptrc);
    return 0;
}