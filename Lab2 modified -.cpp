#include <stdio.h>
#include <stdlib.h>

#define MAX 5   // Size for all queues

// ---------------- Normal Queue (Patients) ----------------
int nq[MAX], frontN=-1, rearN=-1;
int isEmptyN(){ return (frontN==-1 || frontN>rearN); }
int isFullN(){ return rearN==MAX-1; }

void enqueueN(int x){
    if(isFullN()){ printf("Normal Queue Overflow! No more patients.\n"); return; }
    if(frontN==-1) frontN=0;
    nq[++rearN]=x;
    printf("Patient %d added to Normal Queue.\n",x);
}
void dequeueN(){
    if(isEmptyN()){ printf("Normal Queue Underflow! No patients waiting.\n"); return; }
    printf("Patient %d treated.\n",nq[frontN++]);
}
void displayN(){
    if(isEmptyN()){ printf("Normal Queue Empty.\n"); return; }
    printf("Patients in Normal Queue: ");
    for(int i=frontN;i<=rearN;i++) printf("%d ",nq[i]);
    printf("\n");
}

// ---------------- Circular Queue (Beds) ----------------
int cq[MAX], frontC=-1, rearC=-1;
int isEmptyC(){ return (frontC==-1); }
int isFullC(){ return ((frontC==0 && rearC==MAX-1)||(rearC+1)%MAX==frontC); }

void enqueueC(int x){
    if(isFullC()){ printf("Circular Queue Overflow! No free beds.\n"); return; }
    if(frontC==-1) frontC=0;
    rearC=(rearC+1)%MAX;
    cq[rearC]=x;
    printf("Bed %d allocated.\n",x);
}
void dequeueC(){
    if(isEmptyC()){ printf("Circular Queue Underflow! No patients to discharge.\n"); return; }
    printf("Bed %d freed.\n",cq[frontC]);
    if(frontC==rearC) frontC=rearC=-1;
    else frontC=(frontC+1)%MAX;
}
void displayC(){
    if(isEmptyC()){ printf("No beds allocated.\n"); return; }
    printf("Beds in use: ");
    int i=frontC;
    while(1){
        printf("%d ",cq[i]);
        if(i==rearC) break;
        i=(i+1)%MAX;
    }
    printf("\n");
}

// ---------------- Priority Queue (Emergency Patients) ----------------
struct P { int patient, priority; } pq[MAX];
int sizeP=0;
int isEmptyP(){ return (sizeP==0); }
int isFullP(){ return (sizeP==MAX); }

void enqueueP(int x,int p){
    if(isFullP()){ printf("Priority Queue Overflow! Too many emergencies.\n"); return; }
    if(p<1 || p>5){ printf("Invalid Priority! (1=highest, 5=lowest)\n"); return; }
    int i=sizeP++;
    while(i>0 && pq[i-1].priority>p){ pq[i]=pq[i-1]; i--; }
    pq[i].patient=x; pq[i].priority=p;
    printf("Emergency patient %d with priority %d added.\n",x,p);
}
void dequeueP(){
    if(isEmptyP()){ printf("Priority Queue Underflow! No emergency patients.\n"); return; }
    printf("Emergency patient %d treated.\n",pq[--sizeP].patient);
}
void displayP(){
    if(isEmptyP()){ printf("No emergency patients.\n"); return; }
    printf("Emergency Queue (Patient:Priority): ");
    for(int i=0;i<sizeP;i++) printf("(%d:%d) ",pq[i].patient,pq[i].priority);
    printf("\n");
}

// ---------------- Deque (Ambulances) ----------------
int dq[MAX], frontD=-1, rearD=-1;
int isEmptyD(){ return (frontD==-1); }
int isFullD(){ return ((frontD==0 && rearD==MAX-1)||(frontD==rearD+1)); }

