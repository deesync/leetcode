#include <stdio.h>
#include <stdlib.h>

// Write a function to find the longest common prefix string amongst an array of strings.
// If there is no common prefix, return an empty string ""

char * longestCommonPrefix(char ** strs, int strsSize) 
{   
    char * const prefix = (char *) calloc(sizeof(char), 200); 

    for (int c = 0; strs[0][c]; c++) {
        for (int i = 1; i < strsSize; ++i)            
            if (strs[0][c] != strs[i][c]) return prefix;

        prefix[c] = strs[0][c];
    } 

    return prefix; 
}

// --------------------------------- cut here --------------------------------------------

int main()
{
    char *strs[] = {"flower","flo","flowerpow,"};

    printf("%s\n", longestCommonPrefix(strs, 3));

    return 0;
}