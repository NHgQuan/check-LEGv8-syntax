#ifndef __MATH__
#define __MATH__
int expo(const int base, const int exponent)
{
    if(exponent == 0)   return base;
    int result = 1;
    for(int i = 0; i < exponent; i++)
    {
        result*=base;
    }
    return result;
}

#endif