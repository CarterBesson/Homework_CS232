#ifndef indexPage_H
#define indexPage_H

 // ADDED FOR isalpha
#define ALPHA_SIZE (26)
#define MAX_BUFFER_SIZE 300000

struct TrieNode
{
  int letter;
  struct TrieNode* nextNode[ALPHA_SIZE];
  int count;
  int totalWordCount;
};

struct TrieNode* indexPage(const char* url, struct TrieNode* root);

int addWordOccurrence(const char* word, struct TrieNode* root);

void printTrieContents(struct TrieNode* root, char *word, int *count);

int freeTrieMemory(struct TrieNode* root);

int getText(const char* srcAddr, char* buffer, const int bufSize);

void setupNode(struct TrieNode* node);

void addWordProcess(char *arr, int bytes, struct TrieNode *root);

void removeSpaces(char *str);

#endif