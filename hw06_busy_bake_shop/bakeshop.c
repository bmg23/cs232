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

/*****************************BUFFER STUFF******************************************************/
struct thread_buffer {
    int front, rear, size;
    pthread_t thread_array[5]; 
} customer_buffer; 

int getCount() {
    return customer_buffer.rear - customer_buffer.front; 
}

bool isEmpty() { return getCount() == 0; }
bool isFull() { return getCount() == 4; } 
/*****************************BUFFER STUFF******************************************************/

#define N_BAKER_THREADS 2
#define N_CUSTOMER_THREADS 10

#define N_CUSTOMERS_IN_STORE 5

#define TIME_TO_BAKE 1000000
#define TASK_TIME 1000000 

//Global variables 
sem_t sem_baker; 
sem_t sem_customer; 


//Global values
int baked_loaves; 
int sold_loaves;  

//Bake bread, stop and help a customer if they enter
void* baker(void* arg) {
    
    while(baked_loaves < 10) {        
        sem_wait(&sem_baker);     
        //Bake bread
        ++baked_loaves;  

          
        //Bake Time 
        usleep(TIME_TO_BAKE);       

        printf("\nJust baked bread! Total loaves today are: %d\n", baked_loaves); 

        sem_post(&sem_baker);

      
    }

    
}

//Help customers in the store
void* cashier(void* arg) {
    while(sold_loaves < 10) {
        sem_wait(&sem_baker); 
        sem_wait(&sem_customer); 

        while(baked_loaves == 0) {
            usleep(1000); 
        }

        //Get the current customer
        pthread_t tempThread; tempThread = customer_buffer.thread_array[customer_buffer.front++ % customer_buffer.size]; 
        //Task Time 
        usleep(TASK_TIME); 

        //Transaction with customer        
        printf("\nCustomer %d picked up a loaf of bread.\n", tempThread);
        printf("Customer %d paid for loaf.\n", tempThread);
        printf("The Baker has printed the reciept.\n"); 
        printf("Customer %d has left the store.\n", tempThread); 


        //Task Time 
        usleep(TASK_TIME); 



        //Sell bread and let customer move out. 
        ++sold_loaves; 
        printf("Sold bread! Total sold loaves today are: %d\n", sold_loaves); 
        customer_buffer.front = customer_buffer.front + 1; 
        
        sem_post(&sem_customer);
        sem_post(&sem_baker); 
        
         
    }

}

//Allow customers to enter store
void* customer() {
 
    sem_wait(&sem_customer); 

   
    printf("\nCustomer %d is getting in line.\n", pthread_self());

    customer_buffer.thread_array[customer_buffer.rear++ % customer_buffer.size] = pthread_self(); 
    customer_buffer.size = customer_buffer.size + 1; 
        
    
    

    sem_post(&sem_customer); 
    //Task Time 
    usleep(TASK_TIME);
}


int main() {
    //Open bakery 
    printf("Brian's Bakery is open!\n"); 

    //Initalize global semaphores
    sem_init(&sem_baker, 0, 2); 
    sem_init(&sem_customer, 0, 1); 

    customer_buffer.front = 0;
    customer_buffer.rear = 0;
    customer_buffer.size = N_CUSTOMERS_IN_STORE;
    
    
    //Create Customers
    pthread_t thread_customers[N_CUSTOMER_THREADS]; 
    size_t i; 

    
    for(i = 0; i < 10; ++i) {
        pthread_create(&thread_customers, NULL, customer, NULL); 
    }


    //Create Baker
    pthread_t thread_baker; 
    pthread_t thread_cashier;
    
    pthread_create(&thread_baker, NULL, baker,  NULL);
   

    //Initalize global vars
    baked_loaves = 0;
    sold_loaves = 0; 

 

    
    pthread_create(&thread_cashier, NULL, cashier,  NULL); 
    
    // Call pthread_exit(NULL); so that the main program does not exit until all threads have exited.
    pthread_exit(NULL); 


    //Clean up
    sem_destroy(&sem_customer);
    sem_destroy(&sem_baker);

    return 0;

}
