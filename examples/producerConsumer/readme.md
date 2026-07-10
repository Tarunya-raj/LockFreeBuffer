##### The Producer Consume a classic synchornization problem in Operating systems and multithreading
		1. Producer thread generates data and puts it into a shared buffer.
		2. Consumer thread takes data from th buffer and process it.
		3. Synchronization needed to avoid
			a. Poducer keep trying to add to buffer even when its full.
			b. Consumer keep trying to remove even when the buffer is empty (Busy waiting CPU cycle lost).
			c. Race conditions(Read and write at same time- undefined behaviour).


    If there is no communication between two threads there can be stale state where the producer thinks buffer is full even though the consumer might have conusmed some data,
    Also the consmer will have to keep checking for data in buffer. If the speed of producer and conusmer is different then having independent behavior will end up wsting lot of CPU cycles.

##### Producer thread generate data and place into shared buffer.  Consumer thread remove data from the shared buffer and process it. The buffer has limited capacity.
 

##### Algorithm for Producer - consumer
 
    1. Producer want to insert item
 	a. Acquire a lock for the buffer so other can't modify the critical section.
 	b. Check if the buffer is full.
 	c. if buffer full producer cant insert and it goes to sleep.
 	d. if buffer !full procer will insert item. size increases.
 	e. Notify the consumer buffer is not empty.
 	f. Release the lock once the insertion is done.
 	
    2. Consumer wants to get/consume the data from buffer.
 	a. Acquire lock for the buffer, so other thread can't modify the critical section.
 	b. Check if buffer is empty.
 	c. buffer empty consumer thread goes to sleep.
 	d. buffer in !empty remove the first element.
 	e. once consumed decrement size of buffer.
 	f. Release the lock once that element is consumed.
 	
 
