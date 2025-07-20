#include "../inc/minishell.h"

void garbage_collector(t_garbage **garbage, void *address)
{
    t_garbage *new_node;

    new_node = malloc(sizeof(t_garbage));
    if (!new_node)
        return;
    new_node->address = address;
    new_node->next = *garbage;
    *garbage = new_node;
}

void free_garbage(t_garbage **garbage)
{
    t_garbage *tmp;
    while (*garbage)
    {
        tmp = (*garbage)->next;
        if ((*garbage)->address)
            free((*garbage)->address);
        free(*garbage);
        *garbage = tmp;
    }
}

t_garbage   **get_garbage_head(t_garbage *gb_list_head, int flag)
{
    static t_garbage    *gb_head;

    if (flag == GET)
        return (&gb_head);
    if (flag == SET && gb_list_head != NULL)
        gb_head = gb_list_head;
    else if (flag == FREE && gb_head != NULL)
    {
        free_garbage(&gb_head);
        gb_head = NULL;
        return (NULL);
    }
    return (&gb_head);
}

void    *ft_malloc(int size, int size2)
{
    void        *add;

    (void)size2; // Unused parameter for compatibility
    add = malloc(size);
    if (!add)
        error_msg("malloc");
    garbage_collector(get_garbage_head(NULL, GET), add);
    return (add);
}