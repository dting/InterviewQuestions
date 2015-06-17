#include <stdio.h>
#include <string.h>
#include <ctype.h>

// To execute C, please define "int main()"
//"dog"
//"god"

void reverse_string(char * str, int len)
{
    char temp;
    int i = 0;
    for (i = 0; i < len/2; i++)
    {
      temp = str[i];
      str[i] = str[len-1-i];
      str[len-1-i] = temp;
    }
}

int main() {
  
    printf("********************************************************************************\n");
    char my_str[1024];
    strncpy(my_str, "To execute C, please define \"int main()\"", 1024);

    // First reverse entire string
    reverse_string(my_str, strlen(my_str));
    // for each word, reverse the word
    int i = 0;
    int start_idx = 0;

    while (i < strlen(my_str))
    {
        // The next group of letters could be either alpha-characters or
        // non-alpha characters. Find which one and then reverse that group
        int is_alpha = isalpha(my_str[i]);
        start_idx = i;
        while (is_alpha && isalpha(my_str[i]) ||
               !is_alpha && !isalpha(my_str[i]))
        {
            i++;
        }
        // Found a group of alpha or non-alpha, reverse it
        printf("Reversing my_str\n %s\n from start_idx %d for length of %d."
                "i is %d, my_str[start_idx] is %c, my_str[i-1] is %c\n",
               my_str, start_idx, i-start_idx, i, my_str[start_idx], my_str[i-1]);
        reverse_string(&my_str[start_idx], i - start_idx);
        // Move on to the next character
    }
    printf("--------------------------------------------------------------------------------\n");
    printf("%s\n", my_str);
    printf("********************************************************************************\n");
    return 0;
}

