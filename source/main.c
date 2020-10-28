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

const char *title = "title";
const char *link = "link";
const char *description = "description";
const char *item = "item";
const char *pubDate = "pubDate";
int main(void)
{
    FILE *fp;
    FILE *fp2;
    int ch;
    char tag[20] = "";
    int encontrouTag = 0;
    int count = 0;

    fp = fopen("./elpais.xml", "r");
    fp2 = fopen("index.html", "w");

    if (fp == NULL)
    {
        fprintf(stderr, "Erro na abertura do arquivo");
        return 1;
    }
    if (fp2 == NULL)
    {
        fprintf(stderr, "Erro!");
        return 1;
    }
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '<')
        {
            findTag(fp, tag);
            encontrouTag = 1;
        }
        if ((encontrouTag == 1) && (strcmp(tag, title) == 0))
        {
            if (count == 0)
            {
                fprintf(fp2, "%s", "<!DOCTYPE html>\n");
                fprintf(fp2, "%s", "<html>\n");
                fprintf(fp2, "%s", "<head>\n");
                fprintf(fp2, "%s", "<title>");
                findContent(fp, fp2);
                fprintf(fp2, "%s", "</title>\n");
                fprintf(fp2, "%s", "</head>\n");
                fprintf(fp2, "%s", "<body>\n");
                count = 1;
                encontrouTag = 0;
                puts("");
                fseek(fp, 0, SEEK_SET);
            }
            else
            {
                fprintf(fp2, "%s", "<h2>");
                findContent(fp, fp2);
                fprintf(fp2, "%s", "</h2>\n");
                encontrouTag = 0;
                puts("");
            }
        }
        if ((encontrouTag == 1) && (strcmp(tag, link) == 0))
        {
            fprintf(fp2, "%s", "<a href=");
            findContent(fp, fp2);
            fprintf(fp2, "%s", ">Saiba mais");
            fprintf(fp2, "%s", " </a>\n");
            encontrouTag = 0;
            puts("");
        }
        if ((encontrouTag == 1) && (strcmp(tag, description) == 0))
        {
            fprintf(fp2, "%s", "<p>");
            findContent(fp, fp2);
            fprintf(fp2, "%s", "</p>\n");
            encontrouTag = 0;
            puts("");
        }
        if ((encontrouTag == 1) && (strcmp(tag, item) == 0))
        {

            fprintf(fp2, "%s", "<hr>\n");
            encontrouTag = 0;
        }
        if ((encontrouTag == 1) && (strcmp(tag, pubDate) == 0))
        {
            fprintf(fp2, "%s", "<p>");
            findContent(fp, fp2);
            fprintf(fp2, "%s", "</p>\n");
            encontrouTag = 0;
            puts("");
        }
    }
    puts("");
    fprintf(fp2, "%s", "<hr>\n");
    puts("");
    fprintf(fp2, "%s", "</body>\n");
    fprintf(fp2, "%s", "</html>");

    fclose(fp);
    return 0;
}
