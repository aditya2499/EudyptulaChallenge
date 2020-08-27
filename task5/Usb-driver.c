#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/hid.h>
#include <linux/usb.h>

static int helloWorld_init(void)
{
	pr_debug("Hello World!\n");
	return 0;
}

static void helloWorld_exit(void)
{
	pr_debug("exiting the module\n");
}


static struct usb_device_id table[] = {
	{
		USB_INTERFACE_INFO(
			USB_INTERFACE_CLASS_HID,
			USB_INTERFACE_SUBCLASS_BOOT,
			USB_INTERFACE_PROTOCOL_KEYBOARD
		)
	},
	{ }
};

module_init(helloWorld_init);
module_exit(helloWorld_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aditya Bansal");
MODULE_DESCRIPTION("My first module to print hello owlrd");
MODULE_VERSION("1.00");
MODULE_DEVICE_TABLE(usb, table);
