#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("argonlaser");
MODULE_DESCRIPTION("Tasklet example");
 
char my_tasklet_data[] ="my_tasklet_function was called";
void my_tasklet_function(unsigned long data);

/* Init the bottom half */
DECLARE_TASKLET( my_tasklet, my_tasklet_function, 
         (unsigned long) &my_tasklet_data );

/* Bottom Half Function */
void my_tasklet_function( unsigned long data )
{
  printk("%s\n", (char *)data );
  return;
}

static int __init init_tasklet(void)
{
  printk("Tasklet init done.\n");
 
  /* Schedule the Bottom Half */
  tasklet_schedule(&my_tasklet); 
  printk("Tasklet schedule done.\n");
  return 0;
}
 
static void __exit cleanup_tasklet(void)
{
  /* Stop the tasklet before we exit */
  tasklet_kill(&my_tasklet);
  printk("Tasklet killed.\n");
  return;
}

module_init(init_tasklet);
module_exit(cleanup_tasklet);
