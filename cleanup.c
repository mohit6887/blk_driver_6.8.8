#include"headers.h"
#include"declerations.h"


static void __exit cleanup(void)
{

	printk(KERN_INFO "%s: Begin.\n",__func__);
	kfree(dev);
	if(majorno> 0)
	{
		unregister_blkdev(majorno,BDDNAME);

	}
	printk(KERN_INFO "%s: End \n",__func__);

}
module_exit(cleanup);


