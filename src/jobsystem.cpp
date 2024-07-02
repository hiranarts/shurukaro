void jobQueueInit(JobQueue* queue){
    queue->tail= 0;
    queue->head= 0;
    queue->count = 0;

    queue->shutdown.store(0,std::memory_order_relaxed);
    pthread_mutex_init(&queue->mutex, NULL);
    pthread_cond_init(&queue->cv, NULL);

    //spin up threads
    for (int i = 0; i < NO_THREADS; i++){
        pthread_create(&queue->pid[i],NULL,threadSpin,queue);
    }
    printf("Spun up threads\n");
}
//get a mutex 
    //flush the queue 
    //join all threads 
    //delete threads 
    //delete job queue
void jobQueueDestroy(JobQueue* queue){
    //get a mutex
    pthread_mutex_lock(&queue->mutex);
    //broadcast the shutdown 
    queue->shutdown.store(1, std::memory_order_relaxed);
    pthread_cond_broadcast(&queue->cv);
    //flush the queue 
    //TODO: Figure out where the arguments go maybe a pre allocated array
    for (int i = queue->head; i != queue->tail; i=(i+1)%JOB_QUEUE_SIZE){
        //free(queue->jobs[i].args);
    }
    pthread_mutex_unlock(&queue->mutex);
    //join threads 
    for (int i = 0; i < NO_THREADS; i++){
        pthread_join(queue->pid[i], NULL);
    }
    pthread_mutex_destroy(&queue->mutex);
    pthread_cond_destroy(&queue->cv);
    free(queue);
}

void enqueue(JobQueue* queue, function_pointer func, void* args){
  //Lock the queue
  pthread_mutex_lock(&queue->mutex);
  if(((queue->tail + 1) % JOB_QUEUE_SIZE) == ((queue->head) % JOB_QUEUE_SIZE)){
    fprintf(stderr,"ERROR: JobQueue is overwriting HEAD\n");
  }   
  queue->jobs[queue->tail].function = func;
  //assume args is already malloced 
  queue->jobs[queue->tail].args = args;
  queue->count++;
  queue->tail = (queue->tail+1) % JOB_QUEUE_SIZE;
  //if the count was 0 and you added a job to it then wake up one of the threads 
  pthread_cond_signal(&queue->cv);
  //unlock mutex
  pthread_mutex_unlock(&queue->mutex);
}

void* threadSpin(void* args){
    JobQueue* queue = (JobQueue*)(args);
    for(;;){
        //lock mutex
        pthread_mutex_lock(&queue->mutex);
        //if the queue is empty then unlock queue ans stall
        while((queue->count == 0) && !(queue->shutdown.load(std::memory_order_relaxed))){
            printf("Stuck on wait\n");
            pthread_cond_wait(&queue->cv, &queue->mutex);
        }
        //if shutdown is initiated
        if(queue->shutdown.load(std::memory_order_relaxed)){
            printf("Thread shutting down");
            pthread_mutex_unlock(&queue->mutex);
            break;
        }
        //now you have a queue and should pop a job from the queue
        Job current_task = queue->jobs[queue->head];
        queue->head = (queue->head + 1) % JOB_QUEUE_SIZE;
        queue->count--;
        pthread_mutex_unlock(&queue->mutex);
        //run task
        current_task.function(current_task.args);	
    }
    return NULL;
}

