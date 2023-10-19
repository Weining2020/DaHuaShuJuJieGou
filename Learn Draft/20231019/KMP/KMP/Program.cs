//20231019
//对于写代码求next数组，我真牛啊。


//string tString = "abcabde";
//List<int> myNext = GetNext(tString);
//for (int i = 0; i < myNext.Count; i++)
//{
//    Console.WriteLine(myNext[i]);
//}


List<int> GetNext(string T)
{
    int i = 0;
    int k = 0;
    List<int> next = new List<int>(T.Length);
    //next[0] = 0;//next [1]必须是0.
    next.Add(0);
    while (i < T.Length - 1)
    {
        if (k == 0 || T[i] == T[k - 1])
        {
            i++;
            k++;
            //next[i] = k;
            next.Add(k);
        }
        else
        {
            k = next[k - 1];
        }
    }
    return next;
}

int IndexKMP(string mainString, string childString, int pos = 0)
{
    int i = pos;
    int j = 0;
    int n = 0;
    List<int> next = GetNext(childString);

    while (i < mainString.Length - 1 && j < childString.Length - 1)
    {
        if (j == 0 || mainString[i].Equals(childString[j - 1]))
        {
            i++;
            j++;
        }
        else
        {
            j = next[j - 1];
        }

        Console.WriteLine($"{++n}th,{i},{j}");
    }

    if (j >= childString.Length - 1)
    {
        return i - next.Count;
    }
    else
    {
        return 0;
    }
}


string myMainString = "cbaabcabdef";
string myChildString = "baa";

int result = IndexKMP(myMainString, myChildString);
Console.WriteLine(result);
//Console.WriteLine(IndexKMP(myMainString, myChildString));
