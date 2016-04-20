#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// The maximum length of Huffman Code
#define MAX_TREE_HT 16
// The maximum number of distinct characters in the message
#define MAX_CHARS 128
// The maximum length of a message (both encoded and decoded)
#define MAX_MSG_LEN 512
// The following node represents a node in the Huffman tree
struct HuffmanTreeNode
{
char data; // One of the input characters
unsigned freq; // Frequency of the character
struct HuffmanTreeNode *left, *right; // Left and right child of this node
};
// Collection of Huffman tree nodes organized in Min Heap
struct MinHeap
{
unsigned size; // Current size of min heap
unsigned capacity; // capacity of min heap
struct HuffmanTreeNode **array; // Array of minheap node pointers
};
/// Huffman Code of one letter
struct HuffmanCodeOfOneLetter
{
char letter;
char code[MAX_TREE_HT];
};
//Collections of letters and their Huffman Codes
struct HuffmanCodes
{
unsigned count; // number of valid entries in the following array
struct HuffmanCodeOfOneLetter info[MAX_CHARS];
};
struct MinHeap* createMinHeap(unsigned capacity) //allocates memory for
minheap
{
struct MinHeap* minHeap =
(struct MinHeap*) malloc(sizeof(struct MinHeap));
minHeap->size = 0; // current size is 0
minHeap->capacity = capacity;minHeap->array =
(struct HuffmanTreeNode**)malloc(minHeap->capacity *
sizeof(struct HuffmanTreeNode*));
return minHeap;
}
void swapHuffmanTreeNode(struct HuffmanTreeNode** a, struct
HuffmanTreeNode** b)
{
struct HuffmanTreeNode* t = *a;
*a = *b;
*b = t;
}
void minHeapify(struct MinHeap* minHeap, int idx)
{
int smallest = idx;
int left = 2 * idx + 1;
int right = 2 * idx + 2;
if (left < minHeap->size &&
minHeap->array[left]->freq < minHeap->array[smallest]-
>freq)
smallest = left;
if (right < minHeap->size &&
minHeap->array[right]->freq < minHeap->array[smallest]-
>freq)
smallest = right;
if (smallest != idx)
{
swapHuffmanTreeNode(&minHeap->array[smallest], &minHeap-
>array[idx]);
minHeapify(minHeap, smallest);
}
}
struct HuffmanTreeNode* extractMin(struct MinHeap* minHeap)
{
struct HuffmanTreeNode* temp = minHeap->array[0];
minHeap->array[0] = minHeap->array[minHeap->size - 1];
--minHeap->size;
minHeapify(minHeap, 0);
return temp;
}
void insertMinHeap(struct MinHeap* minHeap, struct HuffmanTreeNode* hfn)
{
++minHeap->size;
int i = minHeap->size - 1;
while (i && hfn->freq < minHeap->array[(i - 1)/2]->freq)
{
minHeap->array[i] = minHeap->array[(i - 1)/2]; //exchange of
pointers
i = (i - 1)/2;
}
minHeap->array[i] = hfn;}
void deleteHuffmanTreeNode(struct HuffmanTreeNode* root)
{
if (root != NULL) {
if (root->left != NULL) {
deleteHuffmanTreeNode(root->left);
}
if (root->right != NULL) {
deleteHuffmanTreeNode(root->right);
}
free(root);
}
}
void deleteMinHeap(struct MinHeap *minHeap)
{
int i;
if (minHeap != NULL) {
for (i=0; i<minHeap->size; i++) {
deleteHuffmanTreeNode(minHeap->array[i]);
}
free(minHeap->array);
free(minHeap);
}
}
int isSizeOne(struct MinHeap* minHeap)
{
return (minHeap->size == 1);
}
struct HuffmanTreeNode* newHuffmanTreeNode(char data, unsigned freq)
{
struct HuffmanTreeNode* temp =
(struct HuffmanTreeNode*) malloc(sizeof(struct
HuffmanTreeNode));
temp->left = temp->right = NULL;
temp->data = data;
temp->freq = freq;
return temp;
}
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size)
{
int i;
struct HuffmanTreeNode *tmp;
struct MinHeap* minHeap = createMinHeap(size);
for (i = 0; i < size; ++i) {
tmp = newHuffmanTreeNode(data[i], freq[i]);
insertMinHeap(minHeap, tmp);
}
return minHeap;
}struct HuffmanTreeNode* buildHuffmanTree(char data[], int freq[], int size)
{
struct HuffmanTreeNode *left, *right, *top;
// Step 1: Create a min heap of capacity equal to size. Initially, there are
// nodes equal to size.
struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);
// Iterate while size of heap doesn't become 1
while (!isSizeOne(minHeap))
{
// Step 2: Extract the two minimum freq items from min heap
left = extractMin(minHeap);
right = extractMin(minHeap);
// Step 3: Create a new internal node with frequency equal to the
// sum of the two nodes frequencies. Make the two extracted node
as
// left and right children of this new node. Add this node to the min
heap
// '$' is a special value for internal nodes, not used
top = newHuffmanTreeNode('$', left->freq + right->freq);
top->left = left;
top->right = right;
insertMinHeap(minHeap, top);
}
// Step 4: The remaining node is the root node and the tree is complete.
top = extractMin(minHeap);
deleteMinHeap(minHeap);
return top;
}
void addHuffmanCode(struct HuffmanCodes *hf, char c, char code[])
{
if (hf != NULL) {
hf->info[hf->count].letter = c;
strcpy(hf->info[hf->count].code, code);
hf->count++;
}
}
int isLeaf(struct HuffmanTreeNode* root)
{
if(root-> left == NULL && root->right == NULL)
return 1;
else
return 0;
}
void printCodes(struct HuffmanTreeNode* root, struct HuffmanCodes *phf, char
arr[], int top)
{
// Assign 0 to left edge and recurif (root->left)
{
arr[top] = '0';
printCodes(root->left, phf, arr, top + 1);
}
// Assign 1 to right edge and recur
if (root->right)
{
arr[top] = '1';
printCodes(root->right, phf, arr, top + 1);
}
// If this is a leaf node, then it contains one of the input
// characters, print the character and its code from arr[]
if (isLeaf(root))
{
arr[top] = '\0';
printf("%c: %s\n", root->data, arr);
addHuffmanCode(phf, root->data, arr);
}
}
void printHuffmanCode(struct HuffmanCodes *hf, char c)
{
int i = 0;
if (hf != NULL) {
while (i < hf->count) {
if (hf->info[i].letter == c) {
printf("%s", hf->info[i].code);
break;
}
i++;
}
}
}
void printEncoding(char msg[], struct HuffmanCodes *phf)
{
int i = 0;
while (msg[i] != '\0') {
printHuffmanCode(phf, msg[i]);
i++;
}
printf("\n");
}
void printDecoding(char msg[], struct HuffmanTreeNode *root)
{
struct HuffmanTreeNode *nd = root;
if (msg == NULL) return;
if (*msg == '\0') return;
if (isLeaf(root)) return;
while (!(isLeaf(nd))) {if (*msg == '0') {
nd = nd->left;
} else if (*msg == '1') {
nd = nd->right;
} else {
printf(" ... Error encounted, the encoded string string is not
well formed ... Aborting!!!\n\n");
return;
}
msg++;
}
printf("%c", nd->data);
printDecoding(msg, root);
}
int main()
{
char arr[MAX_CHARS];
int freq[MAX_CHARS];
char msg[MAX_MSG_LEN];
char encmsg[MAX_MSG_LEN];
int size, i;
int ch, ch1;
char code[MAX_TREE_HT];
int top = 0;
struct HuffmanTreeNode* root;
struct HuffmanCodes hf;
do
{
printf("\nChoose from the following:\n");
printf("1. Enter a alphabets and their frequencies\n2. Exit\n");
printf("\nEnter choice: ");
scanf(" %d", &ch);//gets(ch);
fflush(stdin);
switch (ch)
{
case 1:
printf("\nEnter no of alphabets:\n");
scanf("%d",&size);
printf("Enter alphabets : ");
for (i=0; i<size; i++)
{
scanf(" %c", &arr[i] ) ;
}
fflush(stdin);
printf("Enter frequencies: ");
for (i=0; i<size; i++)
{
scanf("%d", &freq[i]) ;
}
printf("\nHuffman Code of letters -->\n");
root = buildHuffmanTree(arr, freq, size);
hf.count = 0;
printCodes(root, &hf, code, top);
fflush(stdin);do{
printf("\nOperations\n");
printf("1. Encoding \n2. Decode\n3. Exit\n");
printf("\nEnter choice: ");
scanf(" %d", &ch1);
switch (ch1)
{
case 1:
printf("\nEnter message for encoding:");
scanf("%s",msg);
printf("\nMessage Encoding :\n");
printEncoding(msg, &hf);
break;
case 2: printf("\nEnter a huffman code to decode:");
scanf("%s",encmsg);
printDecoding(encmsg, root);
printf("\n");
break;
case 3: break;
}
}while(ch1 !=3);
break;
case 2:
deleteHuffmanTreeNode(root);
break;
default: printf("Invalid choice ... Try again\n");
break;
}
} while (ch!= 2);
return 0;
}
