#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/hid.h>
#include <linux/usb.h>
#include <linux/miscdevice.h>

static char *id = "a21ee7cfaff1";


static ssize_t misc_read(struct file *, char *, size_t, loff_t *);
static ssize_t misc_write(struct file *, const char *, size_t, loff_t *);

static const struct file_operations eudyptula_fileops = {
	.owner = THIS_MODULE,
	.read = misc_read,
	.write = misc_write
};

static struct miscdevice eudyptula_misc = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "eudyptula",
	.fops = &eudyptula_fileops
};

static int hello_init(void)
{
	return misc_register(&eudyptula_misc);
}

static void hello_exit(void)
{
	misc_deregister(&eudyptula_misc);
	pr_debug("exiting the module\n");
}

static ssize_t misc_read(struct file *f, char *buf, size_t count,
	loff_t *offset)
{
	return simple_read_from_buffer(buf, count, offset, id,
		strlen(id));
}

static ssize_t misc_write(struct file *f, const char *buf, size_t count,
	loff_t *offset)
{
	char msg[16] = {0};
	int ret;

	ret = simple_write_to_buffer(msg, sizeof(msg), offset, buf, count);
	if (ret < 0)
		return ret;

	if (!strncmp(msg, id, strlen(id))
		&& count - 1 == strlen(id))
		return count;

	return -EINVAL;
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aditya Bansal");
MODULE_DESCRIPTION("Misc Char Module");
MODULE_VERSION("1.00");

