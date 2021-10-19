#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * ##### METHODEN-DEKLARATION #####
 */

// Ersetze Substring
int string_replace(char *, char *, char *);

// Ersetze Anrede im Brief
char *changeSalutation(char *, char *);

// Hilfsmethode fuer changeSalutation
char *changeGenderInLetter(char *, char *);

/**
 * ##### METHODEN-IMPLEMENTIERUNG #####
 */

/**
 * Veraendert die Anrede im Brief anhand Gender-"Flag" im Namen. Bsp: "Liebe(r)" wird bei weiblichen Adressat zu "Liebe"
 * Wenn kein Gender-"Flag" angegeben, bleibt die Anrede "Liebe(r)".
 * Entfernt Gender-"Flag" nach erfolgreicher Anpassung.
 * @param name - Name des Adressaten
 * @param brf - Brief an Adressaten
 * @return Name des Adressaten
 */
char *changeSalutation(char *name, char *brf) {
    // Wenn Gender-"Flag" maennlich oder weiblich ersetzen
    // Wenn kein "Flag", Brief nicht veraendern
    if (name[0] == 'm') {
        changeGenderInLetter("r", brf);
        memmove(name, name + 1, strlen(name));
    } else if (name[0] == 'f') {
        changeGenderInLetter("", brf);
        memmove(name, name + 1, strlen(name));
    }
    return name;
}

/**
 * Ersetze Gender-"Flag".
 * Hilfsmethode fuer changeSalutation
 * @param replaceGender - Zu ersetzende Anrede
 * @param brf - Brief an Adressat
 * @return Angepasster Brief
 */
char *changeGenderInLetter(char *replaceGender, char *brf) {
    string_replace(brf, "(r)", replaceGender);

    return brf;
}

/**
 * String-Replace Implementierung.
 * ueberprueft, ob der zu ersetzende String exisitiert.
 * Wenn Ja, wird der Substring durch Parameter replace ersetzt.
 * @param scr - Gesamter String
 * @param substring - Such-String
 * @param replace - Ersetz-String
 * @return errno
 */
int string_replace(char *scr, char *substring, char *replace) {
    char *substring_src = strstr(scr, substring); //returns pointer to that substring that we would like to replace
    if (substring_src == NULL) {
        errno = 1;
        return errno;
    }
    memmove(substring_src + strlen(replace), substring_src + strlen(substring),
            (strlen(substring_src) - strlen(substring) + 1));

    memcpy(substring_src, replace, strlen(replace)); //copies n characters from memory area src to memory area dest
    errno = 0;
    return errno;
}

// ##### MAIN-METHODE #####
/**
 * Main-Methode zum Erstellen von Serienbriefen.
 * Anhand eines char Arrays werden die Adressaten angegeben.
 * Im Verzeichnis Briefe/Template/ liegt die Briefvorlage.
 * Das Adressat-Array wird iteriert und fuer jeden Adressaten wird ein Brief angelegt.
 * Vor dem Anlegen wird geprueft, ob der Adressat weiblich oder maennlich ist, um entsprechend die Anrede anzupassen.
 * In der Briefvorlage wird der Platzhalter "###" fuer den Namen mit der Methode string_replace mit dem Namen
 * des Adressaten ersetzt.
 *
 * @return errno
 */
int main() {

    // File-Pointer. Zum Lesen und Schreiben der Dateien
    FILE *fp;

    // Errno
    errno = 0;

    //Briefvorlage
    char brfTemplate[1024];

    // Platzhalter fuer Namen in Briefvorlage
    char namePlaceholder[] = "###";

    // Alle Adressaten
    char *namen[100];

    char *adressaten[100];
    // Greife lesend auf Briefvorlage zu
    fp = fopen(".\\Briefe\\Namen\\Namen.txt", "r");
    //read line by line
    const int line_size = 300;
    char* line = malloc(line_size);
    int j = 0;
    while (fgets(line, line_size, fp) != NULL)  {
        adressaten[j] = line;
        j++;
    }
    free(line);

    fclose(fp);

    // Greife lesend auf Briefvorlage zu
    fp = fopen(".\\Briefe\\Template\\Brf.txt", "r");

    // Wenn Briefvorlage nicht vorhanden, beende Programm mit errno = 1
    if (fp == 0) {
        printf("sch... passiert\n");
        errno = 1;
        return errno;
    } else {
        // Wenn Briefvorlage vorhanden, schreibe Inhalt in Variable brfTemplate
        fgets(brfTemplate, 1024, fp);
    }

    // Schliesse File-Pointer mit Briefvorlage
    fclose(fp);

    //Hole Laenge des Adressaten-Arrays. Nur sizeof liefert Groesse in Byte
    int array_length = sizeof(adressaten) / sizeof(adressaten[0]);

    // Iteriere ueber Adressaten-Array mit Hilfe der Variable array_length
    for (int i = 0; i < array_length && adressaten[i] != NULL; i++) {

        // Brief vorbereiten
        char *brf = malloc(strlen(brfTemplate) + 1);

        // Brief-Vorlage kopieren
        strcpy(brf, brfTemplate);

        // Adressat vorbereiten
        char *name = malloc(strlen(adressaten[i]) + 1);

        // Adressat kopieren
        strcpy(name, adressaten[i]);

        // Entferne (r) in Anrede
        changeSalutation(name, brf);

        // Zusammenfuegen des Dateinamen
        // Pfad
        char fileName[1024] = ".\\Briefe\\";
        // Name des Adressaten
        strcat(fileName, name);
        // Suffix + Dateityp
        strcat(fileName, "Brf.txt");

        // Oeffne File
        fp = fopen(fileName, "w+");
        if (fp == 0) {
            printf("sch... passiert\n");
            errno = 1;
            return errno;
        } else {
            // Ersetze Namen-Platzhalter mit Adressat-Name
            string_replace(brf, namePlaceholder, name);
            
            // Mit File-Pointer den Brief in Datei schreiben
            fprintf(fp, "%s\n", brf);
            
            // File-Pointer schliessen
            fclose(fp);
        }

        // Speicherplatz fuer Brief wieder freigeben
        free(brf);
    }

    // Programm beenden
    return errno;
}
