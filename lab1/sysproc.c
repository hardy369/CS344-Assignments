#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}


static char ascii_art[] = 
"   _____   \n"
"  /     \\  \n"
" | () () | \n"
"  \\  ^  /  \n"
"   |||||   \n"
"   |||||   \n";

int sys_draw(void) {
    char *buf;
    uint size;

    if (argint(1, (int*)&size) < 0 || size < sizeof(ascii_art)) {
        return -1;  // Buffer is too small or invalid size
    }
    if (argptr(0, &buf, size) < 0) {
        return -1;  // Failed to get user pointer
    }
    memmove(buf, ascii_art, sizeof(ascii_art));  // Copy ASCII art to user buffer
    return sizeof(ascii_art);  // Return number of bytes copied
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
