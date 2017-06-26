#include <time.h>
#include <string.h>
#include "SymbolBuffer.h"

char* ReplaceNullSymb (char *buf1) {
    int i;
    char *temp = buf1;
    for ( ; *temp ; ++temp ) {
        if (*temp == '\0') {
           *temp = ' ';
        }
    }
    return buf1;
}

char* ReadBuf(char* debug_t, char* buf, int bufSize) {
    int i;
    for (i=0; i<BufLength(debug_t); i++) {
        buf[i]=(char)debug_t[i];
    }
    return buf;
}
void AddToBuf(char* text, int textSize) {
    strcat(debug_t,text);
}

//узнать сколько осталось места в буфере
int SpaceLeft(char* buf, int bufferSize) {
    int space=0;
    char *temp = buf;
    int counter = 0;
//    while (*temp != NULL) {
//        counter++;
//        ++temp;
//    }
    space = bufferSize-counter;
    return space;
}

int BufLength(char* buf) {
    int counter = 0;
    char *temp = buf;
//    while (*temp != NULL) {
//        counter++;
//        ++temp;
//    }
    return counter;
}

int WriteToFile(char* buf) {
    char buffer[225];
    time_t t = time(NULL); // get time and date
    struct tm* aTm = localtime(&t);
    FILE *logFile = fopen("serverlog.log", "a+"); // a+ (create + append) option will allow appending which is useful in a log file
    if (logFile == NULL) {
        perror("Ошибка при открытии serverlog.log - логи не будут сохранены");
        //return EXIT_FAILURE;
    }
    //fprintf(logFile,"%04d/%02d/%02d %02d:%02d:%02d: %s \n", aTm->tm_year+1900, aTm->tm_mon+1, aTm->tm_mday, aTm->tm_hour, aTm->tm_min, aTm->tm_sec, buf);
    //ReadBuf(debug_t,buffer,sizeof(buffer));
    fprintf(logFile,"%s", buf);
    fclose(logFile);
    *debug_t = 0;
    return 1;
}

int ClearBuf(char* buf, int size) {
    int i;
    for (i=0; i<size; i++) {
        buf[i]=0;
    }
    return 1;
}

void Log(char* text) {
    char buffer[225];
    int i;
    time_t t = time(NULL); // get time and date
    struct tm* aTm = localtime(&t);
    snprintf(buffer, sizeof(buffer), "[%02d:%02d:%02d] %s", aTm->tm_hour, aTm->tm_min, aTm->tm_sec, text);
    ReplaceNullSymb((char*)buffer);
    if (SpaceLeft(debug_t,sizeof(debug_t))>=strlen(buffer)) {
        //printf("%d >= %d\n", SpaceLeft(debug_t,sizeof(debug_t)), strlen(buffer));
        AddToBuf(buffer,strlen(buffer));
    }
    else {
        WriteToFile(debug_t);
        *debug_t = 0;
        AddToBuf(buffer,strlen(buffer));
    }
    printf("result %s", buffer);
}
/*
int main(int argc, char** argv) {
    //ClearBuf(debug_t, sizeof(debug_t));
    Log("COAP//:\n ,,,lssk\n");
    Log("other\n text\n");
    Log("way\n text\n");
    WriteToFile(debug_t);
    return (EXIT_SUCCESS);
}
*/


