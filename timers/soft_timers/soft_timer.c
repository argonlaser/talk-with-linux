#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/timer.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("argonlaser");
MODULE_DESCRIPTION("Soft timer example");

#define TIMER_DELAY (1000) // in ms
#define MAX_REPEAT (5) 
 
struct timer_list my_timer;
static int timer_cb_count = 0;

/* Soft timer callback Function */
void my_timer_callback( unsigned long data )
{
  int ret = 0;
  printk("Timer callback runnning: %d time\n", timer_cb_count );
  if (timer_cb_count == MAX_REPEAT) {
    return;
  }
  ret = mod_timer( &my_timer, jiffies + msecs_to_jiffies(TIMER_DELAY) );
  if (ret) {
    printk("Error in mod_timer\n");
    return;
  }
  timer_cb_count++;
  
}

static int __init init_soft_timer(void)
{
  int ret = 0;
  printk("Soft timer init done.\n");
  
  // my_timer.function, my_timer.data
  setup_timer( &my_timer, my_timer_callback, 0 );
 
  printk("Starting timer to fire for every 1000ms starting from  (%ld) for %d times\n", jiffies, MAX_REPEAT);
  ret = mod_timer( &my_timer, jiffies + msecs_to_jiffies(TIMER_DELAY) );
  if (ret) {
     printk("Error in mod_timer\n");
  }
 
  return 0;
}
 
static void __exit cleanup_soft_timer(void)
{
  int ret;

  /* delete timer if callback not running(timer not in use) */ 
  ret = del_timer( &my_timer );
  if (ret) printk("The timer is still in use or callback is running...\n");
 
  printk("Timer module removed\n");
}

module_init(init_soft_timer);
module_exit(cleanup_soft_timer);
