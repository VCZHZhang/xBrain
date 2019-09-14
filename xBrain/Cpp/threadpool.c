#include "threadpool.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#define DEFAULT_TIME 1            /*Ĭ��ʱ��10s*/
#define MIN_WAIT_TASK_NUM 10       /*�������������������͸�������߳���*/
#define DEFAULT_THREAD_NUM 10      /*ÿ�δ��������ٵ��̸߳���*/
#define true 1
#define false 0


/*����*/
typedef struct {
   void *(*function)(void *);
   void *arg;
} threadpool_task_t;

/*�̳߳ع���*/
struct threadpool_t{
   pthread_mutex_t lock;                 /* ��ס�����ṹ�� */
   pthread_mutex_t thread_counter;       /* ����ʹ��æ�߳���ʱ���� */
   pthread_cond_t  queue_not_full;       /* ����������������в�Ϊ�� */
   pthread_cond_t  queue_not_empty;      /* ������в�Ϊ�� */

   pthread_t *threads;                   /* ����̵߳�tid,ʵ���Ͼ��ǹ������� ���� */
   pthread_t admin_tid;                  /* �������߳�tid */
   threadpool_task_t *task_queue;        /* ������� */

   /*�̳߳���Ϣ*/
   int min_thr_num;                      /* �̳߳�����С�߳��� */
   int max_thr_num;                      /* �̳߳�������߳��� */
   int live_thr_num;                     /* �̳߳��д����߳��� */
   int busy_thr_num;                     /* æ�̣߳����ڹ������߳� */
   int wait_exit_thr_num;                /* ��Ҫ���ٵ��߳��� */

   /*���������Ϣ*/
   int queue_front;                      /* ��ͷ */
   int queue_rear;                       /* ��β */
   int queue_size; 
 
   /* ���ڵ������� */
   int queue_max_size;                   /* ���������ɵ���������� */

   /*״̬*/
   int shutdown;                         /* trueΪ�ر� */
};


/*  ����ԭ��  */

/*�����̳߳�*/
threadpool_t *threadpool_create(int min_thr_num, int max_thr_num, int queue_max_size);
/*�ͷ��̳߳�*/
int threadpool_free(threadpool_t *pool);
/*�����̳߳�*/
int threadpool_destroy(threadpool_t *pool);
/*�����߳�*/
void *admin_thread(void *threadpool);
/*�߳��Ƿ����*/
int is_thread_alive(pthread_t tid);
/*�����߳�*/
void *threadpool_thread(void *threadpool);
/*���̳߳ص�������������һ������*/
int threadpool_add_task(threadpool_t *pool, void *(*function)(void *arg), void *arg);

/*           */


/*�����̳߳�*/
threadpool_t *
threadpool_create(int min_thr_num, int max_thr_num, int queue_max_size)
{
   int i;
   threadpool_t *pool = NULL;
   do
   {
      if ((pool=(threadpool_t *)malloc(sizeof(threadpool_t))) == NULL)
      {
        printf("malloc threadpool false; \n");
	break;   
      }
      /*��Ϣ��ʼ��*/
      pool->min_thr_num = min_thr_num;
      pool->max_thr_num = max_thr_num;
      pool->busy_thr_num = 0;
      pool->live_thr_num = min_thr_num;
      pool->wait_exit_thr_num = 0;
      pool->queue_front = 0;
      pool->queue_rear = 0;
      pool->queue_size = 0;
      pool->queue_max_size = queue_max_size;
      pool->shutdown = false;
   
      /*��������߳������������߳����鿪�ռ䣬��0*/
      pool->threads = (pthread_t *)malloc(sizeof(pthread_t)*max_thr_num);
      if (pool->threads == NULL)
      {
         printf("malloc threads false;\n");
	 break;
      }
      memset(pool->threads, 0, sizeof(pthread_t)*max_thr_num);

      /*���п��ռ�*/
      pool->task_queue = 
      (threadpool_task_t *)malloc(sizeof(threadpool_task_t)*queue_max_size);
      if (pool->task_queue == NULL)
      {
         printf("malloc task queue false;\n");
	 break;
      }

      /*��ʼ������������������*/
      if ( pthread_mutex_init(&(pool->lock), NULL) != 0           ||
           pthread_mutex_init(&(pool->thread_counter), NULL) !=0  || 
	   pthread_cond_init(&(pool->queue_not_empty), NULL) !=0  ||
	   pthread_cond_init(&(pool->queue_not_full), NULL) !=0)
      {
         printf("init lock or cond false;\n");
         break;
      }

      /*����min_thr_num�������߳�*/
      for (i=0; i<min_thr_num; i++)
      {
         /*poolָ��ǰ�̳߳�*/
         pthread_create(&(pool->threads[i]), NULL, threadpool_thread, (void *)pool);
	 printf("start thread 0x%x... \n", (unsigned int)pool->threads[i]);
      }
      /*�������߳�*/
      pthread_create(&(pool->admin_tid), NULL, admin_thread, (void *)pool);

      return pool;
   } while(0);

   /*�ͷ�pool�Ŀռ�*/
   threadpool_free(pool);
   return NULL;
}

