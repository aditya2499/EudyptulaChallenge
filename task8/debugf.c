#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <linux/debugfs.h>

static char *id = "a21ee7cfaff1";
static struct dentry *dir;

static ssize_t debugfs_read(struct file *, char *, size_t, loff_t *);
static ssize_t debugfs_write(struct file *, const char *, size_t, loff_t *);

static const struct file_operations debugfs_fileops = {
	.owner = THIS_MODULE,
	.read = debugfs_read,
	.write = debugfs_write
};

static int hello_init(void)
{
	debugfs_create_dir("eudyptula", NULL);

	debugfs_create_file("id", 0666, dir, NULL, &debugfs_fileops);

	return 0;
}

static void hello_exit(void)
{
	debugfs_remove_recursive(dir);
	pr_debug("exiting the module\n");
}

static ssize_t debugfs_read(struct file *f, char *buf, size_t count,
	loff_t *offset)
{
	return simple_read_from_buffer(buf, count, offset, id,
		strlen(id));
}

static ssize_t debugfs_write(struct file *f, const char *buf, size_t count,
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
MODULE_DESCRIPTION("debugfs_Module.01");
MODULE_VERSION("1.00");

