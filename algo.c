/*This program is created by Gagan.G.Saralaya on 10/2/2025 to 
act like the algorithm used in various social media sites
which involves scrolling through content.
This program tries to understand what the 
user likes and prints the liked number, 
which the user liked as much as possible. 
And often it mixes things up and prints a 
random number from time to time and checks 
if the user likes the different number. 
The program also removes the number which has been liked by the user once but
the time spent on that number is less.
Here we can associate the number as the type of content(eg- music,sports,comedy)
and using this program we can see if the user is into a certain type of content 
like music 
it also mixes things a little to see if the user is interested in some other things like sports
or comedy.
If the user likes to watch comedy content more and has stopped liking sports content
the program removes it from the liked content, now comedy is in the liked content.*/
/*
This edited program is more accurate than the previous one as 
it also recommends content from friends.
Here lets take a and b as the friends of the user and we assume
the content viwed and liked by friends a and b are 1,3,5 and 2,4,6 respectively.
If the user likes the content viewed by friends a and b, the program will save 
that specific content in the liked content.
If the user doesn't like the content viewed by friends a and b, the program will
recommend a random content.
If the user has viewed more than 3 contents and has liked more than 3 contents, the program will
recommend content from the liked content.
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int cont;
int scroll;
int timet;
int insertnum;
time_t start, end;
int favcount;
int rep;
//Prints random number
void take();
//Prints random number which is inputed from another function
int takee(int a);
//Inserts all the content into the linked list to print out the history
void insert(int data,int points);
//inserts liked content
void ins(int data,int points,int strike);
//Deletes node, but has no use in this program
void delete(int a);
//Deletes content which has more than 5 strikes
void delete2(int a);
//Inserts a strike to the number which has lost user retention
void ins_strike(int a);
//checks if strike is more than 5
void check_excess_strike(int a);
int a[]={1,3,5};
int b[]={2,4,6};
char username[50];
int prev=0;
int prev2;
void display();
void display2();
struct node{
    int data;
    int points;
    struct node *next;
};
struct node2{
    int data;
    int points;
    int strike;
    struct node2 *next;
};

struct node *head = NULL;  
struct node *tail = NULL;
struct node *newnode=NULL;
void insert(int data,int points){
    newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->points = points;
    newnode->next = NULL;
    insertnum++;
    if(head == NULL){
        head = newnode;
        tail = newnode;
        points = 0;
    }
    else{
        tail->next = newnode;
        tail = newnode;
        tail->points=points;
    }
}
struct node2 *newnode2=NULL;
struct node2 *head2 = NULL;
struct node2 *tail2 = NULL;
void ins(int data,int points,int strike){
    newnode2=(struct node2*)malloc(sizeof(struct node2));
    newnode2->data=data;
    newnode2->points=points;
    newnode2->strike=strike;
    newnode2->next=NULL;
    if(head2==NULL){
        head2=newnode2;
        tail2=newnode2;
        points=0;
    }
    else{
        tail2->next=newnode2;
        tail2=newnode2;
        tail2->points=points;
    }
}
void delete2(int a){
    struct node2 *temp2;
    temp2 = head2;
    while(temp2->next->data !=a){
        temp2=temp2->next;
    }
    if(temp2->next==head2){
        head2=temp2->next;
    }
    free(temp2);
}
void delete(int a){
    struct node *temp;
    temp = head;
    while(temp->next->data !=a){
        temp=temp->next;
    }
    if(temp->next==head){
        head=temp->next;
    }
    
    free(temp);
}
//alters strike for each node
void ins_strike(int a){
    struct node2 *temp2;
    temp2 = head2;
    while(temp2->data!=a){
        temp2 = temp2->next;
    }
    temp2->strike=temp2->strike+1;

}
void check_excess_strike(int a){
    struct node2 *temp2;
    temp2 = head2;
    while(temp2->data!=a){
        temp2 = temp2->next;
    }
    if(temp2->strike>5){
        delete2(a);
    }
}
int countnodes(struct node2 *head2){
    favcount=0;
    struct node2 *temp=head2;
    while(temp!=NULL){
        favcount++;
        temp=temp->next;
    }
    return favcount;
}
int getrandom(struct node2 *head2){
    int count=countnodes(head2);
    int a=rand()%count;
    struct node2 *temp;
    temp=head2;
    for(int i=0;i<a;i++){
        temp=temp->next;
    }
    return temp->data;
}
//displays random number and time taken
void display(){
    printf("\nHistory of content viewed by %s",username);
    struct node *temp;
    temp = head;
    while(temp != NULL){
        printf("\nC=%d",temp->data);
        printf("\tT=%d",temp->points);
        temp = temp->next;
    }
}
void case1(int x,int timet){
    int check;
    if(timet>7){

        ins(x,timet,0);
        for(int i=0;i<2;i++){
            check=takee(x);
        }
        if(check<7){
            ins_strike(x);
            take();
            check_excess_strike(x);
        }
        else{
            take();
        }
    }
    else{
        int nextcont=rand()%3;
        if(nextcont==0){//Insert friend content
            //This displays random content from friends a and b.
            int anyfriend=rand()%2;
            if(anyfriend==0){
                int a1=rand()%3;
                printf("\nFriend's content recommended");
                takee(a[a1]);
            }
            else{
                int b1=rand()%3;
                printf("\nFriend's content recommended");
                takee(b[b1]);
            }
            take();
        }
        else{
        if(rep<3){
            rep++;
            take();
        }
        else if(rep>3 && countnodes(head2)>0){
        rep=0;
        int a=getrandom(head2);
        if(a!=-1){
        case1(a,8);
        }
        }
        else{
            take();
        }
        }
    }
}
//displays liked content
void display2(){
    printf("\nLiked content");
    struct node2 *temp2;
    temp2 = head2;
    while(temp2 != NULL){
        printf("\nLiked content of %s is %d",username,temp2->data);
        printf("\nTime taken is %d",temp2->points);
        printf("\nStrike is %d",temp2->strike);
        temp2 = temp2->next;
    }
    for(int i=0;i<3;i++){
        printf("\nLiked content of a=%d",a[i]);
        printf("\nLiked content of b=%d",b[i]);
    }
}
void take(){    
    cont=rand()%12;
    printf("\nContent is %d",cont);
    int y=cont;
    printf("\nEnter 0 to scroll:");
    time(&start);
    scanf("%d",&scroll);
    time(&end);
    
    if(scroll==0){
    timet=difftime(end,start);//takes difference betwee endtime and starttime
    printf("Time taken is %d\n",timet);
    insert(y,timet);
    case1(y,timet);
    prev=timet;
    }
    else{
        display2();
        display();
        exit(0);
    }
}

int takee(int a){
    printf("\nNumber is:%d",a);
    printf("\nEnter 0 to scroll:");
    int y=a;
    time(&start);
    scanf("%d",&scroll);
    time(&end);

    if(scroll==0){
    timet=difftime(end,start);
    printf("Time taken is %d\n",timet);
    insert(y,prev);
    return timet;
}
    else{
        display2();
        display();
        exit(0);
    }
    return 0;
}

int main(){
    printf("\nWelcome to Gagan's social media site 10/2/2025\n");
    printf("-------------------------------------");
    printf("\nEnter your username:");
    scanf("%s",username);
    srand(time(0));//randomizes the random number
    take();
    return 0;
}
//Created by Gagan.G.Saralaya on 10/02/2025
//Here instead of using short form videos and photos, I have used numbers to represent the content.