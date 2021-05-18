# Starve_Free_Readers_Writers_Problem
The readers-writers problem is one of the most famous problems concerning processs synchronisation and concurrent in computer science. It is one of the most prominent problems in the field of process management. Process synchronisation is required to manage the readers and the writers so that there is no inconsistency generated. The problem relates to a dataset such as a file which is shared between more than one processes at a time. Concurrent threads of execution attempt to access the same file at the same time. The involved users or the processes can be divided into two types:
- Readers - The processes which wish to read the dataset but do not update or modify it.
- Writers - The processes which can both read and modify the shared resource, such as a file.

The following are the three variations to this problem-

### First readers–writers problem
In this case, no reader is kept waiting, if the shared resource is open for reading. This means if there is atleast one reader accessing the resource, then new readers can also enter the critical section to read that resource. If a stream of readers continuously enter to read the resource, then they can lock all potential writers and starve them. A writer will be able to access the resource only when it is releasd by the last reader. This can lead to starvation and is not a fair solution.


### Second readers–writers problem
This problem is very similar to the first case, the only thing is that now the roles are reversed. The writers are given preference over the readers. In this case, the reader cannot access the resource until the last writer exits from the critical section. This solution is based on writers preference and can lead to starvation of readers.


### Third readers–writers problem
This solution overcomes the drawbacks posed by the previous two problems. Here we develop a solution with equal fairness for readers and writers. For achieveing this, a constarint is added that no thread shall be allowed to starve. If this constraint is implemented then the operation of obtaining a lock on the shared data will always terminate in a bounded amount of time. This will avoid indefinite waiting, hence it will prevent starvation. If the semaphores use a FIFO ordering while blocking and releasing threads. Hence, in simple words we can say that if a writer arrives while some readers are accessing the resource, it will wait until the readers free the resource and only then will it modify it. Similarly, the new readers which have arrived in the meantime will have to wait.  

### Explanation for the logic behind the code
The solution that is used for making the reader-writer problem starve free requires the use of three semaphores. The following are the semaphores involved:
- `read_mutex` - This semaphore is used while updating the count of the readers in the critical section, which is represented by the integer variable `readers_in_cs`. This semaphore is only available to the reader method.
- `access_for_cs` - This semaphore is in control of either the readers or the writers. It is responsible for blocking the readers or writers if it is needed. For example, if a reader is reading, and a writer tries to enter the critical section, this semaphore will block the access for the writer until all the readers who arrived before the writer have finished reading. Similarly, if a writer is modifying the file and a reader requests access to the critical section, this semaphore blocks it and does not grant access till the writer has exited. Though, the semaphore does not block access in one case, when a reader is already reading the file/shared dataset and another reader tries to read it. There is no problem for two processes to occur concurrently if they do not modify the dataset and only read the files. The value of the `access_for_cs` semaphore gets updated in three cases. These cases are:
  - When the first reader arrives
  - When the last reader leaves the critical section
  - When any writer modifes the shared dataset/file

- `order` - The `order` semaphore is the one which helps in preserving the order in which the readers and the writers arrive. It is used at the beginning of the entry section of both the reader and writer code. The role of this semaphore is to check if a reader or writer is already waiting to get executed. If this is the case, then the incoming process gets blocked. If there is no process waiting, then access to the incoming process is granted and no new reader or writer can now access the critical section.

#### Explanation for the reader code
In the reader code, the wait methods are called for `order` and `read_mutex` semaphores. When a process already exists inside the queue, then the value of the `order` semaphore is 1 and this blocks the calling process. If the value is 0, then the value of the `order` semaphore is made 1. The `read_mutex` semaphore checks that no other process is updating the count of readers in the critical section. If `reader_in_cs` is 0, then writers are not allowed to access the critical section. The `order` and `read_mutex` semaphores are released after the count of the readers is updated. After the reader process is finished, then the `readers_in_cs` count is decreased by getting hold of the `read_mutex` semaphore. When the count of readers accessing the critical section becomes zero, the writers can be given access of the critical section.
#### Explanation for the writer code
The `order` semaphore is checked first and after checking, the writer is provided access with the `access_in_cs` semaphore. The order is preserved, hence the `order` semaphore can be released. After modifying the shared dataset/file, the writer releases the `access_in_cs` semaphore. 

### Why does this approach avoid starvation?
This solution will avoid starvation for both the readers and the writers. Let us see how starvation is avoided. The code guarantees mutual exclusion, bounded waiting and certain progress.
#### Mutual Exclusion
The `access_in_cs` semaphore guarantees mutual exclusion between both readers and writers. This semaphore ensures that only one writer can enter the critical section at a time. Though multiple readers can enter the critical section at an instance, the first reader has to request access through the `access_in_cs` semaphore so that no other writer is present in the critical section at that moment. Hence, this ensures mutual exclusion among the writers, as well as mutual exclusion between the readers and the writers.
#### Bounded Wait
As mentioned in the introduction of the third readers-writers problem, starvation for both readers and writers can be prevented if the semaphores use FIFO policy while blocking and releasing processes. The semaphore is implemented using a queue which implements the FIFO policy, hence every process has to wait for a finite amount of time before it can access the critical section. This guaranteed bounded wait for all the porcesses.
#### Progress
The readers and writers take a finite amount of time to execute the critical section. Once the readers and writers complete their required processes, they release the semaphores which allows for new readers and writers to access the critical section. Hence, this prevents any occurence of deadlock and ensure progress.

