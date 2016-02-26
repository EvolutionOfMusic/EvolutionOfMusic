#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

void handler(int sig){
  puts("signal received");
  return;
}


int main(){
  signal(SIGCONT, handler);
  puts("pausing"); 
  pause();
  puts("resuming");
  return 0;
}
