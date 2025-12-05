#define DEBUG

#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/moduleparam.h>
#include <linux/ktime.h>
#include <linux/printk.h>

MODULE_AUTHOR("ІО-32 Павлюк Роман");
MODULE_DESCRIPTION("Архітектура Комп'ютерів Лабораторна Робота 6 Модуль 1");
MODULE_LICENSE("Dual BSD/GPL");



struct my_list_node
{
    ktime_t time_first;
    ktime_t time_second;
    struct list_head node;
};

struct my_list
{
    struct list_head nodes;
};

static struct my_list hello_list;



int print_hello(void)
{
    struct my_list_node *node = kmalloc(sizeof(struct my_list_node), GFP_KERNEL);
    if(node == NULL) 
    {
        return -ENOMEM;
    }

    ktime_t time_first = ktime_get();
    pr_info("Hello World!\n");
    ktime_t time_second = ktime_get();

    node->time_first = time_first;
    node->time_second = time_second;

    list_add_tail(&node->node, &hello_list.nodes);

    return 0;
}


static int __init hello_init(void)
{
    INIT_LIST_HEAD(&hello_list.nodes);
    return 0;
}

static void __exit hello_exit(void)
{
    pr_debug("Вихід з модулю, початок\n");

    int i = 0;
    struct my_list_node *e, *n;

    list_for_each_entry_safe(e, n, &hello_list.nodes, node)
    {
        pr_debug("Повідомлення %d: початок - %lld, кінець - %lld, різниця - %lld (наносекунд)\n", (i + 1), e->time_first, e->time_second, e->time_second - e->time_first);
        list_del(&e->node);
        kfree(e);
        i++;
    }

    pr_debug("Вихід з модулю, кінець\n");
}

EXPORT_SYMBOL(print_hello);
module_init(hello_init);
module_exit(hello_exit);
