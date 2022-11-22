#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int nb_voit = 0;
int nb_cam = 0;
sem_t semVoit ;
sem_t passVoit ;
sem_t semCam ;
pthread_mutex_t nb_voiture ; 
pthread_mutex_t nb_camion ; 

void* tacheVoit(void *arg){
    
    sem_wait(&passVoit);
    sem_wait(&semVoit);
    pthread_mutex_lock(&nb_voiture);
        nb_voit += 1 ;
        if(nb_voit == 1 ){
            printf("------------------------\n");
            sem_wait(&semCam);
        }
    pthread_mutex_unlock(&nb_voiture);
    sem_post(&passVoit);

    //passer
    printf("la voiture passe %d \n " , nb_voit);
    
    sem_post(&semVoit);
    pthread_mutex_lock(&nb_voiture);
        nb_voit -- ;
        if(nb_voit ==  0 ){
            printf("------------------------\n");
            sem_post(&semCam);
        }
    pthread_mutex_unlock(&nb_voiture);

    

}

void* tacheCam(void *arg){

    pthread_mutex_lock(&nb_camion);
        nb_cam += 1 ;
        if(nb_cam == 1 ){
            sem_wait(&passVoit);
        }
    pthread_mutex_unlock(&nb_camion);

    sem_wait(&semCam);
    
    printf("la camion passe \n" );
    
    sem_post(&semCam);

    pthread_mutex_lock(&nb_camion);
        nb_cam -- ;
        if(nb_cam ==  0 ){
            sem_post(&passVoit);
        }
    pthread_mutex_unlock(&nb_camion);


}

int main(){

    pthread_t voit , cam ;
    sem_init(&semVoit,0,3);
    sem_init(&passVoit,0,1);
    sem_init(&semCam,0,1);
    pthread_mutex_init(&nb_voiture , NULL);
    pthread_mutex_init(&nb_camion , NULL);

    pthread_create(&voit , NULL , tacheVoit , NULL);
    pthread_create(&voit , NULL , tacheVoit , NULL);
    pthread_create(&cam , NULL , tacheCam , NULL);
    pthread_create(&voit , NULL , tacheVoit , NULL);
    pthread_create(&cam , NULL , tacheCam , NULL);
    pthread_create(&voit , NULL , tacheVoit , NULL);


    pthread_join(voit , NULL) ;
    pthread_join(cam , NULL) ;



    return 0;
}