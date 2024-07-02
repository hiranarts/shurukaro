#pragma once
//TODO move this to the platform layer
#define JOB_QUEUE_SIZE 256
#define NO_THREADS 4

typedef void (*function_pointer)(void*);

struct Job{
  // This is the pointer to the actual function
  function_pointer function;
  //This is a malloced argument to the function pointer
  void* args;
};

struct JobQueue{
    Job jobs[JOB_QUEUE_SIZE];
    int tail;//init = -1; this is the index where we add jobs
    int head;//init = 0; this is the index where we pop jobs 
    int count;//init = 0;
    pthread_mutex_t mutex;
    pthread_cond_t cv; 
    pthread_t pid[NO_THREADS];
    std::atomic<int> shutdown; 
};

/* Initialize and spin up threads */
void jobQueueInit(JobQueue* queue);
/* Join and destroy threads as well as destroy queue, used when shutting down program */
void jobQueueDestroy(JobQueue* queue);
/* Function that pulls jobs off the queue, only used by threads */
void* threadSpin(void* args);
/* Add jobs on the queue, the args should be malloced before hand */
void enqueue(JobQueue* queue, function_pointer func, void* args);
