#include <stdbool.h>
typedef struct {
    list_ele_t *head; 
    list_ele_t *tail;
    size_t size;


} queue_t;
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));

    if (q != NULL) {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    }
    return q;
}
void q_free(queue_t *q)
{

    list_ele_t *tmp;
    if (!q)
        return;
    while (q->head) {
        tmp = q->head->next;

        free(q->head->value);
        free(q->head);
        q->head = tmp;
    }
    free(q);
}
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    if (!q)
        return false;
    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;
    newh->value = malloc(strlen(s) + 1);
    if (!newh->value) {
        free(newh);
        return false;
    }
    strcpy(newh->value, s);
    if (q->head == NULL) {
        q->tail = newh;
    }
    newh->next = q->head;
    q->head = newh;
    q->size++;
    return true;
}
bool q_insert_tail(queue_t *q, char *s)
{
    
    if (!q)
        return false;
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (!newh) {
        return false;
    }
    newh->value = malloc(strlen(s) + 1);
    if (!newh->value) {
        free(newh);
        return false;
    }
    strcpy(newh->value, s);
    if (q->size == 0) {
        q->head = newh;
    } else {
        q->tail->next = newh;
    }
    newh->next = NULL;
    q->tail = newh;

    q->size++;
    return true;
}
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    
    if (!q || !q->head)
        return false;
    if (sp) {
        strncpy(sp, q->head->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    list_ele_t *tmp;
    tmp = q->head;

    q->head = q->head->next;
    free(tmp->value);
    free(tmp);
    q->size--;
    return true;
}
int q_size(queue_t *q)
{
    if (q != NULL && (q->head != NULL))
        return q->size;
  
    return 0;
}
void q_reverse(queue_t *q)
{
    
    if (q && (q->size > 1)) {
        list_ele_t *now = q->head;
        list_ele_t *tmp = now->next;
        q->tail = q->head;
        while (tmp != NULL) {
            now = tmp;
            tmp = tmp->next;
            now->next = q->head;
            q->head = now;
        }
        q->tail->next = NULL;
    }
}