/*�ͷ��̳߳�*/
int 
threadpool_free(threadpool_t *pool)
{
   if (pool == NULL)
   {
     return -1;
   }

   if (pool->task_queue)
   {
      free(pool->task_queue);
   }
   if (pool->threads)
   {
      free(pool->threads);
      pthread_mutex_lock(&(pool->lock));               /*����ס������*/
      pthread_mutex_destroy(&(pool->lock));
      pthread_mutex_lock(&(pool->thread_counter));
      pthread_mutex_destroy(&(pool->thread_counter));
      pthread_cond_destroy(&(pool->queue_not_empty));
      pthread_cond_destroy(&(pool->queue_not_full));
   }
   free(pool);
   pool = NULL;

   return 0;
}

/*�����̳߳�*/
int 
threadpool_destroy(threadpool_t *pool)
{
   int i;
   if (pool == NULL)
   {
     return -1;
   }
   pool->shutdown = true;

   /*���ٹ������߳�*/
   pthread_join(pool->admin_tid, NULL);

   //֪ͨ�����߳�ȥ��ɱ(���Լ�������Ĺ�����)
   for (i=0; i<pool->live_thr_num; i++)
   {
     pthread_cond_broadcast(&(pool->queue_not_empty));
   }

   /*�ȴ��߳̽��� ����pthread_exit Ȼ��ȴ������*/
   for (i=0; i<pool->live_thr_num; i++)
   {
     pthread_join(pool->threads[i], NULL);
   }

   threadpool_free(pool);
   return 0;
}

/*�����߳�*/
void *
admin_thread(void *threadpool)
{
   int i;
   threadpool_t *pool = (threadpool_t *)threadpool;
   while (!pool->shutdown)
   {
      printf("admin -----------------\n");
      sleep(DEFAULT_TIME);                             /*��һ��ʱ���ٹ���*/
      pthread_mutex_lock(&(pool->lock));               /*����*/ 
      int queue_size = pool->queue_size;               /*������*/
      int live_thr_num = pool->live_thr_num;           /*�����߳���*/
      pthread_mutex_unlock(&(pool->lock));             /*����*/
      
      pthread_mutex_lock(&(pool->thread_counter));
      int busy_thr_num = pool->busy_thr_num;           /*æ�߳���*/  
      pthread_mutex_unlock(&(pool->thread_counter));

      printf("admin busy live -%d--%d-\n", busy_thr_num, live_thr_num);
      /*�������߳� ʵ�������������� ��С���ڵȴ�����������������߳���С������߳���*/
      if (queue_size >= MIN_WAIT_TASK_NUM && live_thr_num <= pool->max_thr_num)
      {
         printf("admin add-----------\n");
         pthread_mutex_lock(&(pool->lock));
         int add=0;

         /*һ������ DEFAULT_THREAD_NUM ���߳�*/
	 for (i=0; i<pool->max_thr_num && add<DEFAULT_THREAD_NUM 
	     && pool->live_thr_num < pool->max_thr_num; i++)
	 {
	    if (pool->threads[i] == 0 || !is_thread_alive(pool->threads[i]))
	    {
	       pthread_create(&(pool->threads[i]), NULL, threadpool_thread, (void *)pool);
	       add++;
	       pool->live_thr_num++;
	       printf("new thread -----------------------\n");
	    }
	 }

	 pthread_mutex_unlock(&(pool->lock));
      }

      /*���ٶ�����߳� æ�߳�x2 ��С�� ����̣߳����Ҵ��Ĵ�����С�߳���*/
      if ((busy_thr_num*2) < live_thr_num  &&  live_thr_num > pool->min_thr_num)
      {
        // printf("admin busy --%d--%d----\n", busy_thr_num, live_thr_num);
         /*һ������DEFAULT_THREAD_NUM���߳�*/
	 pthread_mutex_lock(&(pool->lock));
         pool->wait_exit_thr_num = DEFAULT_THREAD_NUM;
	 pthread_mutex_unlock(&(pool->lock));

	 for (i=0; i<DEFAULT_THREAD_NUM; i++)
	 {
	    //֪ͨ���ڴ��ڿ��е��̣߳���ɱ
	    pthread_cond_signal(&(pool->queue_not_empty));
	    printf("admin cler --\n");
	 }
      }
   }
  
   return NULL;
}
/*�߳��Ƿ���*/
int 
is_thread_alive(pthread_t tid)
{
   int kill_rc = pthread_kill(tid, 0);     //����0���źţ������Ƿ���
   if (kill_rc == ESRCH)  //�̲߳�����
   {
      return false;
   }
   return true;
}

