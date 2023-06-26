#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

//clear array
void removeChar(char *str[])
{
    *str='\0';
}

int changeName()
{
    printf("\n\n");
    int wordLength,j=0,jumpNum=0,z,difference,control2,fla=0,spare,nameCount=0;
    char searchedWord[60],backupFile[3000],searchedFilePath[100],flag[100],flag2[100],control[30],newWord[100],flagArray,flagArray2,nameFlag[100][100];
    char spareArray[300],txtArray[3000],nameFlag2[100][100],newWordFlag[100],oldWordFlag[100],pathFlag[200],pathFlag2[200];
    getchar();
A: //tag control
    printf("Word/phrase group to be renamed: ");
    fgets(searchedWord,60,stdin);
    if(searchedWord[0]!='[' || searchedWord[1]!='[' || searchedWord[strlen(searchedWord)-2]!=']' || searchedWord[strlen(searchedWord)-3]!=']')
    {
        printf("\033[31m\nIncorrect format. Ex: [[Hello]]\n\033[0m");
        goto A;
    }
    searchedWord[strcspn(searchedWord,"\n")]=0;
B: //tag control
    printf("New word/phrase group: ");
    fgets(newWord,60,stdin);
    if(newWord[0]!='[' || newWord[1]!='[' || newWord[strlen(newWord)-2]!=']' || newWord[strlen(newWord)-3]!=']')
    {
        printf("\033[31m\nIncorrect format. Ex: [[Hello]]\n\033[0m");
        goto B;
    }
    newWord[strcspn(newWord,"\n")]=0;
    int f=0;
    //backup process
    for(int x=2; x<strlen(newWord)-2; x++)
    {
        newWordFlag[f]=newWord[x];
        f++;
    }
    for(int i=0; i<strlen(newWordFlag); i++)
    {
        if(newWordFlag[i]==' ')
            newWordFlag[i]='_';
    }
    f=0;
    for(int x=2; x<strlen(searchedWord)-2; x++)
    {
        oldWordFlag[f]=searchedWord[x];
        f++;
    }

    wordLength=strlen(searchedWord);
    strcpy(searchedFilePath,"C:\\Users\\baran\\OneDrive\\Belgeler\\University\\");
    strcpy(flag,searchedFilePath);

    //file scan
    DIR* dir2=opendir("C:\\Users\\baran\\OneDrive\\Belgeler\\University\\");
    if(dir2==NULL)
    {
        return 1;
    }
    struct dirent* entitiy2;
    entitiy2=readdir(dir2);
    while(entitiy2!=NULL)
    {
        //two rounds of jumping
        strcpy(control,entitiy2->d_name);
        control[strcspn(control,"\n")]=0;
        if(!strcmp(control,"src") || !strcmp(control,"output.txt"))
        {
            goto I;
        }
        if(jumpNum<=1)
        {
            jumpNum++;
            goto I;
        }
        if(control[(strlen(control)-4)]=='.')
        {
            goto I;
        }
        jumpNum=0;
        strcpy(searchedFilePath,flag);
        strcat(searchedFilePath,entitiy2->d_name);
        searchedFilePath[strcspn(searchedFilePath,"\n")]=0;
        strcpy(flag2,searchedFilePath);
        //subfile scan
        DIR* dir=opendir(searchedFilePath);
        if(dir==NULL)
        {
            return 1;
        }
        struct dirent* entitiy;
        entitiy=readdir(dir);
        while(entitiy!=NULL)
        {
            //two rounds of jumping
            if(jumpNum<=1)
            {
                jumpNum++;
                goto M;
            }
            strcpy(control,entitiy->d_name);
            if(control[(strlen(control)-3)]!='t')
            {
                goto M;
            }
            strcpy(nameFlag[nameCount],entitiy->d_name);
            nameFlag[nameCount][strcspn(nameFlag[nameCount],"\n")]=0;
            nameCount++;

            if(!strcmp(nameFlag,nameFlag2))
            {
                printf("%s  ==  %s\n",nameFlag2,nameFlag);
            }
            //path adjustment
            strcpy(searchedFilePath,flag2);
            strcpy(pathFlag2,flag2);
            strcat(searchedFilePath,"\\");
            strcat(searchedFilePath,entitiy->d_name);
            searchedFilePath[strcspn(searchedFilePath,"\n")]=0;
            //reading txt
            FILE *searched;
            if((searched=fopen(searchedFilePath,"r"))==0)
            {
                perror("\033[31mError opening a file\033[0m");
                goto M;
            }
            if(fla!=0)
            {
                removeChar(txtArray);
            }
            fla++;
            while(fgets(spareArray,300,searched))
            {
                strcat(txtArray,spareArray);
            }
            fclose(searched);
            strcpy(backupFile,txtArray);
            strcat(backupFile," ");
            int w=0;
            //finding and correcting the tag
            while(w!=1)
            {
                w++;
                if(wordLength>=strlen(backupFile))
                    continue;
                j=0;
                for(int i=0; i<strlen(backupFile)-wordLength; i++)
                {
                    if(strlen(backupFile)<=1)
                        break;


                    for(j=0; j<wordLength; j++)
                    {
                        if(backupFile[i+j]!=searchedWord[j])
                        {
                            j=0;
                            break;
                        }

                        if(j==wordLength-1 && (isdigit(backupFile[i+j+1])==0 && isalpha(backupFile[i+j+1])==0))
                        {
                            if((i+j)-(strlen(searchedWord)-1)!=0)
                            {
                                if(isalpha(backupFile[(i+j)-strlen(searchedWord)])==0)
                                {
                                    z=(i+j)-strlen(searchedWord);
                                    control2=z;
                                    difference=(strlen(newWord)-strlen(searchedWord));
                                    if(strlen(newWord)>strlen(searchedWord))
                                    {

                                        difference=(strlen(newWord)-strlen(searchedWord));
                                        while(difference>0)
                                        {
                                            for(int x=0; x<(strlen(backupFile)-(i+j)-strlen(searchedWord)); x++)
                                            {
                                                if(x==0)
                                                {
                                                    flagArray=backupFile[z+1];
                                                    backupFile[z+1]=backupFile[z];
                                                    backupFile[z]=' ';
                                                }
                                                else
                                                {
                                                    flagArray2=backupFile[z+1];
                                                    backupFile[z+1]=flagArray;
                                                    flagArray=flagArray2;
                                                }
                                                z++;
                                                control2++;
                                                if(strlen(backupFile)-1==control2)
                                                    break;
                                            }
                                            control2=(i+j)-strlen(searchedWord)-1;
                                            z=(i+j)-strlen(searchedWord);
                                            z++;
                                            difference=difference-1;
                                        }
                                    }
                                    else if(strlen(newWord)<strlen(searchedWord))
                                    {
                                        z=(i+j+1)+(difference);
                                        while(difference<0)
                                        {
                                            backupFile[z]=' ';
                                            z++;
                                            difference++;
                                        }
                                        difference=(strlen(newWord)-strlen(searchedWord));
                                        z+=difference;
                                        spare=z+1;
                                        difference=difference*(-1);
                                        while(difference>0)
                                        {
                                            for(int x=0; x<(strlen(backupFile)-z); x++)
                                            {
                                                backupFile[spare]=backupFile[spare+1];
                                                spare++;
                                                if(spare+1==strlen(backupFile))
                                                {
                                                    break;
                                                }
                                            }
                                            spare=z+1;
                                            difference--;
                                        }
                                        difference=(strlen(newWord)-strlen(searchedWord));
                                        difference=difference*(-1);
                                        while(difference>0)
                                        {
                                            backupFile[strlen(backupFile)-difference]=' ';
                                            difference--;
                                        }
                                    }
                                    z=(i+j)-strlen(searchedWord);
                                    for(int x=0; x<strlen(newWord); x++)
                                    {
                                        backupFile[z+1]=newWord[x];
                                        z++;
                                    }
                                    printf("\033[32m%s converted to %s\n\033[0m",searchedWord,newWord);
                                    //saving the edited file
                                    FILE *wrtFile;
                                    if((wrtFile=fopen(searchedFilePath,"w"))==0)
                                    {
                                         perror("\033[31mError opening a file\033[0m");;
                                    }
                                    else
                                    {
                                        fputs(backupFile,wrtFile);
                                    }
                                    fclose(wrtFile);
                                    j=0;
                                    break;
                                }
                            }
                            else
                            {
                                printf("\033[32m%s converted to %s\n\033[0m",entitiy->d_name,newWord);
                                j=0;
                                break;
                            }
                        }
                    }
                }
            }
            for(int x=0; x<nameCount; x++)
            {
                for(z=0; z<(strlen(nameFlag[x])-4); z++)
                {
                    nameFlag2[x][z]=nameFlag[x][z];
                }
            }
            //file name editing
            for(int x=0; x<nameCount; x++)
            {
                if(!strcmp(oldWordFlag,nameFlag2[x]))
                {
                    strcat(oldWordFlag,".txt");
                    strcat(newWordFlag,".txt");
                    strcpy(pathFlag,searchedFilePath);
                    pathFlag[strcspn(pathFlag,"\n")]=0;
                    pathFlag2[strcspn(pathFlag2,"\n")]=0;
                    strcat(pathFlag2,"\\");
                    strcat(pathFlag2,newWordFlag);
                    pathFlag2[strcspn(pathFlag2,"\n")]=0;
                    printf("%s\n%s\n\n\n",pathFlag,pathFlag2);
                    int ret = rename(pathFlag, pathFlag2);

                    if(ret == 0)
                    {
                        printf("\033[32mFile name successfully changed\n\033[0m");
                    }
                    else
                    {
                        printf("\033[31mFailed to change file name\n\033[0m");
                    }
                }
            }
M:
            entitiy=readdir(dir);
        }
        closedir(dir);
I:
        entitiy2=readdir(dir2);
    }
    closedir(dir2);
    return 0;
}

