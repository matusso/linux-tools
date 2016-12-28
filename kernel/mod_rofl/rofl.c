#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/random.h>

#include <asm/uaccess.h>
MODULE_AUTHOR("Matus Bursa <burso@burso.eu>");
MODULE_DESCRIPTION("rofl - generating jokes to /dev/rofl");
MODULE_LICENSE("Beerware");
MODULE_VERSION("0.1.0");

#define MAX_SIZE 1024

static ssize_t rofl_read(struct file *, char *, size_t, loff_t *);

static const char rofl_jokes[][MAX_SIZE] = { 
	"I dreamt I was forced to eat a giant marshmallow. When I woke up, my pillow was gone.\n",
	"My dog used to chase people on a bike a lot. It got so bad, finally I had to take his bike away.\n",
	"It is so cold outside I saw a politician with his hands in his own pockets.\n"
};

static const struct file_operations rofl_fops = {
        .owner = THIS_MODULE,
        .read  = rofl_read,
};

static struct miscdevice rofl_dev = {      
        MISC_DYNAMIC_MINOR,     
        "rofl",
        &rofl_fops
};

static ssize_t rofl_read(struct file * file, char * buffer, 
                          size_t count, loff_t *ppos)
{
	int i, random_number;

	get_random_bytes(&i, sizeof(i));	
	random_number = i % (sizeof(rofl_jokes) / MAX_SIZE);
    
    size_t len = strlen(rofl_jokes[random_number]); 
    if (count < len)
		return -EINVAL;
    
    if (*ppos != 0)
        return 0;
    
    if (copy_to_user(buffer, rofl_jokes[random_number], len))
        return -EINVAL;
    
    *ppos = len;
    return len;
}

static int __init rofl_init(void)
{
        int ret = 0;   
        ret = misc_register(&rofl_dev);
        if (ret) {
                printk(KERN_ERR "Unable to register \"/dev/rofl\" device\n");
		}

        return ret;
}

static void __exit rofl_exit(void)
{
        misc_deregister(&rofl_dev);
}

module_init(rofl_init);
module_exit(rofl_exit);
