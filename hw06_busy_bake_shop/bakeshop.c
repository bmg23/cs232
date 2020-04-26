/*Busy Bake Shop 
* Author: Brian Goins
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h> 
#include <unistd.h>
#include <stdbool.h>
#include <sys/queue.h>

#define N_BAKER_THREADS 2
#define N_CUSTOMER_THREADS 10

#define N_CUSTOMERS_IN_STORE 4

#define TIME_TO_BAKE 1000000
#define TASK_TIME 1000000 


/******************************************BUFFER**************************************************/
struct thread_buffer {
    int write, read, size;
    pthread_t thread_array[N_CUSTOMERS_IN_STORE]; 
} cust_buff; 

bool buffIsFull() { 
    if((cust_buff.write + 1) % N_CUSTOMERS_IN_STORE == cust_buff.read){
        return true; 
    } else {return false; } 
}

bool buffIsEmpty() { 
    if(cust_buff.write == cust_buff.read) {
        return true; 
    } else { return false; } 
}

void moveRead() { cust_buff.read = (cust_buff.read + 1) % N_CUSTOMERS_IN_STORE; }

void moveWrite() { cust_buff.write = (cust_buff.write + 1) % N_CUSTOMERS_IN_STORE; }
/******************************************BUFFER**************************************************/

//Global variables 
sem_t sem_baker; 
sem_t sem_customer;  

int sold_loaves; 

//Bake bread, stop and help a customer if they enter
void* baker(void* arg) {
    int baked_loaves = 0; 
    while(baked_loaves < 10) {        
        sem_wait(&sem_baker);     
        //Bake bread
        ++baked_loaves;  

        usleep(TIME_TO_BAKE);       

        printf("\nJust baked bread! Total loaves today are: %d\n", baked_loaves); 

        sem_post(&sem_baker);

        usleep(TASK_TIME); 
    }

}

//Help customers in the store
void* cashier(void* arg) {
   
    while(sold_loaves < 10) {
        sem_wait(&sem_baker);
        sem_wait(&sem_customer); 


        //Get the current customer
        pthread_t customer_thread = cust_buff.thread_array[cust_buff.read]; 

        usleep(TASK_TIME); 

        //Transaction with customer   
        printf("\n**************************************\n");
        printf("Customer %ld picked up a loaf of bread.\n", customer_thread);
        printf("Customer %ld paid for loaf.\n", customer_thread);
        printf("The Baker has printed the reciept.\n"); 
        
        


        //Sell bread and let customer move out. 
        ++sold_loaves; 
        moveRead(); 

        usleep(TASK_TIME); 



        printf("Sold bread! Total sold loaves today are: %d\n", sold_loaves); 
        printf("Customer %ld has left the store.\n", customer_thread); 
        printf("**************************************\n");
        //End of transaction
 
        //pthread_cancel(customer_thread); 
     

        sem_post(&sem_customer);
        sem_post(&sem_baker);

        usleep(TASK_TIME); 
    }

}

//Allow customers to enter store
void* customer() {

    while(1) {
        sem_wait(&sem_customer); 
        if(!buffIsFull()) {         
            printf("\nCustomer %ld is getting in line.\n", pthread_self());

            //Customer gets in line
            cust_buff.thread_array[cust_buff.write] = pthread_self(); 
            moveWrite(); 

            usleep(TASK_TIME);             

            sem_post(&sem_customer);
            //Thread exits 
            break; 
        } 
        sem_post(&sem_customer); 


        usleep(TASK_TIME); 
        
    }
}


int main() {
    //Open bakery 
    printf("Brian's Bakery is open!\n"); 

    //Initalize global semaphores
    sem_init(&sem_baker, 0, 2); 
    sem_init(&sem_customer, 0, 1); 
    int sold_loaves = 0;

    //Create Baker
    pthread_t thread_baker; 
    pthread_t thread_cashier;
    
    pthread_create(&thread_baker, NULL, baker,  NULL);


    cust_buff.read = 0;
    cust_buff.write = 0;

    
    
    //Create Customers
    pthread_t thread_customers[N_CUSTOMER_THREADS]; 
    size_t i; 

    
    for(i = 0; i < 10; ++i) {
        pthread_create(&thread_customers[i], NULL, customer, NULL); 
    }


    pthread_create(&thread_cashier, NULL, cashier,  NULL); 
    
    
    // Call pthread_exit(NULL); so that the main program does not exit until all threads have exited.
    pthread_exit(NULL); 


    //Clean up
    sem_destroy(&sem_customer);
    sem_destroy(&sem_baker);

    return 0;

}
