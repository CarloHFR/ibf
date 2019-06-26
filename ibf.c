//Interpretador de brainfuck
//Criado por: Carlo Henrique FR
//Baseado em: https://www.youtube.com/watch?v=Wf3PK54oE6Y
//Data: 23/04/2019
//Versão: 1.0

#include <stdio.h>      //Biblioteca padrão de entrada e saida.
#include <stdlib.h>     //Biblioteca padrão.
#include <locale.h>     //Biblioteca que permite usar portugues no terminal.


#define TAM_MEMORIA 65536       //Definindo o tamanho da memoria para um valor fixo.
char memoria[TAM_MEMORIA];      //Criando um vetor para salvar os dados manipulados. (memoria tem no maximo 64k.).
char *celula = memoria;         //Uma celula é um espaço da memoria como uma gaveta em um gaveteiro. (Definindo um apontador na variavel celula)


#define TAM_PROGRAMA 65536              //Definindo o tamanho do programa para um valor fixo.
char programa[TAM_PROGRAMA];            //Criando um vetor para salvar o programa. (programa deve ser no maximo 64k).
char *enderecoPrograma = programa;      //Aponta o endereço da instruçao que esta sendo executada. (Definindo um apontador na variavel endecoPrograma).

int colchete;       //Variavel que é utilizado para saber se existe um loop no programa.

//Função que interpreta o programa.
int interpretador()
{
    //Executa ate que o programa acabe.
    while(*enderecoPrograma)
    {
        switch(*enderecoPrograma)       //Comparando as possiveis instruções para então executar as operações atricuidas a elas.
        {
            case '>':       //Avançando uma celula na memoria. (Incrementando o ponteiro da celula).
                celula++;
                break;

            case '<':       //Retornando para a celula anterior (Decrementando o ponteiro da celula).
                celula--;
                break;

            case '+':       //Incrementando o conteudo da celula.
                ++*celula;
                break;

            case '-':       //Decrementando o conteuda da celula.
                --*celula;
                break;

            case '.':       //Printando o conteudo da celula no terminal (DEVE ESTAR EM ASCII).
                putchar(*celula);
                break;

            case ',':       //Salvando um caracter fornecido pelo usuario.
                *celula = getchar();
                break;

            case '[':       //Verificando se existe um loop no programa.

                if(*celula == 0)        //Executa se o dado na celula for 0.
                {
                    colchete = 1;       //Variavel que guarda a quantidade de colchetes
                    while(colchete)     //Se existir um colchete execute.
                    {
                        enderecoPrograma++;     //Buscando a proxima instrução.

                        if(*enderecoPrograma == '[')        //Se encontrar um colchete aberto incremente a variavel colchete.
                        {
                            colchete++;
                        }

                        if(*enderecoPrograma == ']')        //Se encontrar um colchete fechado decremente a variavel colchete.
                        {
                            colchete--;
                        }
                    }
                }
                break;

            case ']':       //Verificando se existe um loop no programa.

                colchete = 1;       //Variavel que guarda a quantidade de colchetes
                while(colchete)     //Executa se a variavel colchete for diferente de zero.
                {
                    enderecoPrograma--;     //Retornando para a instrução anterior.

                    if(*enderecoPrograma == '[')        //Se encontrar um colchete fechado decremente a variavel colchete.
                    {
                        colchete--;
                    }

                    if(*enderecoPrograma == ']')        //Se encontrar um colchete aberto incremente a variavel colchete.
                    {
                        colchete++;
                    }
                }
                enderecoPrograma--;       //Retornando para a instrução anterior.
                break;
        }
        enderecoPrograma++;     //Incrementando o enderecoPrograma para executar a proxima instrução.
    }
}

//Função principal do programa (chama o interpretador).
int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Portuguese");    //Mudando a linguagem do terminal para portugues.

    FILE *arquivo;                      //Salvando o arquivo inteiro na variavel.
    char caractere;                     //Variavel para salvar um unico caractere por vez.
    int ponteiroPrograma = 0;           //Indice que sera usado para armazenar o caractere no vetor "programa".
    char *nomeArquivo;

    if (argc < 2)       //Checando se foi passado um arquivo.
    {
        printf("\n--ERRO - Arquivo não encontrado--\n");
        return(1);
    }
    else       //Se passado o arquivo receber o nome dele na variavel "nomeArquivo".
    {
        nomeArquivo = argv[1];
    }

    arquivo = fopen(nomeArquivo,"r");                   //Lendo o arquivo com nome passado pelo usuario, e salvando na variavel arquivo.

    while( (caractere = fgetc(arquivo))!= EOF )         //Lendo um caractere por vez da variavel aquivo e salvando no vetor "programa".
    {
        programa[ponteiroPrograma] = caractere;         //Salvando o caractere no endereço indicado pelo "ponteiroPrograma".
        ponteiroPrograma++;                             //Incrementando a variavel que faz o endereçamento do vetor "programa".
    }
    programa[ponteiroPrograma]='\0';                    //Finalizando o carregamento do programa colocando um '\0' para indicar o fim do vetor.

    fclose(arquivo);    //Fechando o arquivo.

    interpretador();    //Função utilizada para interpretar o programa.

    printf("\n");       //Quebrando a linha para ficar organizado no terminal.
    system("PAUSE");    //Pausar o sistema para que a janela do terminal não feche apos rodar o programa.
    return 0;           //Finalizando o programa.
}
