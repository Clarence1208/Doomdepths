//
// Created by Clarence Hirsch on 18/10/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "messageResolver.h"

// Function to create a translation list
TranslationList *create_translation_list(int numTranslations) {
    TranslationList *translationList = malloc(sizeof(TranslationList));
    translationList->translations = malloc(sizeof(Translation) * numTranslations);
    translationList->size = 0;
    return translationList;
}

// Function to load translations from a file
TranslationList *loadTranslations(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    //count number of lines in file
    int ch = 0;
    int lines = 0;
    while(!feof(file))
    {
        ch = fgetc(file);
        if(ch == '\n')
        {
            lines++;
        }
    }
    rewind(file);

    TranslationList *translationList = create_translation_list(lines);


    while (fscanf(file, "%255[^=]=%255[^\n]\n",translationList->translations[translationList->size].messageID, translationList->translations[translationList->size].translation) == 2) {
        translationList->size++;
    }

    fclose(file);
    return translationList;
}

// Function to lookup a translation
const char *translate(const char *messageID, Translation translations[], int numTranslations) {
    for (int i = 0; i < numTranslations; i++) {
        if (strcmp(messageID, translations[i].messageID) == 0) {
            return translations[i].translation;
        }
    }
    return messageID; // Return the original English string if no translation is found
}