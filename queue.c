#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *head = malloc(sizeof(struct list_head));
    if (!head) {
        return NULL;
    }
    INIT_LIST_HEAD(head);
    return head;
}

/* Free all storage used by queue */
void q_free(struct list_head *head)
{
    if (!head)
        return;
    element_t *entry;
    element_t *safe;
    list_for_each_entry_safe (entry, safe, head, list) {
        free(entry->value);
        list_del(&entry->list);
        free(entry);
    }
    free(head);
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head)
        return false;
    element_t *ele = malloc(sizeof(element_t));
    if (!ele)
        return false;
    ele->value = strdup(s);
    if (!ele->value) {
        free(ele);
        return false;
    }
    list_add(&ele->list, head);
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head)
        return false;
    element_t *ele = malloc(sizeof(element_t));
    if (!ele)
        return false;
    ele->value = strdup(s);
    if (!ele->value) {
        free(ele);
        return false;
    }
    list_add_tail(&ele->list, head);
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head)) {
        return NULL;
    }
    element_t *ele = list_first_entry(head, element_t, list);
    list_del(&ele->list);
    if (sp && ele->value) {
        memcpy(sp, ele->value, bufsize);
        sp[bufsize - 1] = '\0';
    }
    return ele;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head)) {
        return NULL;
    }
    element_t *ele = list_last_entry(head, element_t, list);
    list_del(&ele->list);
    if (sp && ele->value) {
        memcpy(sp, ele->value, bufsize);
        sp[bufsize - 1] = '\0';
    }
    return ele;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head)
        return -1;
    int i = 0;
    struct list_head *node;
    list_for_each (node, head) {
        i++;
    }
    return i;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    if (!head || list_empty(head)) {
        return false;
    }
    struct list_head *fast = head->next;
    struct list_head *slow = head->next;
    while (fast != head && fast->next != head) {
        slow = slow->next;
        fast = fast->next->next;
    }
    list_del(slow);
    element_t *ele = list_entry(slow, element_t, list);
    free(ele->value);
    free(ele);
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    if (!head)
        return false;
    element_t *entry;
    element_t *safe;
    list_for_each_entry_safe (entry, safe, head, list) {
        if (strcmp(entry->value, safe->value) == 0) {
            element_t *ele_1;
            element_t *ele_2;
            list_for_each_entry_safe (ele_1, ele_2, &entry->list, list) {
                if (strcmp(ele_1->value, ele_2->value) != 0)
                    break;
            }
            entry->list.prev->next = &ele_2->list;
            ele_2->list.prev = entry->list.prev;
        }
    }
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    if (!head || !head->next) {
        return;
    }
    struct list_head *previous = head;
    struct list_head *current = head->next;
    while (current && current->next != head) {
        previous->next = current->next;
        previous->next->prev = previous;
        current->next = previous->next->next;
        current->prev = previous->next;
        current->prev->next = current;
        current->next->prev = current;

        previous = current;
        current = current->next;
    }
    head->next->prev = head;
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head)
{
    if (!head || !head->next) {
        return;
    }
    struct list_head *node;
    struct list_head *safe;
    list_for_each_safe (node, safe, head) {
        node->next = node->prev;
        node->prev = safe;
    }
    node = head->next;
    head->next = head->prev;
    head->prev = node;
}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend)
{
    /*
    if(!head || !list_empty(head) || head->next->next == head){
    return;
    }
    struct list_head *temp = NULL;
    struct list_head *fast = head;
    struct list_head *slow = head;
    while(fast != head && fast->next != head){
        temp = slow;
        slow = slow->next;
        fast = fast ->next ->next;
    }
    temp->next = head;
    q_sort(head, descend);
    struct list_head l;
    l.next = slow;
    q_sort(&l, descend);
    if(!descend){
        head = mergelist(head->next, slow->next, cmp_ascend);
    return;
    }else{
    head = mergelist(head->next, slow->next, cmp_descend);
    return;
    }*/
}
/*
struct list_head* mergelist(struct list_head *l1, struct list_head *l2,
int(*func)(const char *, const char *)){ struct list_head *head =
malloc(sizeof(struct list_head)); struct list_head *curr = head; element_t *one;
    element_t *two;
    while(l1 != NULL && l2 != head){
    one = list_entry(l1, element_t, list);
    two = list_entry(l2, element_t, list);
        if(func(one->value, two->value)){
            curr->next = l1;
        l1->prev = curr;
            l1 = l1->next;
        }else{
            curr->next = l2;
        l2->prev = curr;
            l2 = l2->next;
        }
        curr = curr->next;
    }
    if(l1){
        curr->next = l1;
    l1->prev = curr;
    }
    if(l2 != head){
    curr->next = l2;
        l1->prev = curr;
    }
    return curr;
}

int cmp_ascend(const char *ch1, const char *ch2){
    return strcmp(ch1, ch2);
}

int cmp_descend(const char *ch1, const char *ch2){
    return strcmp(ch2, ch1);
}
*/

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    if (!head || list_empty(head)) {
        return 0;
    }
    struct list_head *node = head->prev;
    struct list_head *previous;
    element_t *current = list_entry(node, element_t, list);
    char *ch = current->value;
    int num = q_size(head);
    while (node != head) {
        previous = node->prev;
        current = list_entry(node, element_t, list);
        if (strcmp(current->value, ch)) {
            list_del(node);
            free(node);
            num--;
        } else {
            ch = current->value;
        }
        node = previous;
    }
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return num;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    if (!head || list_empty(head)) {
        return 0;
    }
    struct list_head *node = head->prev;
    struct list_head *previous;
    element_t *current = list_entry(node, element_t, list);
    char *ch = current->value;
    int num = q_size(head);
    while (node != head) {
        previous = node->prev;
        current = list_entry(node, element_t, list);
        if (strcmp(ch, current->value)) {
            list_del(node);
            free(node);
            num--;
        } else {
            ch = current->value;
        }
        node = previous;
    }
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return num;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