//printing of tags
void writeOutput()
{
    char control[30],path[100],flag[100],searched[10],flag2[100],backupFile[500],tagArray[100][100],requestArray[100][100];
    int i=0,j,m=2,a,tagCount=0,requestCount=0;
    strcpy(searched,"[[");
    int sayac=0;
    strcpy(path,"C:\\Users\\baran\\OneDrive\\Belgeler\\University\\");
    strcpy(flag,path);
    //file scan
    DIR* dir=opendir("C:\\Users\\baran\\OneDrive\\Belgeler\\University\\");
    if(dir==NULL)
    {
        return 1;
    }
    struct dirent* entitiy;
    entitiy=readdir(dir);
    while(entitiy!=NULL)
    {
        //two rounds of jumping
        if(sayac<=1)
        {
            sayac++;
            goto P;
        }
        strcpy(control,entitiy->d_name);
        control[strcspn(control,"\n")]=0;
        //is txt
        for(i=0; i<strlen(control); i++)
        {
            if(control[i]=='.')
            {
                goto P;
            }
        }
        //don't read
        if(!strcmp(control,"output.txt") || control[strlen(control)-2]=='l' || !strcmp(control,"src") )
        {
            goto P;
        }

        strcpy(path,flag);
        strcat(path,control);
        path[strcspn(path,"\n")]=0;

        sayac=0;
        strcpy(flag2,path);
        flag2[strcspn(flag2,"\n")]=0;
        //subfile scan
        DIR* dir2=opendir(path);
        if(dir2==NULL)
        {
            goto P;
        }
        struct dirent* entitiy2;
        entitiy2=readdir(dir2);
        //finding and printing tags
        while(entitiy2!=NULL)
        {
            if(sayac<=1)
            {
                sayac++;
                goto H;
            }
            strcpy(control,entitiy2->d_name);
            if(control[strlen(control)-4]!='.' && control[strlen(control)-3]!='t')
            {
                goto H;
            }
            if((control[strlen(control)-3])=='t')
            {
                strcpy(requestArray[requestCount],control);
                requestCount++;
            }

            strcpy(path,flag2);
            strcat(path,"\\");
            strcat(path,entitiy2->d_name);
            path[strcspn(path,"\n")]=0;
            FILE *kontrol2;
            if((kontrol2=fopen(path,"r"))==0)
            {
                perror("\033[4;31mError Open File\033[0m");
            }
            else
            {
                while(fgets(backupFile,500,kontrol2)!=NULL)
                {
                    j=0;
                    for(int i=0; i<strlen(backupFile)-2; i++)
                    {
                        if(strlen(backupFile)<=1)
                            break;
                        for(; j<2; j++)
                        {
                            if(backupFile[i+j]!=searched[j])
                            {
                                j=0;
                                break;
                            }
                            else if(j==1)
                            {
                                a=j+i;
                                strcpy(tagArray[tagCount],"[[");
                                sayac=0;
                                while(1)
                                {
                                    tagArray[tagCount][m]=backupFile[a+1];
                                    sayac++;
                                    m++;
                                    a++;
                                    if(backupFile[a+1]==']' && backupFile[a+2]==']')
                                    {
                                        if(strlen(tagArray[tagCount])>m)
                                        {
                                            for(int dl=m; dl<strlen(tagArray[tagCount])+1; dl++)
                                            {
                                                tagArray[tagCount][dl]='\0';
                                            }
                                        }
                                        tagArray[tagCount][m+1]=']';
                                        tagArray[tagCount][m+2]=']';
                                        tagCount++;
                                        break;
                                    }
                                    if(backupFile[a+1]==']' && backupFile[a+2]!=']')
                                    {
                                        for(int v=0; v<strlen(tagArray[tagCount]); v++)
                                        {
                                            tagArray[tagCount][v]='\0';
                                        }
                                        m=m-1;
                                        break;
                                    }
                                }
                                m=2;
                                break;
                            }
                        }
                    }
                }
            }
            fclose(kontrol2);
H:
            entitiy2=readdir(dir2);
        }
        closedir(dir2);
P:
        entitiy=readdir(dir);
    }
    closedir(dir);

    char tagEditArray[100][100];
    printf("\033[4;33m\nTag List                                 Repetition Count\n\033[0m\n");
    int x=0;
    int rptCount[40];
    a=0;
    m=0;
    //printing tags and repetition numbers in the text
    for(i=0; i<tagCount; i++)
    {
        for(j=0; j<tagCount; j++)
        {
            if(!strcmp(tagArray[i],tagEditArray[j]))
            {
                x=1;
            }
        }
        if(x==0)
        {
            if(tagArray[i]!=" ")
            {
                strcpy(tagEditArray[a],tagArray[i]);
                a++;
            }
        }
        x=0;
    }
    for(i=0; i<a; i++)
    {
        for(j=0; j<tagCount; j++)
        {
            if(!strcmp(tagEditArray[i],tagArray[j]))
            {
                m++;
            }
        }
        rptCount[i]=m;
        m=0;
    }
    //record to output
    FILE *output;
    if((output=fopen("C:\\Users\\baran\\OneDrive\\Belgeler\\University\\output.txt","w"))==0)
    {
        perror("\033[4;31mError Open File\033[0m");
    }
    fprintf(output,"\033[4;33m\nTag List                                 Repetition Count\033[0m\n");

    FILE *searchFile;
    char controlArray[100],flag3[100];
    for(i=0; i<a; i++)
    {
        for(j=0; j<strlen(tagEditArray[i])-2; j++)
        {
            if(tagEditArray[i][j+2]==']')
                break;
            tagEditArray[i][j]=tagEditArray[i][j+2];
        }
        if(strlen(tagEditArray[i])>j-1)
        {
            for(int dl=j; j<strlen(tagEditArray[i]); dl++)
            {
                tagEditArray[i][dl]='\0';
            }
        }
    }
    for(i=0; i<a; i++)
    {
        if(i+1==a)
        {
            printf("%-36s      %15d",tagEditArray[i],rptCount[i]);
            fprintf(output,"%-36s      %15d",tagEditArray[i],rptCount[i]);
            continue;
        }
        printf("%-36s      %15d\n",tagEditArray[i],rptCount[i]);
        fprintf(output,"%-36s      %15d\n",tagEditArray[i],rptCount[i]);
    }
    for(i=0; i<a; i++)
    {
        for(j=0; j<strlen(tagEditArray[i]); j++)
        {
            if(tagEditArray[i][j]==' ')
            {
                tagEditArray[i][j]='_';
            }
        }
    }
    strcpy(controlArray,"C:\\Users\\baran\\OneDrive\\Belgeler\\University\\Lessons\\");
    strcpy(flag3,controlArray);
    printf("\033[4;33m\n_                                                       _\033[0m\n");
    printf("\033[4m\nOrphan Tags\033[0m\n");
    fprintf(output,"\nOrphan Tags\n");
    //printing oprhan tags
    for(i=0; i<a; i++)
    {
        strcpy(controlArray,flag3);
        strcat(controlArray,tagEditArray[i]);
        controlArray[strcspn(controlArray,"\n")]=0;
        strcat(controlArray,".txt");
        if((searchFile=fopen(controlArray,"r"))==0)
        {
            fprintf(output,"%s\n",tagEditArray[i]);
            printf("%s\n",tagEditArray[i]);
        }
    }
    char txtTemizleme[100][100];
    printf("\033[4m\nRequested Tags\033[0m\n");
    fprintf(output,"\nRequested Tags\n");
    //printing requested tags
    for(i=0; i<a; i++)
    {
        strcat(tagEditArray[i],".txt");
    }
    int y=0;
    x=0;
    for(i=0; i<a; i++)
    {
        for(j=0; j<strlen(tagEditArray[i]); j++)
        {
            if(tagEditArray[i][j]==' ')
            {
                tagEditArray[i][j]='_';
            }
        }
    }
    for(i=0; i<requestCount; i++)
    {
        for(j=0; j<strlen(requestArray[i]); j++)
        {
            if(requestArray[i][j]==' ')
            {
                requestArray[i][j]='_';
            }
        }
    }
    for(i=0; i<requestCount; i++)
    {
        for(j=0; j<a; j++)
        {
            if(!strcmp(requestArray[i],tagEditArray[j]))
            {
                y=1;
                break;
            }
        }
        if(y==0)
        {
            for(int k=0; k<strlen(requestArray[i])-3; k++)
            {
                if(requestArray[i][k]=='_')
                {
                    requestArray[i][k]=' ';
                }
                if(requestArray[i][k]=='.')
                    break;
                txtTemizleme[x][k]=requestArray[i][k];
            }
            printf("%s\n",txtTemizleme[x]);
            fprintf(output,"%s\n",txtTemizleme[x]);
            x++;
        }
        y=0;
    }
    fclose(searchFile);
    fclose(output);
}

