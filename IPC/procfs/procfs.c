#include <linux/module.h>	/* Specifically, a module */
#include <linux/kernel.h>	/* We're doing kernel work */
#include <linux/proc_fs.h>	/* Necessary because we use the proc fs */
#include <asm/uaccess.h>	/* for copy_from_user */

#define PROCFS_MAX_SIZE		1024
#define PROCFS_NAME 		"argonlaser"

static struct proc_dir_entry *my_proc_file;
static char procfs_buffer[PROCFS_MAX_SIZE];

static unsigned long procfs_buffer_size = 0;

/** 
* This function is called then the /proc file is read
*
*/
int 
procfile_read(char *buffer,
       char **buffer_location,
       off_t offset, int buffer_length, int *eof, void *data)
{
 int ret;
 
 printk("procfile_read (/proc/%s) called\n", PROCFS_NAME);
 
 if (offset > 0) {
   /* we have finished to read, return 0 */
   ret  = 0;
 } else {
   /* fill the buffer, return the buffer size */
   memcpy(buffer, procfs_buffer, procfs_buffer_size);
   ret = procfs_buffer_size;
 }
 printk("Read the value %s", (char*) buffer);
 return ret;
}

/**
* This function is called with the /proc file is written
*
*/
int procfile_write(struct file *file, const char *buffer, unsigned long count,
      void *data)
{
 /* get buffer size */
 procfs_buffer_size = count;
 if (procfs_buffer_size > PROCFS_MAX_SIZE ) {
   procfs_buffer_size = PROCFS_MAX_SIZE;
 }
 
 /* write data to the buffer */
 if ( copy_from_user(procfs_buffer, buffer, procfs_buffer_size) ) {
   return -EFAULT;
 }
 printk("Size written- %ld", procfs_buffer_size);
 return procfs_buffer_size;
}

static const struct file_operations proc_file_fops = {
  .owner = THIS_MODULE,
  .write  = procfile_write,
  .read  = procfile_read,
 };

/**
*This function is called when the module is loaded
*
*/
int init_module()
{
  my_proc_file = proc_create(PROCFS_NAME, 0, NULL, &proc_file_fops);
  if(my_proc_file == NULL) {
    return -ENOMEM;
  }
   
  return 0;

 printk(KERN_INFO "/proc/%s created\n", PROCFS_NAME);	
 return 0;	/* everything is ok */
}

/**
*This function is called when the module is unloaded
*
*/
void cleanup_module()
{
 remove_proc_entry(PROCFS_NAME, NULL);
 printk(KERN_INFO "/proc/%s removed\n", PROCFS_NAME);
}

MODULE_LICENSE("GPL");