/*
 * find and output the given number's shortest square sum.
 * like input: 12=2^2+2^2+2^2 (not 3^2+1^2+1^2+1^2) output: {2 2 2}  
 *
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM_CHARS 256
#define DEBUG 0

#if DEBUG
#define dbgprintf(fmt, ...) \
    do {\
        fprintf(stderr, "%s:%d:" fmt, __FUNCTION__, __LINE__, __VA_ARGS__);\
    } while (0)
#else
#define dbgprintf(fmt, ...) do {} while (0)
#endif

typedef struct num_map
{
    int cost;
    char numbers_str[MAX_NUM_CHARS];
} num_map_t;


int max_min_cost = 0;
int number = 1000000;
int allocated_num_maps;
num_map_t * num_maps;

void cleanup_num_maps()
{
    /* TODO: Uncomment this when we support dynamically
     * allocating the buffers for the string of numbers
     *
    int i = 0;
    for (i = 0; i < allocated_num_maps; i++) {
        if (num_maps[i].numbers_str) {
            free(num_maps[i].numbers_str);
        }
    }
    */
    free(num_maps);
}

void build_sums(int num)
{
    int sqrt_num = (int) sqrt(num);
    if ((sqrt_num * sqrt_num) == num) {
        num_maps[num].cost = 1;
        /* TODO: Modify to dynamically allocate the number
         * of characters. Need to add routine to count the
         * number of digits
        num_maps[num].numbers_str = calloc(num*2, sizeof(char));
        if (num_maps[num].numbers_str == 0) {
            fprintf(stderr, "ERROR Calloc failed at line %d\n", __LINE__);
            cleanup_num_maps();
            exit(1);
        }
        */
        snprintf(num_maps[num].numbers_str, MAX_NUM_CHARS, "%d", sqrt_num);
        dbgprintf("Found sqrt for num %d:%d\n", num, sqrt_num);
        return;
    }
    int i = 0;
    int min_cost = -1;
    int min_idx1 = -1;
    int min_idx2 = -1;
    for (i = 1; i <= num/2; i++) {
        int total_cost = num_maps[i].cost + num_maps[num-i].cost;
        if ((total_cost < min_cost) || (min_cost == -1)) {
            // Found that A+B = num and the cost of each is minimal
            min_cost = total_cost;
            min_idx1 = i;
            min_idx2 = num-i;
            dbgprintf("Found min cost for num: %d cost: %d "
                      "min_idx1: %d: min_idx2: %d\n",
                      num, min_cost, min_idx1, min_idx2);
        }
    }
    int strlen1 = strlen(num_maps[min_idx1].numbers_str);
    int strlen2 = strlen(num_maps[min_idx2].numbers_str);
    num_maps[num].cost = min_cost;
    /* TODO: Modify to dynamically allocate the number
     * of characters. Need to add routine to count the
     * number of digits
    int new_strlen = strlen1 + strlen2 + 2;
    num_maps[num].numbers_str = calloc(new_strlen, sizeof(char));
    */
    snprintf(num_maps[num].numbers_str, MAX_NUM_CHARS, "%s %s",
             num_maps[min_idx1].numbers_str, num_maps[min_idx2].numbers_str);
    dbgprintf("Min cost for num: %d is %d. Num_str is %s\n",
              num, num_maps[num].cost, num_maps[num].numbers_str);
    if (max_min_cost < min_cost) {
        max_min_cost = min_cost;
        printf("Min cost for num: %d is %d. Num_str is %s\n",
               num, num_maps[num].cost, num_maps[num].numbers_str);
    }
}


void find_sums(int num)
{
    int i = 1;
    for (i = 1; i <= num; i++) {
        build_sums(i);
    }
    printf("sum of squares: %s\n", num_maps[num].numbers_str);
    printf("max min_cost: %d\n", max_min_cost);
}

int main()
{

    num_maps = calloc(number+1, sizeof(num_map_t));
    
    if (num_maps) {
        allocated_num_maps = number + 1;
    } else {
        fprintf(stderr, "ERROR Calloc failed at line %d\n", __LINE__);
        return 1;
    }

    find_sums(number);
    return 0;
}
