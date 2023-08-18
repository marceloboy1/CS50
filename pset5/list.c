
typedef struct node
{
    int number;
    struct node *next;
}
node;

int main (void)
{
    //cria o primeiro nó, com valor nulo
    node *list = NULL;

    //cria um novo no
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return 1;
    }

    //coloca valores nele e ele passa a ser o primeiro no
    n->number = 1;
    n->next = NULL;
    list = n;

    //cria um novo no
    n = malloc(sizeof(node));
    if (n == NULL){
        free(list);
        return 1;
    }
    n -> number = 2;
    n -> next = NULL;

    //adiciona ele como o no do primeiro no
    list -> next = n;


    //cria um terceiro no
    n = malloc(sizeof(node));
    if (n == NULL){
        free(list);
        return 1;
    }
    n -> number = 3;
    n -> next = NULL;

    //adiciona o terceiro no nó do segundo no
    list -> next -> next = n;

    //loop for para iterar sobre a lista
    for (node *tmp = list; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n", tmp->number);
    }

    while(list != NULL)
    {
        node *tmp = list->next;
        free(list);
        list=tmp;
    }
}

