#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int ft_strlen(char *str)
{
    int i = 0;

    while (str[i])
        i++;
    return (i);
}

int check_tags(char *str)
{
    int i = 0;

    while (str[i])
    {
        while (str[i] && (str[i] >= 'a' && str[i] <= 'z'))
           i++;
        if (str[i] == ' ')
            i++;
        if ((str[i] != '<' && str[i] != '>' && str[i] != '/'))
        {
            return (1);
        }
        i++;
    }
    return (0);
}

int check_for_self_closing(char *s1, char *s2)
{
    int i = 0;
    int w_len_s1 = ft_strlen(s1);
    int w_len_s2 = ft_strlen(s2);

    if (s1[w_len_s1 - 2] == '/' || s2[w_len_s2 - 2] == '/')
    {
        return (0);
    }
    return (1);
}

char    *remove_tags(char *str)
{
    int k = 0;
    int x = 0;
    char    *newer = malloc((ft_strlen(str) + 1) * sizeof(char));

    while (str[k])
    {
        while (str[k] && str[k] == '/' || str[k] == '>')
        {
            k++;
        }
        newer[x++] = str[k];
        k++;
    }
    newer[x] = '\0';
    return (newer);
}

int compare_tags(char **arr, int size)
{
    int begin = 0;
    int midDown = size / 2 - 1;
    int midUp = size / 2;
    int end = size - 1;

    while (begin <= end)
    {
        if (midDown < 0)
            break ;
        char *s1 = arr[midDown];
        char *s2 = arr[midUp];
        midDown--;
        midUp++;
        if (check_for_self_closing(s1, s2) == 0)
            return (0);
        else if (strcmp(remove_tags(s1), remove_tags(s2)) != 0)
            return (1);
        begin++;
    }
    return (0);
}

char **fill_arr(char **arr, char *str, int size)
{
     char **new_arr = (char **)malloc((size + 1) * sizeof(char *));
    
    // Copy the existing elements from arr to new_arr
    for (int i = 0; i < size; i++) {
        new_arr[i] = arr[i];
    }
    
    new_arr[size] = malloc((ft_strlen(str) + 1) * sizeof(char));

    int i = 0;
    while (str[i])
    {
        new_arr[size][i] = str[i];
        i++;
    }
    new_arr[size][i] = '\0'; // Add null-terminating character
    return new_arr;
}

char  *get_tag(char *str)
{
    char    **tags = NULL;
    char    *new = malloc((ft_strlen(str) + 1) * sizeof(char));
    int i = 0;
    int j = 0;

    while (str[i] && str[i] != '<')
    {
        new[j++] = str[i];
        i++;
    }
    new[j] = '\0';
    if (check_tags(new) == 1)
        return (NULL);
    return (new);
}

int also_check(char *str)
{
    int i = 0;
    int count1 = 0;
    int count2 = 0;

    if (str[0] != '<')
        return (1);
    while (str[i])
    {
        while (str[i] && str[i] >= 'a' && str[i] <= 'z')
            i++;
        while (str[i] && str[i] == ' ')
            i++;
        if (str[i] == '<')
            count1++;
        else if (str[i] == '>')
            count2++;
        i++;
    }
    if (count1 != count2)
        return (1);
    return (0);
}

int    html_val(char *str)
{
    char    **tags = NULL;
    char    *new_str = NULL;
    int i = 0;
    int size = 0;

    if (also_check(str) == 1)
        return (1);
    while (str[i])
    {
        if (str[i] == '<')
        {
            i++;
            new_str = get_tag(&str[i]);
            if (new_str == NULL)
                return (1);
            tags = fill_arr(tags, new_str, size);
            size++;
        }
        i++;
    }
    if (compare_tags(tags, size) == 1)
        return (1);
    return (0);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Are you dumb use more arguments!");
        return (1);
    }
    int i = 1;

    while (argv[i])
    {
        if (html_val(argv[i]) == 0) {
            printf("%s\n", "SUCCESS");
            return (0);
        }
        else {
            printf("%s\n", "BIG F");
            return (1);
        }
        i++;
    }
}