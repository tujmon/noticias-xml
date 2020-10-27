#ifndef FEED_H
#define FEED_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void findTag(FILE *fp, char tag[20]);
void findContent(FILE *fp, FILE *fp2);

#endif