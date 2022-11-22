#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

pthread_mutex_t AB , BC , CD , FA ,EB ;

//A--> D
void* tache1(void* arg){
    int*  data = reinterpret_cast<int*>(arg);
    int   x    = *data;
    pthread_mutex_lock(&AB);
    printf("le metro %d passe par AB de MR1\n " , x);
    usleep(1000);
    pthread_mutex_unlock(&AB);

    pthread_mutex_lock(&BC);
    printf("le metro %d passe par BC de MR1\n  ", x);
    usleep(1000);
    pthread_mutex_unlock(&BC);

    pthread_mutex_lock(&CD);
    printf("le metro %d passe par CD de MR1\n  ", x);
    usleep(1000);
    pthread_mutex_unlock(&CD);
}

//F -->A
void* tache2(void* arg){
    int*  data = reinterpret_cast<int*>(arg);
    int   x    = *data;
    pthread_mutex_lock(&FA);
    printf("le metro %d passe par FA de MR2\n  " , x);
    usleep(1000);
    pthread_mutex_unlock(&FA);
}

// E--> B 
void* tache3(void* arg){
    int*  data = reinterpret_cast<int*>(arg);
    int   x    = *data;
    pthread_mutex_lock(&EB);
    printf("le metro %d passe par EB de MR3 \n " , x);
    usleep(1000);
    pthread_mutex_unlock(&EB);
}


int main(){
    pthread_t MR1 , MR2 , MR3 ;

    pthread_mutex_init(&AB , NULL);
    pthread_mutex_init(&BC , NULL);
    pthread_mutex_init(&CD , NULL);
    pthread_mutex_init(&FA , NULL);
    pthread_mutex_init(&EB , NULL);

    pthread_create(&MR1 , NULL , tache1 , new int(1));
    pthread_create(&MR1 , NULL , tache1 , new int(2));
    pthread_create(&MR2 , NULL , tache2 , new int(1));
    pthread_create(&MR2 , NULL , tache2 , new int(2));
    pthread_create(&MR3 , NULL , tache3 ,new int(1));

    pthread_join(MR1 , NULL) ;
    pthread_join(MR2 , NULL) ;
    pthread_join(MR3 , NULL) ;


}
