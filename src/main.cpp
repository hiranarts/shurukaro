#include "platform.cpp"
#include <stdio.h>
#include "pthread.h"
#include <atomic>
#include <mutex>
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
  int rear;//init = 0; this is the index where we add jobs
  int front;//init = 0; this is the index where we pop jobs 
  int count;//init = 0;
  pthread_mutex_t mutex;
  pthread_cond_t cv; 
};

void enqueue(JobQueue* queue, function_pointer func, void* args){
  //Lock the queue
  pthread_mutex_lock(&queue->mutex);
  queue->jobs[queue->rear].function = func;
  //assume args is already malloced 
  queue->jobs[queue->rear].args = args;
  queue->count++;
  queue->rear = (queue->rear++) % JOB_QUEUE_SIZE;
  if (queue->rear == queue->front){
	printf("ERROR jobqueu is all backed up\n");
  }
  //if the count was 0 and you added a job to it then wake up one of the threads 
  if (queue->count == 1){
	pthread_cond_signal(&queue->cv);
  }
}

void* threadSpin(void* args){
  //first check if the queue is empty
  JobQueue* queue = (JobQueue*)args;
  for(;;){
	//lock the mutex
	pthread_mutex_lock(&queue->mutex);
	//if the queue is empty
	while(queue->count == 0){
	  //Wait for a signal from the queue, also unlock the mutex and retrieve it when we get a signal
	  pthread_cond_wait(&queue->cv, &queue->mutex);
	}
	//get the job
	Job current_task = queue->jobs[queue->front];
	queue->front = (queue->front + 1) % JOB_QUEUE_SIZE;
	queue->count--;
	//unlock queue
	pthread_mutex_unlock(&queue->mutex);
	//work the job
	current_task.function(current_task.args);
  }
  return NULL;
}
int main(int argc, char** argv){
  pthread_t pid[NO_THREADS];
    platformInit();
	
    bool running = true;
    while(running){

	  SDL_Event event;
	  while(SDL_PollEvent(&event)){
		switch(event.type){
                case SDL_QUIT:
                    running = false;
                    break;

                default:
                    break;
            }
        }

        SDL_SetRenderDrawColor(RENDERER, 0, 255, 255, 255);
        SDL_RenderClear(RENDERER);

        SDL_RenderPresent(RENDERER);
    }

	Mix_FreeMusic(testMusic);
	platformDestroy();
    return 0;
}
