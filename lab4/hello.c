#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/moduleparam.h>
#include <linux/ktime.h>
#include <linux/printk.h>

MODULE_AUTHOR("ІО-32 Павлюк Роман");
MODULE_DESCRIPTION("Архітектура Комп'ютерів Лабораторна Робота 4");
MODULE_LICENSE("Dual BSD/GPL");


static uint count = 1;
module_param(count, uint, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(count, "Скільки раз вивести повідомлення, від 0 до 5 включно");





struct my_list_node
{
    ktime_t time;
    struct list_head node;
};

struct my_list
{
    struct list_head nodes;
};

static struct my_list hello_list;

static int __init hello_init(void)
{
    if(count > 5 && count <= 10)
    {
        printk(KERN_EMERG "Аргумент має бути від 1 до 5 включно\n");
    }
    else if(count == 0)
    {
        printk(KERN_EMERG "Аргумент має бути від 1 до 5 включно\n");
    }
    else if(count > 10)
    {
        printk(KERN_EMERG "Аргумент має бути від 1 до 5 включно. Фатальна помилка\n");
        return -EINVAL;
    }
    else
    {
        // все нормально
    }

    INIT_LIST_HEAD(&hello_list.nodes);

    uint i = 0;
    for(; i < count; i++)
    {
        struct my_list_node *node = kmalloc(sizeof(struct my_list_node), GFP_KERNEL);
        if(node == NULL) 
        {
            return -ENOMEM;
        }
        node->time = ktime_get();
        list_add_tail(&node->node, &hello_list.nodes);

        printk(KERN_EMERG "Hello World!\n");
    }

    return 0;
}

static void __exit hello_exit(void)
{
    int i = 0;
    struct my_list_node *e, *n;

    list_for_each_entry_safe(e, n, &hello_list.nodes, node)
    {
        printk("Повідомлення %d: %lld наносекунд\n", (i + 1), e->time);
        list_del(&e->node);
        kfree(e);
        i++;
    }
}

module_init(hello_init);
module_exit(hello_exit);
