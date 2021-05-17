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
