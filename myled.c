#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/delay.h>

MODULE_AUTHOR("Ryuichi Ueda & Yuuki Takahashi");
MODULE_DESCRIPTION("driver for LED control");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.1");

static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;
static volatile u32 *gpio_base = NULL;

static ssize_t led_write(struct file* filp, const char* buf, size_t count, loff_t* pos)
{
	int i;
	int num = 2000;
	char c;
	if(copy_from_user(&c, buf, sizeof(char)))
		return -EFAULT;

	//printk(KERN_INFO "receive %c\n", c);
	
	if(c == '0'){
		gpio_base[10] = 1 << 14;
		gpio_base[10] = 1 << 15;
		gpio_base[10] = 1 << 16;
		gpio_base[10] = 1 << 23;
		gpio_base[10] = 1 << 24;
		gpio_base[10] = 1 << 25;
	}else if(c == '1'){
		gpio_base[7] = 1 << 23;
		ssleep(5);
		gpio_base[10] = 1 << 23;
		for(i = 0; i < 20; i++){
			gpio_base[7] = 1 << 25;
			msleep(num);
			num = num -100;
			gpio_base[10] = 1 << 25;
			ssleep(1);
		}
	}else if(c == '2'){
		gpio_base[7] = 1 << 4;
		ssleep(1);
		gpio_base[7] = 1 << 5;
		ssleep(1);
		gpio_base[7] = 1 << 6;
		ssleep(1);

		gpio_base[10] = 1 << 4;
		gpio_base[10] = 1 << 5;
		gpio_base[10] = 1 << 6;

		gpio_base[7] = 1 << 14;
		gpio_base[7] = 1 << 15;
		gpio_base[7] = 1 << 16;

	}else if(c == '3'){
		gpio_base[10] = 1 << 23;
		gpio_base[10] = 1 << 24;
		gpio_base[7] = 1 << 25;

		ssleep(1);

		gpio_base[10] = 1 << 23;
		gpio_base[7] = 1 << 24;
		gpio_base[10] = 1 << 25;

		ssleep(1);

		gpio_base[7] = 1 << 23;
		gpio_base[10] = 1 << 24;
		gpio_base[10] = 1 << 25;

		ssleep(1);

		gpio_base[10] = 1 << 23;
		gpio_base[7] = 1 << 24;
		gpio_base[7] = 1 << 25;

		ssleep(1);

		gpio_base[7] = 1 << 23;
		gpio_base[7] = 1 << 24;
		gpio_base[10] = 1 << 25;

		ssleep(1);

		gpio_base[7] = 1 << 23;
		gpio_base[10] = 1 << 24;
		gpio_base[7] = 1 << 25;

		ssleep(1);

		gpio_base[10] = 1 << 23;
		gpio_base[7] = 1 << 24;
		gpio_base[7] = 1 << 25;

		ssleep(1);

		gpio_base[7] = 1 << 23;
		gpio_base[7] = 1 << 24;
		gpio_base[7] = 1 << 25;
	}
	return 1;
}

static ssize_t sushi_read(struct file* flip, char* buf, size_t count, loff_t* pos)
{
	int size = 0;
	char sushi[] = {'s', 'u', 's', 'h', 'i'};
	if(copy_to_user(buf + size, (const char *)sushi, sizeof(sushi))){
		printk(KERN_INFO "sushi:copy_to_user failed\n");
		return -EFAULT;
	}
	size += sizeof(sushi);
	return size;
}


static struct file_operations led_fops = {
	.owner = THIS_MODULE,
	.write = led_write,
	.read = sushi_read	
};

static int __init init_mod(void)
{
	int retval;
	retval = alloc_chrdev_region(&dev, 0, 1, "myled");
	if(retval < 0){
		printk(KERN_ERR "alloc_chrdev_region falled.\n");
		return retval;
	}

	printk(KERN_INFO "%s is loaded. major:%d\n", __FILE__, MAJOR(dev));

	cdev_init(&cdv, &led_fops);
	retval = cdev_add(&cdv, dev, 1);
	if(retval < 0){
		printk(KERN_ERR "cdev_add failed. major:%d, minor:%d\n", MAJOR(dev), MINOR(dev));
		return retval;
	}

	cls = class_create(THIS_MODULE, "myled");
	if(IS_ERR(cls)){
		printk(KERN_ERR "class_create failed.");
		return PTR_ERR(cls);
	}
	device_create(cls, NULL, dev, NULL, "myled%d", MINOR(dev));

	gpio_base = ioremap_nocache(0xfe200000, 0xA0);

	const u32 led_4 = 4;
	const u32 index_4 = led_4/10;
	const u32 shift_4 = (led_4%10)*3;
	const u32 mask_4 = ~(0x7 << shift_4);
	gpio_base[index_4] = (gpio_base[index_4] & mask_4) | (0x1 << shift_4);

	const u32 led_5 = 5;
	const u32 index_5 = led_5/10;
	const u32 shift_5 = (led_5%10)*3;
	const u32 mask_5 = ~(0x7 << shift_5);
	gpio_base[index_5] = (gpio_base[index_5] & mask_5) | (0x1 << shift_5);
	
	const u32 led_6 = 6;
	const u32 index_6 = led_6/10;
	const u32 shift_6 = (led_6%10)*3;
	const u32 mask_6 = ~(0x7 << shift_6);
	gpio_base[index_6] = (gpio_base[index_6] & mask_6) | (0x1 << shift_6);
	
	const u32 led_14 = 14;
	const u32 index_14 = led_14/10;
	const u32 shift_14 = (led_14%10)*3;
	const u32 mask_14 = ~(0x7 << shift_14);
	gpio_base[index_14] = (gpio_base[index_14] & mask_14) | (0x1 << shift_14);
	
	const u32 led_15 = 15;
	const u32 index_15 = led_15/10;
	const u32 shift_15 = (led_15%10)*3;
	const u32 mask_15 = ~(0x7 << shift_15);
	gpio_base[index_15] = (gpio_base[index_15] & mask_15) | (0x1 << shift_15);
	
	const u32 led_16 = 16;
	const u32 index_16 = led_16/10;
	const u32 shift_16 = (led_16%10)*3;
	const u32 mask_16 = ~(0x7 << shift_16);
	gpio_base[index_16] = (gpio_base[index_16] & mask_16) | (0x1 << shift_16);

	const u32 led_b = 23;
	const u32 index_b = led_b/10;
	const u32 shift_b = (led_b%10)*3;
	const u32 mask_b = ~(0x7 << shift_b);
	gpio_base[index_b] = (gpio_base[index_b] & mask_b) | (0x1 << shift_b);

	const u32 led_g = 24;
	const u32 index_g = led_g/10;
	const u32 shift_g = (led_g%10)*3;
	const u32 mask_g = ~(0x7 << shift_g);
	gpio_base[index_g] = (gpio_base[index_g] & mask_g) | (0x1 << shift_g);

	const u32 led_r = 25;
	const u32 index_r = led_r/10;
	const u32 shift_r = (led_r%10)*3;
	const u32 mask_r = ~(0x7 << shift_r);
	gpio_base[index_r] = (gpio_base[index_r] & mask_r) | (0x1 << shift_r);

	return 0;
}

static void __exit cleanup_mod(void)
{
	cdev_del(&cdv);
	device_destroy(cls, dev);
	class_destroy(cls);
	unregister_chrdev_region(dev, 1);
	printk(KERN_INFO "%s is unloaded. major:%d\n", __FILE__, MAJOR(dev));
}

module_init(init_mod);
module_exit(cleanup_mod);
