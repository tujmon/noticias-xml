#include "feed.h"

void findTag(FILE *fp, char tag[20])
{
    int i = 0;
    int ch;

    while (((ch = fgetc(fp)) != EOF) && (ch != '>') && (i < 19))
    {
        tag[i] = ch;
        i++;
    }
    tag[i] = '\0';
}

void findContent(FILE *fp, FILE *fp2)
{
    int ch;
    if ((ch = fgetc(fp)) != EOF && (ch != '<'))
    {
        fprintf(fp2, "%c", ch);
        while (((ch = fgetc(fp)) != EOF) && (ch != '<'))
        {
            fprintf(fp2, "%c", ch);
        }
    }
}
