//
// Created by Clarence Hirsch on 18/10/2023.
//

#ifndef DOOMDEPTHS_MESSAGERESOLVER_H
#define DOOMDEPTHS_MESSAGERESOLVER_H

typedef enum Language {
    EN,
    FR
} Language;

typedef struct {
    char messageID[256];
    char translation[256];
} Translation;

typedef struct {
    Translation *translations;
    int size;
} TranslationList;

TranslationList *create_translation_list(int numTranslations);

TranslationList *loadTranslations(const char *filename);

const char *translate(const char *messageID, TranslationList *translationList);

void freeTranslationList(TranslationList *translationList);

char* languagePathResolver(enum Language language);

enum Language selectLanguageMenu();

#endif //DOOMDEPTHS_MESSAGERESOLVER_H