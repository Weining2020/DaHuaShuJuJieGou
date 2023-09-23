using System;

public class Class1
{
	public Class1()
	{
		public List<int> InsertIntoList(int n, List<int> list, int value)
		{
			int listSize = list.Count;
			if (n > listSize)
			{
				return WrongCode;
			}

			if (listSize == list.Capacity)
			{

				list.AddCapacity(1);
			}

			for (int i = listSize; i > n; i--)
			{
				list[i + 1] = list[i];
			}

			list[n] = value;

			return list;

		}
	}
}
