// structure for a process block
struct process_block_structure
{
    int* process_block;
    process_block_structure* next;
};

struct Queue
{
    process_block_structure *front, *rear;
  
    void* push(int* val)
    {
        process_block_structure* process_blk = new process_block_structure();
        process_blk->process_block = val;
        if(rear != NULL)
        {
            rear->next = process_blk;
            rear = process_blk;
         }
        else
        {
           front = rear = process_blk;  
        }
   }
    
    int* pop()
    {
        if(front==NULL)
        {
            cout<<"UNDERFLOW ERROR";
            return -1;           
        }
        else
        {
            int* val = front->process_block;
            front = front->next;
            if(front == NULL)
                rear = NULL;
            return val;
        }
    }
};
class Semaphore
{
    public:
        int value;
        Queue* queue; 
        Semaphore(int val)
        {
            value = val;
            queue = new Queue();
        }
};
    
void wait(Semaphore* sema, int* process_id)
{
  sema->value = sema->value - 1;
  if(sema->value < 0)
  {
      sema->queue->push(process_id);
      block(); 
      /*this function will block the process by using system call and will transfer it to the waiting queue
      the process will remain in the waiting queue till it is waken up by the wakeup() system calls
      this is a type of non busy waiting*/
  }
};
    
void signal(Semaphore* sema)
{
  sema.value = sema.value + 1;
  if(sema.value <= 0)
  {
  int* PID = sema.queue.pop();
  wakeup(PID);  //Using the System calls, this function will wakeup the process with the specific process id 
  }
};
