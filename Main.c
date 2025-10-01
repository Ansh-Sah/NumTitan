#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct node {
    int data;
    struct node*next;
}Aizen;

void DisplayLL(Aizen* head) {
    while(head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

Aizen* Create(int data) {
    Aizen*newNode = (Aizen*)malloc(sizeof(Aizen));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

//Convertes Numbers into LL (254: 2->5->4->NULL,  but in reverse order so we can add it directly or effectively)
Aizen* Converter(const char*str) {
    Aizen *head = NULL, *end = NULL;
    int length = strlen(str);
    for(int i = length - 1; i >= 0; --i) {
        if(!isdigit((unsigned char)str[i])) //from header file 'ctype.h'
        continue;
        Aizen*newNode = Create(str[i] - '0'); //'0' is used for converting the ASCII value to int ('0'=48, '5' = 53, '5'-'0'=53-48=5)
        //Linking
        if (head == NULL) 
        head = end = newNode;
        else {
            end->next = newNode;
            end = newNode;
        }
    }
    return head;
}

Aizen* Addition(Aizen*tmp1, Aizen*tmp2) {
    Aizen *head = NULL, *end = NULL;
    int carry = 0; //like sum=14 the it will store 4 in LL and carry 1 and add in the next LL
    while(tmp1 != NULL || tmp2 != NULL || carry>0) {
        int sum = carry;
        if(tmp1) { 
            sum += tmp1->data;//Adding the current digit of the first number to sum
            tmp1 = tmp1->next; 
        }
        if(tmp2) {
            sum += tmp2->data; //Likewise above but for 2nd LL and also add the both LL because the sum updates according to the prev if codn.
            tmp2 = tmp2->next; 
        }
        Aizen*newNode = Create(sum % 10); //Creating the LL only for unit place like 24 but we are storing 4 on;y in the LL
        carry = sum / 10; //We carry forward(or updating carry) the remaing digits like from the above example (we carry forward 2)
        //Linking
        if(head == NULL) 
        head = end = newNode;
        else { 
            end->next = newNode; 
            end = newNode; 
        }
    }
    return head;
}

//For Multiplication we can use the same logic as addition but with more nested loops and more carry handling.

// Multiply a single digit with a linked list
Aizen* MultiplyDigit(Aizen *num, int digit) {
    Aizen *head = NULL, *end = NULL;
    int carry = 0;
    while(num || carry) { // loop until all digits processed and carry becomes 0
        int prod = carry + (num ? num->data *digit : 0);
        Aizen* newNode = Create(prod % 10);
        carry = prod / 10;
        if(!head) 
            head = end = newNode;
        else { 
            end->next = newNode; 
            end = newNode; 
        }
        if(num) num = num->next;
    }
    return head;
}

// Add zeros at the beginning of linked list
Aizen* Zeros(Aizen *head, int zeros) {
    for(int i = 0; i < zeros; i++) {
        Aizen *newNode = Create(0);
        newNode->next = head;
        head = newNode;
    }
    return head;
}

// Multiply two numbers represented as reversed linked lists
Aizen* Multiplication(Aizen *num1, Aizen *num2) {
    Aizen *result = Create(0); // Initialize result as 0
    Aizen *ptr2 = num2;
    int shift = 0;

    while(ptr2) {
        // Multiply num1 by current digit of num2
        Aizen* temp = MultiplyDigit(num1, ptr2->data);
        // Shift according to position
        temp = Zeros(temp, shift);
        // Add to running result using your Addition function
        result = Addition(result, temp);
        ptr2 = ptr2->next;
        shift++;
    }

    return result;
}

//For Printing the LL in reverse order
void printList(Aizen*head) {
    if(head == NULL){
        //printf("Linked List is empty.\n");
        return;
    }
    else {
    printList(head->next); //Recursion
    printf("%d", head->data);
    }
}

int main() {
    //using 'char' because we can store lacks of values in it.
    //char num1[1000001], num2[1000001]; //Static memory allocation
    char *num1 = malloc(10000 * sizeof(char)); // 10 thousand digits
    char *num2 = malloc(10000 * sizeof(char)); //Dynamically allocating memory

    printf("Enter first number: ");
    scanf(" %s", num1);
    printf("Enter second number: ");
    scanf(" %s", num2);

    Aizen*head1 = Converter(num1);
    printf("\nLinked list for number 1: ");
    DisplayLL(head1);

    Aizen*head2 = Converter(num2);
    printf("Linked list for number 2: ");
    DisplayLL(head2);

    Aizen*sum = Addition(head1, head2);
    printf("Linked list for sum: ");
    DisplayLL(sum);

    printf("\nAddition = ");
    printList(sum);
    printf("\n");

    printf("\nMultiplication = ");
    Aizen*product = Multiplication(head1, head2);
    printList(product);
    printf("\n");

    return 0;
}