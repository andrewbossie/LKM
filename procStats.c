//Andrew Bossie
// This is a loadable kernel module that litst the process information for 
// processes who are children to a given PID

#include <linux/kernel.h> 
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/sched.h>
#include <linux/list.h>

long inp_pid = 0;
module_param(inp_pid, long, S_IRUSR | S_IWUSR);

static int procStats_init(void){

	static struct task_struct *ts;
	static struct task_struct __rcu *real_parent;
	static struct task_struct *child;
	static struct list_head *children_list;

	printk(KERN_ALERT "Loading Module");

	for_each_process(ts){					// So many nests, is there a better way to do this?
		if(ts->pid > inp_pid){
				list_for_each(children_list, &ts->children){
					printk("%-15s %8s %8s %8s %8s %8s", "PROCESS", "PID", "STATE", "PRIO", "ST_PRIO", "NORM_PRIO");
					printk("%-15s %8d %8ld %8d %8d %8d\n", ts->comm, ts->pid, ts->state, ts->prio, ts->static_prio, ts->normal_prio);
					printk("CHILD\n");
					child = list_entry(children_list, struct task_struct, sibling);
					printk("%-15s %8d %8ld %8d %8d %8d\n", child->comm, child->pid, child->state, child->prio, child->static_prio, child->normal_prio);
					printk("PARENT\n");
					printk("%-15s %8d %8ld %8d %8d %8d\n", ts->real_parent->comm, ts->real_parent->pid, ts->real_parent->state, ts->real_parent->prio, ts->real_parent->static_prio, ts->real_parent->normal_prio);
					printk("\n");
			}
		}
	}

	return 0;
}

static void procStats_exit(void){

	printk(KERN_ALERT "Unloading Module");
}

module_init(procStats_init);
module_exit(procStats_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Process Lister");
MODULE_AUTHOR("Andrew Bossie");