//Bankers Algorithm
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define NUMBER_OF_CUSTOMERS 5            /* maximum number   of processes      */
#define NUMBER_OF_RESOURCES 3             /* maximum number   of resource types*/
int currpro[5][3];     /* 3 threads , 3 resources*/
int t[5][3];       /* temp array location    */
int avail[NUMBER_OF_RESOURCES];          /*    Available[m]  =  #  resources unallocated  */
int maxi[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES]; /* Max[n][m] = max demand of processes n for resource m   */
int alloc[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES] = { {1,2,3},{3,2,1},{1,1,1},{1,1,1},{1,1,1} };  
int n[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];      /*   Need[n][m] = resources m needed by processes */
int ci= 0;             /* Need[n][m] = Max[n][m] - Allocation[n][m]     */
int cj= 0;
int ti= 5;
int tj= 3;

void *inccount(void *r1);
void *watchcount(void *r1);

pthread_mutex_t l; /*mutex id*/
pthread_cond_t count_cv;

int main(){

  long r_1 = 1 , r_2  = 2 , r_3 = 3;
srand(time(NULL));
int x1, y1;
    for(x1=0; x1<NUMBER_OF_CUSTOMERS; x1++){
      for(y1=0; y1<NUMBER_OF_RESOURCES; y1++){
        if(y1==0){
            maxi[x1][y1] = rand() % r_1 + 1;
          }
        else if(y1==1){
            maxi[x1][y1] = rand() % r_2 + 1;
          }
        else{
            maxi[x1][y1] = rand() % r_3 + 1;
          }

        }
      }
  

  pthread_t    currpro[5][3]; /*id of thread*/
  pthread_attr_t   attr;
  int  i ,  j;


    printf("Enter Resource 1: ");     /* write a prompt */
    scanf("%ld",  &r_1 );

    printf("Enter Resource 2: ");     /* write a prompt */
    scanf("%ld",  &r_2 );

    printf("Enter Resource 3: ");     /* write a prompt */
    scanf("%ld",  &r_3 );



  if(pthread_mutex_init(&l, NULL) < 0){
     perror("Pthread_mutex_init error.");
     exit(1);    
     }
  else
     //pthread_mutex_init(&mutex, NULL);
   
  pthread_cond_init(&count_cv, NULL);

    pthread_attr_init (&attr); /*get default attributes*/

  pthread_create(&currpro[0][0] , &attr, watchcount, ( void *) r_1);
  pthread_create(&currpro[1][0] , &attr, inccount, ( void *) r_2);
  pthread_create(&currpro[2][0] , &attr, inccount, ( void *) r_3);
  
  
   for (i=0; i<=ti ; i++){ 
      for(j=0;  j<=tj;j++){ 
          pthread_join (currpro[i][j],NULL);   /* wa i t  f or thread to exit*/
          }
      }
  printf("Main: waited on  %d,  %d threads.  Done.  \n", ti, tj);

  
  pthread_attr_destroy (  &attr);
  
  pthread_mutex_destroy( &l);
  pthread_cond_destroy( &count_cv);
  pthread_exit(NULL);

}

void *inccount(void *r1)
{  /*processes are running, thread of process is initalize to something <=3, each threads request up to 3 resources, when all resources are commited then next thread will have to wait (mutex goes to resource from a thread letting other threads know not to this resource)*/
  int i, j, nm, mm;
  long  id=(long)r1;

  for(i=0; i<10; i++){
      for(j=0; j<10; j++){
    n[nm][mm] = maxi[nm][mm] - alloc[i][j];
    printf("Allocation =  %d,  Need = %d \n", alloc[i][j], n[nm][mm]);
    }
    
    pthread_mutex_lock(&l);
     
	 if(ci==  NUMBER_OF_CUSTOMERS  &&  cj  ==NUMBER_OF_RESOURCES){
         pthread_cond_signal ( &count_cv);
        printf ("inc_count:  thread %ld, Need = %d . Threshold reached.  \n" ,id, n[nm][mm]);
       }
       
    printf("inc_count: thread %ld, Need = %d. Unlocking mutex.  \n" ,id, n[nm][mm]);
    pthread_mutex_unlock(&l);
    sleep(1);
    watchcount ( r1);
    }
  pthread_exit( NULL);
  watchcount (r1) ;
}

void  * watchcount ( void * r1 )
{
	
  long  id=  ( long) r1;
  int nm, mm;

  printf ( "  Start watch_count: thread %ld \n" ,id);

   while (ci <  NUMBER_OF_CUSTOMERS  &&  cj  <NUMBER_OF_RESOURCES )
  
  { 
  
  
  pthread_mutex_lock(&l);
   avail[nm] = maxi[nm][mm] - alloc[ci++][cj++];
   printf("Available   = %d\n", avail[nm]);
    pthread_cond_wait(&count_cv, &l);
   printf( "watch_count: thread %ld, available = %d .Conditional Signal Received. \n", id, avail[mm]);
    cj++ ;
   printf ( "watch_count : thread %ld ,Need now  =%d. \n" ,id, nm[ci][cj]);
  }
    pthread_mutex_unlock(&l);
    pthread_exit (NULL);
}
