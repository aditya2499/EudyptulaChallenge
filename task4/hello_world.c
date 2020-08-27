#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int helloWorld_init(void)
{
	pr_debug("Hello World!\n");
	return 0;
}

static void helloWorld_exit(void)
{
	pr_debug("exiting the module\n");
}

module_init(helloWorld_init);
module_exit(helloWorld_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aditya Bansal");
MODULE_DESCRIPTION("My first module to print hello owlrd");
MODULE_VERSION("1.00");
