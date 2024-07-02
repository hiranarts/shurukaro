#include "shurukaro.cpp"

void work(void* args){
  int* sum = (int*)args;
  printf("args seen %d\n", *sum);  
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

int main(int argc, char** argv){
    JobQueue* queue = (JobQueue*)malloc(sizeof(JobQueue));
    jobQueueInit(queue);
    printf("Created Q\n");
    platformInit();
    int vals[300];
    for (int i = 0; i < 100; i++){
        vals[i] = i;
        enqueue(queue, work, &vals[i]);
    }

    //If user clicks exit
    Mix_FreeMusic(testMusic);
    printf("Shurring down\n");
    jobQueueDestroy(queue);
    platformDestroy();
    printf("Ending Program\n");
    return 0;
}
