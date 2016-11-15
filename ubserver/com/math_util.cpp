#include "math_util.h"

static bool is_set = false;

namespace Math
{
    void SRandom()
    {
        is_set = true;
        srand((unsigned)time(NULL));
    }
    
    //0-(a-1)
    int Random(int a)
    {
        if(!is_set) SRandom();
        return rand()%a;
    }
    
    //a1 - a2
    int Random(int a1, int a2)
    {
        if(a1 > a2)
        {
            return a2 + Random(a1 - a2);
        }
        return a1 + Random(a2 - a1);
    }
}