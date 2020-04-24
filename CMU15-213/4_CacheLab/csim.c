#include "cachelab.h"
#include <getopt.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>  // For atoi()
#include <math.h>

int hit_num=0;
int miss_num=0;
int eviction_num=0;
int time=0;

typedef struct cache_line{
    // Only valid bit and set index is required. The block offset is not used.
    int valid_bit;
    long long tag_bits;
    int LRU_counter;
}cache_line_t;


cache_line_t **initial_cache(int S,int E)
{
    cache_line_t**cache=malloc(sizeof(cache_line_t*)*S);
    for(int i=0;i<S;++i)
        cache[i]=malloc(sizeof(cache_line_t)*E);
    for(int i=0;i<S;++i)
        for(int j=0;j<E;++j)
            cache[i][j].valid_bit=0;
    return cache;
}

FILE* openfile(char*path,char*mode)
{
    FILE*file=fopen(path,mode);
    if(!file)
    {
        printf("Cannot open the file!\n");
        exit(-1);
    }
    return file;
}



int if_cache_hit(int set_bits, int E, long long tag_bits,cache_line_t**cache)
{
    for(int line=0;line<E;++line)
    {
        if(cache[set_bits][line].valid_bit&&cache[set_bits][line].tag_bits==tag_bits)
        {
            ++hit_num;
            cache[set_bits][line].LRU_counter=time;
            printf("hit ");
            return 1;
        }
    }
    return 0;
}

int if_empty_line(int set_bits, int E, long long tag_bits,cache_line_t**cache)
{
    for(int i=0;i<E;++i)
    {
        if(cache[set_bits][i].valid_bit==0)
        {
            ++miss_num;

            cache[set_bits][i].tag_bits=tag_bits;
            cache[set_bits][i].valid_bit=1;
            cache[set_bits][i].LRU_counter=time;
            printf("miss ");
            return 1;
        }
    }
    return 0;
}
int get_LRU_index(int set_bits, int E, long long tag_bits,cache_line_t**cache)
{
    int index=0;
    int min_time=cache[set_bits][0].LRU_counter;
    for(int i=1;i<E;++i)
    {
        if(cache[set_bits][i].LRU_counter<min_time)
        {
            min_time=cache[set_bits][i].LRU_counter;
            index=i;
        }
    }
    return index;
}



void replace(int set_bits, int E, long long tag_bits,cache_line_t**cache)
{
    int index=get_LRU_index(set_bits,E,tag_bits,cache);
    cache[set_bits][index].valid_bit=1;
    cache[set_bits][index].tag_bits=tag_bits;
    cache[set_bits][index].LRU_counter=time;
    ++miss_num;
    ++eviction_num;
    printf("miss evict ");
}


void load_to_cache(int set_bits, int E, long long tag_bits,cache_line_t**cache)
{
    if(if_cache_hit(set_bits,E,tag_bits,cache))
        return;
    if(if_empty_line(set_bits,E,tag_bits,cache))
        return;
    replace(set_bits,E,tag_bits,cache);
    return;
}
int main(int argc, char *argv[])
{
    int opt;
    int s,E,b;
    char*filename;
    while((opt = getopt(argc, argv, "s:E:b:t:")) != -1)
    {
        switch(opt){
            case 's':
                s=atoi(optarg);
                break;
            case 'E':
                E=atoi(optarg);
                break;
            case 'b':
                b=atoi(optarg);
                break;
            case 't':
                filename=optarg;
                break;
            default:
                printf("Error: Unrecognized program option!");
                exit(-1);
        }
    }
    int S = pow(2,s);
    
    printf("S = %d, E = %d, b = %d, file = \"%s\"\n",S,E,b,filename);
    if(s<0||E<0||b<0)
    {
        printf("Parameters are wrong!\n");
        exit(-1);
    }

    FILE*file=openfile(filename,"r");
    char*operation=malloc(sizeof(char)*10);
    unsigned long long address,set_mask,tag_bits,set_bits;
    int size;
    char oper;
    set_mask=~(-1<<s);

    cache_line_t **cache=initial_cache(S,E);

    while(fscanf(file,"%s %llx,%d\n",operation,&address,&size)!=-1)
    {
        ++time;
        oper=*operation;
        set_bits=(address>>b)&set_mask;
        tag_bits=(address>>(b+s));
        if(oper=='L'||oper=='S'||oper=='M')
            load_to_cache(set_bits,E,tag_bits,cache);
        if(oper=='M')
        {
            ++hit_num;
            printf("hit ");
        }

        printf("\n");

    }

    printSummary(hit_num, miss_num, eviction_num);


    return 0;
}