void insertFront(int x){
    if(isFullD()){ printf("Deque Full! Cannot add ambulance.\n"); return; }
    if(frontD==-1) frontD=rearD=0;
    else if(frontD==0) frontD=MAX-1;
    else frontD--;
    dq[frontD]=x;
    printf("Ambulance %d added at front.\n",x);
}
void insertRear(int x){
    if(isFullD()){ printf("Deque Full! Cannot add ambulance.\n"); return; }
    if(frontD==-1) frontD=rearD=0;
    else if(rearD==MAX-1) rearD=0;
    else rearD++;
    dq[rearD]=x;
    printf("Ambulance %d added at rear.\n",x);
}
void deleteFront(){
    if(isEmptyD()){ printf("Deque Empty! No ambulances.\n"); return; }
    printf("Ambulance %d removed from front.\n",dq[frontD]);
    if(frontD==rearD) frontD=rearD=-1;
    else if(frontD==MAX-1) frontD=0;
    else frontD++;
}
void deleteRear(){
    if(isEmptyD()){ printf("Deque Empty! No ambulances.\n"); return; }
    printf("Ambulance %d removed from rear.\n",dq[rearD]);
    if(frontD==rearD) frontD=rearD=-1;
    else if(rearD==0) rearD=MAX-1;
    else rearD--;
}
void getFront(){
    if(isEmptyD()){ printf("Deque Empty.\n"); return; }
    printf("Front ambulance: %d\n",dq[frontD]);
}
void getRear(){
    if(isEmptyD()){ printf("Deque Empty.\n"); return; }
    printf("Rear ambulance: %d\n",dq[rearD]);
}
void displayD(){
    if(isEmptyD()){ printf("No ambulances.\n"); return; }
    printf("Ambulances in Deque: ");
    int i=frontD;
    while(1){
        printf("%d ",dq[i]);
        if(i==rearD) break;
        i=(i+1)%MAX;
    }
    printf("\n");
}

// ---------------- Main Menu ----------------
int main(){
    int type,ch,x,p;
    while(1){
        printf("\n--- Hospital Queue Menu ---\n");
        printf("1.Normal Queue (Patients)\n2.Circular Queue (Beds)\n3.Priority Queue (Emergency)\n4.Deque (Ambulances)\n5.Exit\nChoice: ");
        scanf("%d",&type);
        if(type==5) break;

        switch(type){
            case 1: // Normal Queue
                printf("1.Enqueue 2.Dequeue 3.isEmpty 4.isFull 5.Display\nChoice: ");
                scanf("%d",&ch);
                if(ch==1){ printf("Enter Patient ID: "); scanf("%d",&x); enqueueN(x); }
                else if(ch==2) dequeueN();
                else if(ch==3) printf(isEmptyN()? "Empty\n":"Not Empty\n");
                else if(ch==4) printf(isFullN()? "Full\n":"Not Full\n");
                else if(ch==5) displayN();
                else printf("Invalid!\n");
                break;

            case 2: // Circular Queue
                printf("1.Enqueue 2.Dequeue 3.isEmpty 4.isFull 5.Display\nChoice: ");
                scanf("%d",&ch);
                if(ch==1){ printf("Enter Bed No: "); scanf("%d",&x); enqueueC(x); }
                else if(ch==2) dequeueC();
                else if(ch==3) printf(isEmptyC()? "Empty\n":"Not Empty\n");
                else if(ch==4) printf(isFullC()? "Full\n":"Not Full\n");
                else if(ch==5) displayC();
                else printf("Invalid!\n");
                break;

            case 3: // Priority Queue
                printf("1.Enqueue 2.Dequeue 3.isEmpty 4.Display\nChoice: ");
                scanf("%d",&ch);
                if(ch==1){ printf("Enter Patient ID & Priority(1-5): "); scanf("%d%d",&x,&p); enqueueP(x,p); }
                else if(ch==2) dequeueP();
                else if(ch==3) printf(isEmptyP()? "Empty\n":"Not Empty\n");
                else if(ch==4) displayP();
                else printf("Invalid!\n");
                break;

            case 4: // Deque
                printf("1.InsertFront 2.InsertRear 3.DeleteFront 4.DeleteRear 5.getFront 6.getRear 7.isEmpty 8.isFull 9.Display\nChoice: ");
                scanf("%d",&ch);
                if(ch==1){ printf("Enter Ambulance ID: "); scanf("%d",&x); insertFront(x); }
                else if(ch==2){ printf("Enter Ambulance ID: "); scanf("%d",&x); insertRear(x); }
                else if(ch==3) deleteFront();
                else if(ch==4) deleteRear();
                else if(ch==5) getFront();
                else if(ch==6) getRear();
                else if(ch==7) printf(isEmptyD()? "Empty\n":"Not Empty\n");
                else if(ch==8) printf(isFullD()? "Full\n":"Not Full\n");
                else if(ch==9) displayD();
                else printf("Invalid!\n");
                break;

            default: printf("Invalid Queue Type!\n");
        }
    }
    return 0;
}