void addLesson()
{
    getchar();
    int jumpNum = 0, a = 0, x = 0, rowCount = 0, newFileNum;
    char control[200], row[100][1000], flag[200], path[200];
    strcpy(flag, "C:\\Users\\baran\\OneDrive\\Belgeler\\University\\Lessons\\");
    strcpy(path, flag);
    //subfile scan
    DIR* dir = opendir(flag);
    if (dir == NULL)
    {
        return;
    }

    struct dirent* entity;
    while ((entity = readdir(dir)) != NULL)
    {
        ////two rounds of jumping
        if (jumpNum < 2)
        {
            jumpNum++;
            continue;
        }

        strcpy(control, flag);
        strcat(control, entity->d_name);
        control[strcspn(control, "\n")] = 0;

        if (control[strlen(control) - 1] != 't')
        {
            continue;
        }
        //is txt
        FILE* file;
        if ((file = fopen(control, "r")) == NULL)
        {
            continue;
        }
        fgets(row[a], 500, file);
        row[a][strcspn(row[a], "")] = 0;
        a++;
        fclose(file);
    }
    closedir(dir);

    char lesArray[40][40];
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < strlen(row[i]); j++)
        {
            if (row[i][j] >= '0' && row[i][j] <= '9')
            {
                lesArray[rowCount][x] = row[i][j];
                x++;
            }
        }
        rowCount++;
        x = 0;
    }

    int flagInt = atoi(lesArray[0]);
    for (int j = 0; j < rowCount; j++)
    {
        int num = atoi(lesArray[j]);
        if (flagInt < num)
        {
            flagInt = num;
        }
    }
    //lesson num
    if (flagInt < 199)
    {
        flagInt = 199;
    }

    newFileNum = flagInt + 1;
    int boy = snprintf(NULL, 0, "%d", newFileNum);
    char* txtNum = malloc(boy + 1);
    snprintf(txtNum, boy + 1, "%d", newFileNum);

    char newTxt[60];
    printf("Txt name:  ");
    fgets(newTxt, 60, stdin);
    newTxt[strcspn(newTxt, "\n")] = 0;

    for (int i = 0; i < strlen(newTxt); i++)
    {
        if (newTxt[i] == ' ')
        {
            newTxt[i] = '_';
        }
    }

    strcat(path, newTxt);
    strcat(path, ".txt");
    //create new txt/lesson
    FILE* newF;
    if ((newF = fopen(path, "w")) == NULL)
    {
        perror("\033[31mError creating a file\033[0m");
        free(txtNum);
        return;
    }
    else
    {
        printf("\033[32mFile created successfully\n\033[0m");
    }

    char txtContent[600];
    printf("\n\nFile Content: ");
    fgets(txtContent, 600, stdin);

    fprintf(newF, "Course Code : BLM%s\n", txtNum);
    fprintf(newF, "Course Title : %s\n\n", newTxt);
    fprintf(newF, "Course Content: %s", txtContent);

    fclose(newF);
    free(txtNum);
}

