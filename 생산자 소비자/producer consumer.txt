import threading, time, signal, sys, os, random
from queue import Queue
times=50
buffer_size=5
q=Queue(5)
cv = threading.Condition()
class Consumer(threading.Thread):
    def run(self):
        for i in range(times):
            cv.acquire()
            while q.qsize()<1:
                print('Consumer wait')
                cv.wait()
            print ('Consume :', q.get(0))
            cv.notify()
            cv.release()
            time.sleep(0.00)
class Producer(threading.Thread):
    def run(self):
        for i in range(times):
            cv.acquire()
            while q.qsize()>=buffer_size:
                print('Producer wait')
                cv.wait()
            q.put(i)
            print('produce: ', i)
            cv.notify()
            cv.release()
            time.sleep(0.00)
con= Consumer()
pro= Producer()
con.start()
pro.start()
con.join()
pro.join()
print('End')
