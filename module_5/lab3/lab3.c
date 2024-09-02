#include <linux/module.h>
#include <linux/configfs.h>
#include <linux/init.h>
#include <linux/tty.h>          
#include <linux/kd.h>           
#include <linux/vt.h>
#include <linux/console_struct.h>       
#include <linux/vt_kern.h>
#include <linux/timer.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chydo");
MODULE_DESCRIPTION("Module 5 lab3.");
struct timer_list my_timer;
struct tty_driver *my_driver;
static int _kbledstatus = 0;
static struct kobject *example_kobject;
static int test = 0; 
#define BLINK_DELAY   HZ/5
#define ALL_LEDS_ON   0x07
#define RESTORE_LEDS  0xFF


static ssize_t write(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
        return sprintf(buf, "%d\n", test);
}
 
static ssize_t read(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
        sscanf(buf, "%du", &test);
        return count;
}

static struct kobj_attribute ko_attr = __ATTR(test, 0660, write, read);

static void my_timer_func(struct timer_list *ptr)
{
        int *pstatus = &_kbledstatus;
        if (*pstatus == test)
                *pstatus = RESTORE_LEDS;
        else
                *pstatus = test;

        (my_driver->ops->ioctl) (vc_cons[fg_console].d->port.tty, KDSETLED, *pstatus);
        my_timer.expires = jiffies + BLINK_DELAY;
        add_timer(&my_timer);
}

static int __init kbleds_init(void)
{
        int i;
        printk(KERN_INFO "kbleds: loading\n");
        printk(KERN_INFO "kbleds: fgconsole is %x\n", fg_console);
        for (i = 0; i < MAX_NR_CONSOLES; i++) {
                if (!vc_cons[i].d)
                        break;
                printk(KERN_INFO "poet_atkm: console[%i/%i] #%i, tty %lx\n", i,
                       MAX_NR_CONSOLES, vc_cons[i].d->vc_num,
                       (unsigned long)vc_cons[i].d->port.tty);
        }
        printk(KERN_INFO "kbleds: finished scanning consoles\n");
        my_driver = vc_cons[fg_console].d->port.tty->driver;

        example_kobject = kobject_create_and_add("lab3", kernel_kobj);
        if(!example_kobject) return -ENOMEM;

        if (sysfs_create_file(example_kobject, &ko_attr.attr)) {
            printk(KERN_ERR "kbleds: failed to create file in /sys/kernel/lab3\n");
            kobject_put(example_kobject); 
            return -EINVAL;
        }

        timer_setup(&my_timer, my_timer_func, 0);
        my_timer.expires = jiffies + BLINK_DELAY;
        add_timer(&my_timer);

        return 0;
}

static void __exit kbleds_cleanup(void)
{
        printk(KERN_INFO "kbleds: unloading...\n");
        del_timer(&my_timer);
        (my_driver->ops->ioctl) (vc_cons[fg_console].d->port.tty, KDSETLED, RESTORE_LEDS);
        kobject_put(example_kobject);
}

module_init(kbleds_init);
module_exit(kbleds_cleanup);