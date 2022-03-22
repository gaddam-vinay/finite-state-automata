#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct trans
{
    int a[26];
};
struct gads
{
    int states[1000];
    int isread[1000];
    int noofstates;
};

int main()
{
    int n, k, a, s, e, noofsets1, noofsets2, tem = 0, cstat1, cstat2, flag;
    char p;
    scanf("%d", &n);
    scanf("%d", &k);
    scanf("%d", &a);
    int final[a];
    int finalcheak[n];
    for (int i = 0; i < n; ++i)
    {
        finalcheak[i] = 0;
    }
    int alp[26] = {0};
    for (int i = 0; i < a; ++i)
    {
        scanf("%d", &final[i]);
        finalcheak[final[i]] = 1;
    }
    struct trans tran[n];

    for (int i = 0; i < k; ++i)
    {
        scanf("%d %c %d", &s, &p, &e);
        tran[s].a[p - 97] = e;
        alp[p - 97] = 1;
    }
    struct gads *sets2[n];
    struct gads *sets1[n];
    sets1[0] = (struct gads *)malloc(sizeof(struct gads));
    sets1[1] = (struct gads *)malloc(sizeof(struct gads));
    sets1[1]->noofstates = a;
    for (int i = 0; i < a; ++i)
    {
        sets1[1]->states[i] = final[i];
        sets1[1]->isread[i] = 0;
    }
    sets1[0]->noofstates = n - a;
    for (int i = 0; i < n; ++i)
    {
        if (finalcheak[i] == 0)
        {
            sets1[0]->states[tem] = i;
            sets1[0]->isread[tem] = 0;
            tem++;
        }
    }
    noofsets1 = 2;
    for (int i = 0; i < 10000; ++i)
    {
        noofsets2 = 0;
        for (int j = 0; j < noofsets1; ++j)
        {
            for (int l = 0; l < sets1[j]->noofstates; ++l)
            {
                if (sets1[j]->isread[l] == 0)
                {
                    tem = 0;
                    sets2[noofsets2] = (struct gads *)malloc(sizeof(struct gads));
                    sets2[noofsets2]->isread[tem] = 0;
                    sets2[noofsets2]->states[tem] = sets1[j]->states[l];
                    tem++;
                    for (int fd = l + 1; fd < sets1[j]->noofstates; ++fd)
                    {
                        flag = 0;
                        for (int ok = 0; ok < 26; ++ok)
                        {
                            if (alp[ok] == 1)
                            {
                                cstat1 = tran[sets1[j]->states[l]].a[ok];
                                cstat2 = tran[sets1[j]->states[fd]].a[ok];
                                for (int he = 0; he < noofsets1; ++he)
                                {
                                    for (int she = 0; she < sets1[he]->noofstates; ++she)
                                    {
                                        if (cstat1 == sets1[he]->states[she])
                                        {
                                            for (int hmm = 0; hmm < sets1[he]->noofstates; ++hmm)
                                            {
                                                if (cstat2 == sets1[he]->states[hmm])
                                                {
                                                    flag++;
                                                    break;
                                                }
                                            }
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        if (flag == k / n)
                        {
                            sets2[noofsets2]->isread[tem] = 0;
                            sets2[noofsets2]->states[tem] = sets1[j]->states[fd];
                            sets1[j]->isread[fd] = 1;
                            tem++;
                        }
                    }
                    sets2[noofsets2]->noofstates = tem;
                    noofsets2++;
                }
            }
        }
        if (noofsets2 == noofsets1)
            break;
        noofsets1 = noofsets2;
        for (int j = 0; j < n; ++j)
        {
            sets1[j] = sets2[j];
        }
    }

    // for (int i = 0; i < noofsets1; ++i)
    // {
    //     for (int j = 0; j < sets1[i]->noofstates; ++j)
    //     {
    //         printf("%d ", sets1[i]->states[j]);
    //     }

    //     printf("\n");
    // }

    printf("%d ", noofsets1);
    printf("%d ", noofsets1 * (k / n));
    int nooffinals = 0;
    int finalfinals[n];
    int startindex = 90;
    tem = 0;
    int transtate;
    for (int i = 0; i < noofsets1; ++i)
    {
        if (finalcheak[sets1[i]->states[0]] == 1)
        {
            finalfinals[nooffinals] = i;
            nooffinals++;
            for (int j = 0; j < sets1[i]->noofstates; ++j)
            {
                if (sets1[i]->states[j] == 0)
                {
                    startindex = i;
                }
            }
        }
        if (sets1[i]->states[0] == 0)
        {
            startindex = i;
        }
    }
    printf("%d \n", nooffinals);
    for (int i = 0; i < nooffinals; ++i)
    {
        if (finalfinals[i] != startindex)
            printf("%d ", finalfinals[i]);
        else
            printf("0 ");
    }
    printf("\n");
    // printf("%d", startindex);

    struct trans transition[noofsets1];
    for (int i = 0; i < noofsets1; ++i)
    {
        for (int j = 0; j < 26; ++j)
        {
            if (alp[j] == 1)
            {
                transtate = tran[sets1[i]->states[0]].a[j];
                for (int l = 0; l < noofsets1; ++l)
                {
                    for (int ok = 0; ok < sets1[l]->noofstates; ++ok)
                    {
                        if (sets1[l]->states[ok] == transtate)
                        {
                            transition[i].a[j] = l;
                            break;
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < noofsets1; ++i)
    {
        if (i == startindex)
        {
            for (int j = 0; j < 26; ++j)
            {
                if (alp[j] == 1)
                {
                    printf("0 ");
                    printf("%c ", j + 97);
                    if (transition[i].a[j] == startindex)
                    {
                        printf("0 ");
                    }
                    else if (transition[i].a[j] == 0)
                        printf("%d ", startindex);
                    else
                        printf("%d ", transition[i].a[j]);
                    printf("\n");
                }
            }
        }
        else if (i == 0)
        {
            for (int j = 0; j < 26; ++j)
            {
                if (alp[j] == 1)
                {
                    printf("%d ", startindex);
                    printf("%c ", j + 97);
                    if (transition[i].a[j] == startindex)
                    {
                        printf("0 ");
                    }
                    else if (transition[i].a[j] == 0)
                        printf("%d ", startindex);
                    else
                        printf("%d ", transition[i].a[j]);

                    printf("\n");
                }
            }
        }
        else
        {
            for (int j = 0; j < 26; ++j)
            {
                if (alp[j] == 1)
                {
                    printf("%d ", i);
                    printf("%c ", j + 97);
                    if (transition[i].a[j] == startindex)
                    {
                        printf("0 ");
                    }
                    else if (transition[i].a[j] == 0)
                        printf("%d ", startindex);
                    else
                        printf("%d ", transition[i].a[j]);

                    printf("\n");
                }
            }
        }
    }
}