void deleteTxt(const char* path)
{
    getchar();
    char fileName[30];
    char* flag = strdup(path);
    char* fullPath = (char*)malloc((strlen(path) + 5) * sizeof(char));

A:
    printf("\n\nTxt name: ");
    fgets(fileName, 30, stdin);
    strcpy(fullPath, flag);
    strcat(fullPath, fileName);
    fullPath[strcspn(fullPath, "\n")] = '\0';
    strcat(fullPath, ".txt");

    FILE* searched = fopen(fullPath, "r");
    if (searched == NULL)
    {
        perror("\033[31mError opening a file\033[0m");
        goto A;
    }
    else
    {
        fclose(searched);
    }

    if (remove(fullPath) == 0)
    {
        printf("\033[32mTxt file successfully deleted\n\033[0m");
    }
    else
    {
        printf("\033[31mFailed to delete txt file\n\033[0m");
    }

    free(flag);
    free(fullPath);
}

void readFile(char filePath[])
{
    char* fileName = (char*)malloc(30 * sizeof(char));
    char* flag = (char*)malloc(100 * sizeof(char));
    char reader;
    getchar();
    strcpy(flag, filePath);

    while (1)
    {
        printf("\n\nFile name: ");
        fgets(fileName, 30, stdin);
        for (int i = 0; i < strlen(fileName) + 10; i++)
            printf("_");
        printf("\n\n");
        strcpy(filePath, flag);
        FILE* searched;
        snprintf(filePath + strlen(filePath), sizeof(filePath) - strlen(filePath), "%s", fileName);
        filePath[strcspn(filePath, "\n")] = '\0';
        strcat(filePath, ".txt");
        if ((searched = fopen(filePath, "r")) == NULL)
        {
            perror("\033[31mError opening a file\033[0m");
            continue;
        }
        else
        {
            while (1)
            {
                reader = getc(searched);
                printf("%c", reader);
                if (reader == EOF)
                    break;
            }
        }
        fclose(searched);
        break;
    }
    free(fileName);
    free(flag);
}

