#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/message.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

struct
{
    long type;
    int n;
} Message;

int
main(int argc, char **argv)
{
    int msg_id = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0666);

    Message.type = 1;
    Message.n = 1;
    msgsnd(msg_id, &Message, sizeof(Message) - sizeof(Message.type), 0);

    int n = strtol(argv[1], NULL, 0);
    int max = strtol(argv[2], NULL, 0);

    for (int i = 1; i <= n; ++i) {
        if (!fork()) {
            int x;
            while (msgrcv(msg_id, &x, sizeof(x), i, 0) != -1) {
                printf("%d\n", x);
            }
            if (x == max) {
                msgctl(msg_id, IPC_RMID, 0);
                break;
            }
            Message.type = i % n + 1;
            Message.n = x + 1;
            msgsnd(msg_id, &Message, sizeof(Message) - sizeof(Message.type), 0);
        }
    }
}
