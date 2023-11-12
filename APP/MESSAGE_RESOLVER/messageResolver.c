//
// Created by Clarence Hirsch on 18/10/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "messageResolver.h"
#include "../LOGGER/logger.h"
#include "../UTILS/utils.h"

/**
 * create_translation_list
 * Creates a new translation list
 * size is set to 0
 * @param numTranslations The number of translations to allocate space for
 * @return A pointer to the new translation list
 */
TranslationList *create_translation_list(int numTranslations) {
    TranslationList *translationList = malloc(sizeof(TranslationList));
    translationList->translations = malloc(sizeof(Translation) * numTranslations);
    translationList->size = 0;
    return translationList;
}

/**
 * loadTranslations
 * Loads translations from a file
 * The file should be in the format:
 *      messageID=translation
 * a new TranslationList is created and initialized with the translations from the file
 * @param filename The name of the file to load translations from
 * @return A pointer to the new translation list
 */
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
        //skip lines that start with a #
        if(ch == '#'){
            while(ch != '\n' && ch != EOF){
                ch = fgetc(file);
            }
            ch = fgetc(file);
        }
        if(ch == '\n')
        {
            lines++;
        }
    }
    rewind(file);
    lines++; //add one to account for the last buffer

    logMessage(INFO, "Number of lines in file: %d", lines);

    TranslationList *translationList = create_translation_list(lines);


    char buffer[512]; // Assuming lines won't exceed 511 characters
    while (fgets(buffer, sizeof(buffer), file)) {
        // Skip lines that start with '#'
        if (buffer[0] == '#') {
            continue;
        }

        // Parse and add translations
        if (sscanf(buffer, "%255[^=]=%255[^\n]\n", translationList->translations[translationList->size].messageID, translationList->translations[translationList->size].translation) == 2) {
            translationList->size++;
        } else {
            perror("Error parsing translation file");
        }
    }

    fclose(file);
    return translationList;
}

/*
 * translate
 * Translates a messageID to a translation
 * @param messageID The messageID to translate
 * @param translationList The translation list to search for the messageID
 * @return The translation of the messageID
 */
const char *translate(const char *messageID, TranslationList *translationList) {
    if (messageID == NULL) {
        logMessage(ERROR, "messageID is NULL");
        return "NULL messageID";
    }
    for (int i = 0; i < translationList->size; i++) {
        if (strcmp(messageID, translationList->translations[i].messageID) == 0) {
            return translationList->translations[i].translation;
        }
    }
    return messageID; // Return the original English string if no translation is found
}

/*
 * freeTranslationList
 * Frees the memory allocated for a translation list
 * The memory allocated for the translations is also freed
 * @param translationList The translation list to free
 */
void freeTranslationList(TranslationList *translationList){
    free(translationList->translations);
    free(translationList);
}

char* languagePathResolver(enum Language language){
    switch (language) {
        case EN:
            return "../TRANSLATIONS/message-EN.env";
        case FR:
            return "../TRANSLATIONS/message-FR.env";
        default:
            perror("Language not supported");
            exit(1);
    }
}


Language selectLanguageMenu(){
    int choice = 0;
    int movement = 0;
    do {
        system("/bin/stty cooked");
        cls();
        printf("Select your language:\n");
        printf("%s", choice==0 ? "\x1b[30;47m(*)" : "()");
        printf(" English%s\n",  choice==0 ? "\x1b[0m" : "");
        printf("%s", choice==1 ? "\x1b[30;47m(*)" : "()");
        printf(" French%s\n",  choice==1 ? "\x1b[0m" : "");

        printf("\n\nPress c to confirm\n");
        system("/bin/stty raw");
        movement = getchar();
        system("/bin/stty cooked");
        if (movement == 66 && choice < 1 ) {
            choice++;
        } else if (movement == 65 && choice > 0) {
            choice--;
        }
    } while (movement != 'c' && movement != 'C');
    switch (choice) {
        case 0:
            logMessage(INFO, "Language selected: EN");
            return EN;
        case 1:
            logMessage(INFO, "Language selected: FR");
            return FR;
        default:
            logMessage(ERROR, "Invalid language selected, defaulting to EN");
            return EN;
    }
}