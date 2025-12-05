#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/moduleparam.h>
#include <linux/ktime.h>
#include <linux/printk.h>

#include <hello1.h>

MODULE_AUTHOR("ІО-32 Павлюк Роман");
MODULE_DESCRIPTION("Архітектура Комп'ютерів Лабораторна Робота 6 Модуль 2");
MODULE_LICENSE("Dual BSD/GPL");


static uint count = 1;
module_param(count, uint, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(count, "Скільки раз вивести повідомлення, від 0 до 5 включно");





static int __init hello_init(void)
{
    if(count > 5 && count <= 10)
    {
        pr_warn("Аргумент має бути від 1 до 5 включно\n");
    }
    else if(count == 0)
    {
        pr_warn("Аргумент має бути від 1 до 5 включно\n");
    }
    else if(count > 10)
    {
        pr_err("Аргумент має бути від 1 до 5 включно. Фатальна помилка\n");
        return -EINVAL;
    }
    else
    {
        // все нормально
    }

    uint i = 0;
    for(; i < count; i++)
    {
        print_hello();
    }

    return 0;
}

static void __exit hello_exit(void)
{
}

module_init(hello_init);
module_exit(hello_exit);