/*�����߳�*/
void *
threadpool_thread(void *threadpool)
{
  threadpool_t *pool = (threadpool_t *)threadpool;
  threadpool_task_t task;

  while (true)
  {
    pthread_mutex_lock(&(pool->lock));

    //�������������� ������в�Ϊ�� �ϣ�������������
    while ((pool->queue_size == 0) && (!pool->shutdown))
    { 
       printf("thread 0x%x is waiting \n", (unsigned int)pthread_self());
       pthread_cond_wait(&(pool->queue_not_empty), &(pool->lock));

       //�ж��Ƿ���Ҫ����߳�,��ɱ����
       if (pool->wait_exit_thr_num > 0)
       {
          pool->wait_exit_thr_num--;
          //�ж��̳߳��е��߳����Ƿ������С�߳��������������ǰ�߳�
	  if (pool->live_thr_num > pool->min_thr_num)
	  {
	    printf("thread 0x%x is exiting \n", (unsigned int)pthread_self());
	    pool->live_thr_num--;
	    pthread_mutex_unlock(&(pool->lock));
	    pthread_exit(NULL);//�����߳�
	  }
       }
    }

    //�̳߳ؿ���״̬
    if (pool->shutdown) //�ر��̳߳�
    {
       pthread_mutex_unlock(&(pool->lock));
       printf("thread 0x%x is exiting \n", (unsigned int)pthread_self());
       pthread_exit(NULL); //�߳��Լ������Լ�
    }

    //������߳̿����ó�����
    task.function = pool->task_queue[pool->queue_front].function; //���Ӳ���
    task.arg = pool->task_queue[pool->queue_front].arg;

    pool->queue_front = (pool->queue_front + 1) % pool->queue_max_size;  //���ͽṹ
    pool->queue_size--;

    //֪ͨ�������������
    pthread_cond_broadcast(&(pool->queue_not_full));
    
    //�ͷ��߳���
    pthread_mutex_unlock(&(pool->lock));
    
    //ִ�иղ�ȡ��������
    printf("thread 0x%x start working \n", (unsigned int)pthread_self());
    pthread_mutex_lock(&(pool->thread_counter));            //��סæ�̱߳���
    pool->busy_thr_num++;
    pthread_mutex_unlock(&(pool->thread_counter));

    (*(task.function))(task.arg);                           //ִ������

    //�����������
    printf("thread 0x%x end working \n", (unsigned int)pthread_self());
    pthread_mutex_lock(&(pool->thread_counter));
    pool->busy_thr_num--;
    pthread_mutex_unlock(&(pool->thread_counter));
  }

  pthread_exit(NULL);
}

/*���̳߳ص�������������һ������*/
int 
threadpool_add_task(threadpool_t *pool, void *(*function)(void *arg), void *arg)
{
   pthread_mutex_lock(&(pool->lock));

   /*�����������,����wait����*/
   while ((pool->queue_size == pool->queue_max_size) && (!pool->shutdown))
   {
      pthread_cond_wait(&(pool->queue_not_full), &(pool->lock));
   }
   /*����̳߳ش��ڹر�״̬*/
   if (pool->shutdown)
   {
      pthread_mutex_unlock(&(pool->lock));
      return -1;
   }

   /*��չ����̵߳Ļص������Ĳ���arg*/
   if (pool->task_queue[pool->queue_rear].arg != NULL)
   {
      free(pool->task_queue[pool->queue_rear].arg);
      pool->task_queue[pool->queue_rear].arg = NULL;
   }
   
   /*��������������*/
   pool->task_queue[pool->queue_rear].function = function;
   pool->task_queue[pool->queue_rear].arg = arg;
   pool->queue_rear = (pool->queue_rear + 1) % pool->queue_max_size;  /* �߼���  */
   pool->queue_size++;

   /*����������,���оͲ�Ϊ����,�����̳߳��е�һ���߳�*/
   pthread_cond_signal(&(pool->queue_not_empty));
   pthread_mutex_unlock(&(pool->lock));

   return 0;
}


