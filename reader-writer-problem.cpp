#include <iostream>
#include <thread>
#include <mutex>
#include <semaphore.h>

using namespace std;

class ReadersWriters {
private:
    mutex mutex;
    sem_t write_mutex;
    int readers_count;

public:
    ReadersWriters() : readers_count(0) {
        sem_init(&write_mutex, 0, 1);
    }

    void start_read() {
        mutex.lock();
        readers_count++;
        if (readers_count == 1) {
            sem_wait(&write_mutex);
        }
        mutex.unlock();

        // Reading the shared resource
        cout << "Reader is reading" << endl;

        mutex.lock();
        readers_count--;
        if (readers_count == 0) {
            sem_post(&write_mutex);
        }
        mutex.unlock();
    }

    void start_write() {
        sem_wait(&write_mutex);

        // Writing to the shared resource
        cout << "Writer is writing" << endl;

        sem_post(&write_mutex);
    }
};

void reader_thread(ReadersWriters& rw, int id) {
    while (true) {
        // Reading
        rw.start_read();
        // Simulating some delay for reading
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

void writer_thread(ReadersWriters& rw, int id) {
    while (true) {
        // Writing
        rw.start_write();
        // Simulating some delay for writing
        this_thread::sleep_for(chrono::milliseconds(2000));
    }
}

int main() {
    ReadersWriters rw;

    // Creating reader threads
    thread readers[5];
    for (int i = 0; i < 5; ++i) {
        readers[i] = thread(reader_thread, ref(rw), i);
    }

    // Creating writer threads
    thread writers[2];
    for (int i = 0; i < 2; ++i) {
        writers[i] = thread(writer_thread, ref(rw), i);
    }

    // Joining threads
    for (int i = 0; i < 5; ++i) {
        readers[i].join();
    }
    for (int i = 0; i < 2; ++i) {
        writers[i].join();
    }

    return 0;
}


// #include <iostream>
// #include <semaphore.h>
// #include <pthread.h>

// using namespace std;

// void *reader(void *);
// void *writer(void *);

// int readcount = 0, writecount = 0, sh_var = 5;
// sem_t x, y, z, rsem, wsem;
// pthread_t r[3], w[2];

// void *reader(void *i)
// {
//     cout << "\n-------------------------";
//     cout << "\n\n reader-" << i << " is reading";

//     sem_wait(&z);
//     sem_wait(&rsem);
//     sem_wait(&x);
//     readcount++;
//     if (readcount == 1)
//         sem_wait(&wsem);
//     sem_post(&x);
//     sem_post(&rsem);
//     sem_post(&z);
//     cout << "\nupdated value :" << sh_var;
//     sem_wait(&x);
//     readcount--;
//     if (readcount == 0)
//         sem_post(&wsem);
//     sem_post(&x);
// }

// void *writer(void *i)
// {
//     cout << "\n\n writer-" << i << "is writing";
//     sem_wait(&y);
//     writecount++;
//     if (writecount == 1)
//         sem_wait(&rsem);
//     sem_post(&y);
//     sem_wait(&wsem);

//     sh_var = sh_var + 5;
//     sem_post(&wsem);
//     sem_wait(&y);
//     writecount--;
//     if (writecount == 0)
//         sem_post(&rsem);
//     sem_post(&y);
// }

// int main()
// {
//     sem_init(&x, 0, 1);
//     sem_init(&wsem, 0, 1);
//     sem_init(&y, 0, 1);
//     sem_init(&z, 0, 1);
//     sem_init(&rsem, 0, 1);

//     pthread_create(&r[0], NULL, reader, (void *)0);
//     pthread_create(&w[0], NULL, writer, (void *)0);
//     pthread_create(&r[1], NULL, reader, (void *)1);
//     pthread_create(&r[2], NULL, reader, (void *)2);
//     pthread_create(&r[3], NULL, reader, (void *)3);
//     pthread_create(&w[1], NULL, writer, (void *)3);
//     pthread_create(&r[4], NULL, reader, (void *)4);

//     pthread_join(r[0], NULL);
//     pthread_join(w[0], NULL);
//     pthread_join(r[1], NULL);
//     pthread_join(r[2], NULL);
//     pthread_join(r[3], NULL);
//     pthread_join(w[1], NULL);
//     pthread_join(r[4], NULL);

//     return (0);
// }
