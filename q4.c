#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct trans
{
    int s;
    char t;
    int e;
};

struct trans transition[10000];
int stateno = 0;
int alp[26] = {0};
int transno = 0;
void build_nfa(int start, char regex[])
{
    int i = 0, finalstates[100], nooffinals = 0, st, prevstate;
    char subregex[1000];
    st = start;
    prevstate = stateno;
    transition[transno].s = stateno++;
    transition[transno].e = stateno;
    transition[transno].t = 'E';
    transno++;
    while (i < strlen(regex))
    {
        if (regex[i] >= 97 && regex[i] <= 122)
        {
            prevstate = stateno;
            transition[transno].s = stateno++;
            transition[transno].e = stateno;
            transition[transno].t = regex[i];
            alp[regex[i] - 97] = 1;
            transno++;
        }
        else if (regex[i] == '+')
        {
            finalstates[nooffinals++] = stateno;
            prevstate = st;
            transition[transno].s = st;
            stateno++;
            transition[transno].e = stateno;
            transition[transno].t = 'E';
            transno++;
        }
        else if (regex[i] == '*')
        {
            //prevstate = stateno;
            transition[transno].s = stateno;
            transition[transno].e = prevstate;
            transition[transno].t = 'E';
            transno++;
            transition[transno].s = prevstate;
            transition[transno].e = stateno;
            transition[transno].t = 'E';
            transno++;
        }
        else if (regex[i] == '(')
        {
            prevstate = stateno;
            int j = 0, flag = 1;
            i++;
            while (flag != 0)
            {
                subregex[j++] = regex[i];
                if (regex[i] == '(')
                    flag++;
                if (regex[i] == ')')
                    flag--;
                i++;
            }
            subregex[--j] = '\0';
            build_nfa(prevstate, subregex);
            i--;
        }
        else
        {
            printf("invalid regex\n");
            return;
        }

        i++;
    }
    stateno++;
    for (i = 0; i < nooffinals; i++)
    {
        transition[transno].s = finalstates[i];
        transition[transno].e = stateno;
        transition[transno].t = 'E';
        transno++;
    }
    transition[transno].s = stateno - 1;
    transition[transno].e = stateno;
    transition[transno].t = 'E';
    transno++;
}
int main(int args, char *arg[])
{
    if (args != 3)
    {
        printf("provide valid number of arguments\n");
        return 0;
    }
    FILE *fp = fopen(arg[1], "r");
    char regex[1000];
    fscanf(fp, "%s", regex);
    int j = 0;
    FILE *fp1 = fopen(arg[2], "a");
    build_nfa(0, regex);
    int numofalp = 0;
    for (int i = 0; i < 26; ++i)
    {
        if (alp[i] == 1)
            numofalp++;
    }
    int k = 1;
    fprintf(fp1, "%d %d %d\n", stateno + 1, transno, k);
    fprintf(fp1, "%d\n", stateno);
    for (int i = 0; i < transno; ++i)
    {
        fprintf(fp1, "%d %c %d\n", transition[i].s, transition[i].t, transition[i].e);
    }
}