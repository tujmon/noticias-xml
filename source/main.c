/* 
1) Escolha um site de notícias que possui o recurso de feed RSS e faça o
download de seu arquivo .xml;

2) Crie um programa em C que recebe um arquivo RSS no formato .xml e
extrai as seguintes informações:
    a) Sobre o Canal

        i) Título do canal
        ii) Descrição do canal
        iii) Link do canal

    b) Sobre cada notícia (item)
        i) Título da notícia
        ii) Descrição da notícia
        iii) Link (se disponível)
        iv) Data de publicação se disponível

3) Essas informações deverão ser salvas em um arquivo de formato .html
com o seguinte padrão:
*/

#include "feed.h"

int main(void)
{
    FILE *fp;
    int ch;
    char tag[20] = "";
    int encontrouTag = 0;

    fp = fopen("news.xml", "r");

    if (fp == NULL)
    {
        fprintf(stderr, "Erro na abertura do arquivo");
        return 1;
    }
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '<')
        {
            findTag(fp, tag);
            printf("%s\n", tag);
            encontrouTag = 1;
        }

        if ((encontrouTag == 1) && (strcmp(tag, title) == 0))
        {
            findContent(fp);
            encontrouTag = 0;
            puts("");
        }
    }

    fclose(fp);
    return 0;
}