void searchInFile(const char* filePath, const char* searchedWord)
{
    FILE* aranan = fopen(filePath, "r");
    if (aranan == NULL)
    {
        perror("\033[31mError opening a file\033[0m");
        return;
    }

    int row = 1;
    char line[500];
    while (fgets(line, sizeof(line), aranan) != NULL)
    {
        char* token = strtok(line, " ");
        while (token != NULL)
        {
            if (strlen(token) == strlen(searchedWord) && strcmp(token, searchedWord) == 0)
            {
                const char* fileName = strrchr(filePath, '/');
                printf("Found the word \033[33m%s\033[0m in line \033[33m%d\033[0m of \033[33m%s\033[0m\n", searchedWord, row, fileName+1);
                break;
            }
            token = strtok(NULL, " ");
        }
        row++;
    }
    fclose(aranan);
}

void searchFilesInDirectory(const char* directoryPath, const char* searchedWord)
{
    DIR* dir = opendir(directoryPath);
    if (dir == NULL)
    {
        printf("Cannot open directory: %s\n", directoryPath);
        return;
    }

    struct dirent* entity;
    while ((entity = readdir(dir)) != NULL)
    {
        if (strcmp(entity->d_name, ".") == 0 || strcmp(entity->d_name, "..") == 0 || strcmp(entity->d_name, "src") == 0 || strcmp(entity->d_name, "output.txt") == 0)
        {
            continue;
        }

        char path[200];
        snprintf(path, sizeof(path), "%s/%s", directoryPath, entity->d_name);

        if (strstr(entity->d_name, ".txt") != NULL)
        {
            searchInFile(path, searchedWord);
        }
        else
        {
            DIR* subDir = opendir(path);
            if (subDir != NULL)
            {
                searchFilesInDirectory(path, searchedWord);
                closedir(subDir);
            }
        }
    }
    closedir(dir);
}

