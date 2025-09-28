#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct trie{
    int check;
    char desc[1000];
    struct trie *edge[26];
};

struct trie *createNewNode(){
    struct trie *newNode = (struct trie*)malloc(sizeof(struct trie));
    newNode->check = 0;
    for(int i = 0; i < 26; i++){
        newNode->edge[i] = NULL;
    }
    return newNode;
}

void insertNode(struct trie *root, char *word, char *desc){
    struct trie *curr = root;
    for(int i = 0; i < strlen(word); i++){
        if(curr->edge[word[i] - 'a'] == NULL){
            curr->edge[word[i] - 'a'] = createNewNode();
        }
        curr = curr->edge[word[i] - 'a'];
    }
    strcpy(curr->desc, desc);
    curr->check = 1;
}

bool searchWord(struct trie *root, char *findWord){
    struct trie *curr = root;
    for(int i = 0; i < strlen(findWord); i++){
        if(curr->edge[findWord[i] - 'a'] == NULL){
            return false;
        }
        curr = curr->edge[findWord[i] - 'a'];
    }
    if(curr->check == 0) return false;
    else return true;
}

bool searchPrefix(struct trie *root, char *prefix){
    struct trie *curr = root;
    for(int i = 0; i < strlen(prefix); i++){
        if(curr->edge[prefix[i] - 'a'] == NULL){
            return false;
        }
        curr = curr->edge[prefix[i] - 'a'];
    }
    return true;
}

void printAllPrefix(struct trie *root, char *prefix, char *hold, int idx){
    if (root->check == 1) {
        hold[idx] = '\0';
        printf("- %s%s\n", prefix, hold);
    }
    for (int i = 0; i < 26; i++) {
        if (root->edge[i]) {
            hold[idx] = i + 'a';
            printAllPrefix(root->edge[i], prefix, hold, idx + 1);
        }
    }
}

void printWord(struct trie *root, char *hold, int idx){
    if(root->check == 1){
        hold[idx] = '\0';
        printf("- %s\n", hold);
    }
    for(int i = 0; i < 26; i++){
        if(root->edge[i]){
            hold[idx] = 'a' + i;
            printWord(root->edge[i], hold, idx + 1);
        }
    }
}

bool checkSpace(char *word){
    for(int i = 0; i < strlen(word); i++){
        if(word[i] == ' ') return false;
    }
    return true;
}

bool checkTwoWord(char *word){
    for(int i = 1; i < (strlen(word) - 1); i++){
        if(word[i] == ' ' && isalpha(word[i - 1]) != 0 && isalpha(word[i + 1]) != 0) return true;
    }
    return false;
}

void insertSlangPage(struct trie *root){
    
    char slang[100], desc[1000];

    do{
        printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
        scanf("%[^\n]", slang); getchar();
    }while(strlen(slang) <= 1 || !checkSpace(slang));
    do{
        printf("Input a new slang word description [Must be more than 2 words]:");
        scanf("%[^\n]", desc); getchar();
    }while(!checkTwoWord(desc));

    if(searchWord(root, slang)){
        insertNode(root, slang, desc);
        puts("\nSuccessfully updated a slang word.");
    }
    else{
        insertNode(root, slang, desc);
        puts("\nSuccessfully released new slang word.");
    }
    puts("Press enter to continue...");
    getchar();
}

void searchSlangPage(struct trie *root){
    
    char slang[100];

    do{
        printf("Input a slang word to be searched [Must be more than 1 characters and contains no space]:");
        scanf("%s", slang); getchar();
    }while(strlen(slang) <= 1 || !checkSpace(slang));

    if(!searchWord(root, slang)){
        printf("\nThere is no word \"%s\" in the dictionary.\n", slang);
    }
    else{
        struct trie *curr = root;
        for(int i = 0; i < strlen(slang); i++){
            curr = curr->edge[slang[i] - 'a'];
        }
        printf("Slang word  : %s\n", slang);
        printf("Description : %s\n", curr->desc);
    }
    puts("Press enter to continue...");
    getchar();    
}

void searchPrefixPage(struct trie *root){

    char prefix[100], word[100];

    printf("Input a prefix to be searched: ");
    scanf("%s", prefix); getchar();
    if(!searchPrefix(root, prefix)){
        printf("There is no prefix \"%s\" in the dictionary.", prefix);
    }
    else{
        struct trie *curr = root;
        printf("Words starts with \"%s\":\n", prefix);
        for(int i = 0; i < strlen(prefix); i++){
            curr = curr->edge[prefix[i] - 'a'];
        }
        printAllPrefix(curr, prefix, word, 0);
    }
    puts("\nPress enter to continue...");
    getchar();    
}

bool checkNoSlang(struct trie *root){
    for(int i = 0; i < 26; i++){
        if(root->edge[i] != NULL){
            return false;
        }
    }
    return true;
}

void printAllPage(struct trie *root){
    if(checkNoSlang(root)){
        printf("There is no slang word yet in the dictionary.");
    }
    else{
        char word[100];
        puts("List of all slang words in the dictionary:");
        printWord(root, word, 0);
    }
    puts("\nPress enter to continue...");
    getchar();        
}

int main(){

    int page;
    struct trie *root = createNewNode();

    do{
        puts("\n                      BOOGLE\n");
        puts("1. Release a new slang word");
        puts("2. Search a slang word");
        puts("3. View all slang words with a certain prefix word");
        puts("4. View all slang words");
        puts("5. Exit");
        printf(">> ");
        scanf("%d", &page); getchar();
        system("cls");
        switch(page){
            case 1:
                insertSlangPage(root);
                break;
            case 2:
                searchSlangPage(root);
                break;
            case 3:
                searchPrefixPage(root);
                break;
            case 4:
                printAllPage(root);
                break;
        }
        system("cls");
    }while(page != 5);


    return 0;
}