#include <stdio.h>
#include <stdlib.h>
#include "textRead.h"
void printShaderInfoLog(GLuint shader)
{
    int infologLength = 0;
    int charsWritten  = 0;
    GLchar *infoLog;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH,
                  &infologLength);
    
    if (infologLength > 0)
    {
        infoLog = (GLchar *)
        malloc(infologLength);
        if (infoLog == NULL)
        {
            printf(
                   "Couldn’t alloc InfoLog buf\n");
            exit(1);
        }
        glGetShaderInfoLog(shader, infologLength,
                           &charsWritten, infoLog);
        printf("Shader InfoLog:\n%s\n\n",
               infoLog);
        free(infoLog);
    }
}
void printProgramInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;
    
    glGetProgramiv(obj, GL_INFO_LOG_LENGTH,
                   &infologLength);
    
    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength,
                            &charsWritten, infoLog);
        printf("%s\n",infoLog);
        free(infoLog);
    }
}

char* textRead(char* filename)
{
    FILE* file;
    char* content;
    int count = 0;
    
    if(filename != NULL)	{
        file = fopen(filename,"r+");
    }
    else	{
        printf("%s 파일이 없습니다.",filename);
        return 0;
    }
    if(file != NULL)	{
        fseek(file,0,SEEK_END);
        count = ftell(file);
        rewind(file);
        if(count > 0)	{
            content = new char[count + 1];
            count = fread(content,
                          sizeof(char),count,file);
            
            content[count] = '\0';
        }
        fclose(file);
    }
    else	{
        printf("파일이 없습니다.\n");
        return 0;
    }
    return content;
}