int main()
{
    printf("\033[1m\nWELCOME TO UNIVERSITY SYSTEM\n\033[0m\n");
Z:
    printf("\n");
    int jumpNum=0,exitNum=0;
    char selection[5],readFileName[200],flag[200],fileNames[200][200],fileNames2[200];

    strcpy(flag,"C:\\Users\\baran\\OneDrive\\Belgeler\\University");
    DIR* dir=opendir("C:\\Users\\baran\\OneDrive\\Belgeler\\University");
    if(dir==NULL)
    {
        return 1;
    }
    struct dirent* entitiy3;
    entitiy3=readdir(dir);
    while(entitiy3!=NULL)
    {
        if(jumpNum<2)
        {
            jumpNum++;
            goto F;
        }
        strcpy(readFileName,flag);
        strcat(readFileName,"\\");
        strcat(readFileName,entitiy3->d_name);
        readFileName[strcspn(readFileName,"\n")]=0;
        FILE *reader;
        if((reader=fopen(readFileName,"r"))!=0)
        {
            fclose(reader);
            goto F;
        }
        strcpy(fileNames[exitNum],entitiy3->d_name);
        exitNum++;
        printf("%d) ",exitNum);
        printf("%s\n",entitiy3->d_name);
F:
        entitiy3=readdir(dir);
    }
    closedir(dir);
    exitNum++;
    printf("%d) Exit\n",exitNum);
K:
    printf("\n");
    printf("Select Subfile: ");
    scanf("%s",&selection);

    int chsNum=atoi(selection)-1;
    if(atoi(selection)==0)
    {
        printf("\033[31mOut of range\n\033[0m");
        goto K;
    }
    else if(atoi(selection)==exitNum)
    {
        goto H;
    }
    else if(!strcmp(fileNames[chsNum],"src"))
    {
        printf("\033[31mBanned folder!\n\033[0m");
        goto K;
    }
    else if(chsNum>exitNum)
    {
        printf("\033[31mOut of range\n\033[0m");
        goto K;
    }
    printf("\n");
    strcpy(fileNames2,flag);
    strcat(fileNames2,"\\");
    strcat(fileNames2,fileNames[chsNum]);

    dir=opendir(fileNames2);
    if(dir==NULL)
    {
        return 1;
    }
    struct dirent* entitiy;
    entitiy=readdir(dir);
    jumpNum=0;
    while(entitiy!=NULL)
    {
        if(jumpNum<2)
        {
            jumpNum++;
            goto U;
        }
        printf(".  ");
        printf("%s\n",entitiy->d_name);
U:
        entitiy=readdir(dir);
    }
    closedir(dir);

    printf("\033[4m\n\nTRANSACTIONS:\033[0m\n");
    printf("\n1)Read File\n2)Change Tag\n3)Word and Tag Search\n4)Create .txt\n5)Delete .txt\n6)Back\n");
A:
    printf("\nProcess selection:");
    scanf("%s",&selection);

    switch (atoi(selection))
    {
    case 1:
        readFile(strcat(fileNames2,"\\"));
        break;
    case 2:
        changeName();
        break;
    case 3:
        printf("\033[34m\n\n\nSEARCH SYSTEM\033[0m\n");
        writeOutput();
        getchar();
        printf("\nWord to search: ");
        char searchedWord[60];
        fgets(searchedWord, sizeof(searchedWord), stdin);
        searchedWord[strcspn(searchedWord, "\n")] = '\0';

        printf("\n");
        searchFilesInDirectory("C:\\Users\\baran\\OneDrive\\Belgeler\\University", searchedWord);
        break;
    case 4:
        addLesson();
        break;
    case 5:
        deleteTxt(strcat(fileNames2,"\\"));
        break;
    case 6:
        printf("\n\n");
        goto Z;

    default:
        printf("\033[31mWrong value!!\033[0m\n");
        goto A;
    }
    printf("\033[32m\n\nYour transaction was successful\n\033[0m\n");
    goto Z;
H:
    writeOutput();
    return 0;
}
