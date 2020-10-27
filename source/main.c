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
const char *channel = "channel";
const char *item = "item";
const char *pubDate = "pubDate";
int main(void)
{
    FILE *fp;
    int ch;
    char tag[20] = "";
    int encontrouTag = 0;
    int i = 1;
    int count = 0;

    fp = fopen("./elpais.xml", "r");

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
            encontrouTag = 1;
        }
        if ((encontrouTag == 1) && (strcmp(tag, title) == 0))
        {
            if (count == 0)
            {
                printf("<html>\n");
                printf("<head>\n");
                printf("    <title>");
                findContent(fp);
                printf("</title>\n");
                printf("</head>\n");
                printf("<body>\n");
                printf("<h%d>", i);
                printf("</h%d>\n", i);
                count = 1;
                i++;
                encontrouTag = 0;
                puts("");
            }
            else
            {
                printf("<h%d>", i);
                findContent(fp);
                printf("</h%d>", i);
                i++;
                encontrouTag = 0;
                puts("");
            }
        }
        if ((encontrouTag == 1) && (strcmp(tag, link) == 0))
        {
            printf("<a href=");
            findContent(fp);
            printf("</a>");
            encontrouTag = 0;
            puts("");
        }
        if ((encontrouTag == 1) && (strcmp(tag, description) == 0))
        {
            printf("<p>");
            findContent(fp);
            printf("</p>");
            encontrouTag = 0;
            puts("");
        }
        if ((encontrouTag == 1) && (strcmp(tag, channel) == 0))
        {
            puts("");
            puts("<body>");
            encontrouTag = 0;
            puts("");
        }
        if ((encontrouTag == 1) && (strcmp(tag, item) == 0))
        {
            puts("");
            puts("<hr>");
            encontrouTag = 0;
            puts("");
        }
        if ((encontrouTag == 1) && (strcmp(tag, pubDate) == 0))
        {
            printf("<p>");
            findContent(fp);
            printf("</p>");
            encontrouTag = 0;
            puts("");
        }
    }
    puts("");
    printf("<hr>");
    puts("");
    printf("</body>\n");
    printf("</html>");

    fclose(fp);
    return 0;
}
