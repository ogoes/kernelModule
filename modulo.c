/*
 *
 * Projeto 2
 * Sistemas Operacionais, 4º Semestre -- UTFPR-CM
 * Autores: Dennis Felipe Urtubia e Otávio Goes
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched/signal.h>
#include <linux/sched.h>
 
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Mostra informações sobre os processos e de seus filhos");
MODULE_AUTHOR("D&O"); // Dennis e Otávio


// Estrutura de um processo (PAI)
struct task_struct *task;
// Processo filho
struct task_struct *child;
// Para percorrer a lista de processos filhos
struct list_head *list;
 
static int __init initM ( void ) {
    printk(KERN_INFO "%s","Carregando o modulo\n"); // Delimitador visual
    
    for_each_process ( task ) { // para cada processo pai
        printk (KERN_INFO "\nProcesso Pai\nPiD: %d, Comando: %s, Estado: %ld", task->pid, task->comm, task->state); // Mostra o pid, comando e estado do processo pai
        list_for_each (list, &task->children) { // para cada processo filho no pai
 
            child = list_entry ( list, struct task_struct, sibling ); // declarar todas as variaveis dos filhos
     
            printk (KERN_INFO "\n\t\t\t Processo filho de %s[ %d ] PiD: %d Comando: %s Estado: %ld",task->comm, task->pid, //pid, comando e estado dos processos filhos
                child->pid, child->comm, child->state);
        }
        printk ("-----------------------------------------------------"); // Delimitador visual
    }    
     
 
    return 0;
 
}

static void  __exit exitM ( void ) {
    printk(KERN_INFO "%s","Apagando o modulo\n");
}
 
module_init(initM); // Insere o modulo
module_exit(exitM); // remove o modulo
 
