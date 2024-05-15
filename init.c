#include"headers.h"
#include"declerations.h"

int majorno;
struct blkdev *dev;
char *blkdev_catalog ="blkdev1, 1024; blkdev2, 2048";

static int __init init_bdd(void)
{
	int ret, len;
	char *catalog ,*nextToken;
       printk(KERN_INFO"%s: Begin : \n ",__func__);
	majorno=MAJORNO;
 	majorno=register_blkdev(majorno,BDDNAME);
	if(majorno <=0)
	{
		pr_err("ERROR :register_blkdev() failure \n");
		return -EBUSY;
	}	

	dev=kzalloc(sizeof(struct blkdev),GFP_KERNEL);
	if(!dev)
	{
		ret=-ENOMEM;
		pr_err("ERROR: dev kzalloc failed \n");
		goto FAIL;
	}
	INIT_LIST_HEAD(&dev->link);
	len=strlen(blkdev_catalog);
	if((len<1) && (len > PAGE_SIZE))
	{
		pr_err("%s:ERROR: LINE: %d: Invalid module parameter.catalog\n",__func__,__LINE__);
		ret=-EBUSY;
		goto FAIL;

	}

	catalog =kzalloc((len+1),GFP_KERNEL);
	if(!catalog)
	{
		ret=-ENOMEM;
		pr_err("%s: ERROR: LINE-%d ; kzalloc() failure\n",__func__,__LINE__);
		goto FAIL;
	}
	strcpy(catalog,blkdev_catalog);
	nextToken=catalog;
	printk(KERN_INFO "%s: End . \n",__func__);
	return 0;
FAIL:
	printk(KERN_INFO "%s, End \n", __func__);
	return ret;

}

module_init(init_bdd);
