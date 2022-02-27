

#include <unistd.h>
#include <stdlib.h>
void	ft_putchar(char c)
{
    write(1, &c, 1);
}

void	ft_error(void)
{
    write(1, "Error\n", 6);
}

#include <stdlib.h>
int	*create_params_table(char *params, int max_value)
{
    int	*tmp;
    int	i;
    int	cnt;

    i = 0;
    cnt = 0;
    tmp = (int *)malloc(sizeof(int) * max_value * max_value);
    while (params[cnt] && i < max_value * max_value)
    {
	   tmp[i] = params[cnt] - '0';
	   cnt += 2;
	   i++;
    }
    return (tmp);
}

void	fill_edge_of_table(int **arr, int *tmp, int max_value)
{
    int	i;

    i = 0;
    while (++i <= max_value)
    {
	   arr[0][i] = tmp[i - 1];
    }
    i = 0;
    while (++i <= max_value)
    {
	   arr[max_value + 1][i] = tmp[i + 3];
    }
    i = 0;
    while (++i <= max_value)
    {
	   arr[i][0] = tmp[i + 7];
    }
    i = 0;
    while (++i <= max_value)
    {
	   arr[i][max_value + 1] = tmp[i + 11];
    }
}

void	fill_table(int **arr, int max_value, char *params)
{
    int	i;
    int	j;
    int	*tmp;

    i = 0;
    tmp = create_params_table(params, max_value);
    while (i < max_value + 2)
    {
	   j = 0;
	   while (j++ < max_value + 2)
		  arr[i++][j] = 0;
    }
    fill_edge_of_table(arr, tmp, max_value);
}

int	**create_table(char *params, int max_value)
{
    int	i;
    int	j;
    int	**arr;

    arr = (int **)malloc(sizeof(int *) * max_value + 2);
    if (!(arr))
	   return (0);
    i = -1;
    while (++i < max_value + 2)
    {
	   arr[i] = (int *)malloc(sizeof(int) * max_value + 2);
	   if (!(arr[i]))
		  return (0);
    }
    i = -1;
    while (++i < max_value + 2)
    {
	   j = 0;
	   while (j < max_value + 2)
	   {
		  arr[i][j++] = 0;
	   }
    }
    fill_table(arr, max_value, params);
    return (arr);
}

void	print_table(int **arr, int max_value)
{
    int	i;
    int	j;

    i = 1;
    while (i <= max_value)
    {
	   j = 1;
	   while (j <= max_value)
	   {
		  ft_putchar(arr[i][j] + '0');
		  if (j != max_value)
			 ft_putchar(' ');
		  j++;
	   }
	   ft_putchar('\n');
	   i++;
    }
}

int	sudoku(int **arr, int x, int y)
{
    int	i;

    i = 1;
    while (i < x)
    {
	   if (arr[i][y] == arr[x][y])
		  return (0);
	   i++;
    }
    i = 1;
    while (i < y)
    {
	   if (arr[x][i] == arr[x][y])
		  return (0);
	   i++;
    }
    return (1);
}

int	row_left(int **arr, int x, int max_value)
{
    int	cnt;
    int	i;
    int	highest;

    cnt = 1;
    i = 1;
    highest = arr[x][i];
    while (i <= max_value)
    {
	   if (highest < arr[x][i])
	   {
		  highest = arr[x][i];
		  cnt++;
	   }
	   i++;
    }
    if (cnt == arr[x][0])
	   return (1);
    return (0);
}

int	row_right(int **arr, int x, int max_value)
{
    int	cnt;
    int	i;
    int	highest;

    cnt = 1;
    i = max_value;
    highest = arr[x][i];
    while (i > 0)
    {
	   if (highest < arr[x][i])
	   {
		  highest = arr[x][i];
		  cnt++;
	   }
	   i--;
    }
    if (cnt == arr[x][max_value + 1])
	   return (1);
    return (0);
}


int	col_up(int **arr, int y, int max_value)
{
    int	i;
    int	highest;
    int	cnt;

    i = 1;
    highest = arr[1][y];
    cnt = 1;
    while (i < max_value + 1)
    {
	   if (arr[i][y] > highest)
	   {
		  cnt++;
		  highest = arr[i][y];
	   }
	   i++;
    }
    if (cnt == arr[0][y])
	   return (1);
    return (0);
}

int	col_down(int **arr, int y, int max_value)
{
    int	i;
    int	highest;
    int	cnt;

    i = max_value;
    highest = arr[max_value][y];
    cnt = 1;
    while (i > 0)
    {
	   if (arr[i][y] > highest)
	   {
		  cnt++;
		  highest = arr[i][y];
	   }
	   i--;
    }
    if (cnt == arr[max_value + 1][y])
	   return (1);
    return (0);
}
#include <stdio.h>

int	backtrack(int **arr, int x, int y, int max_value)
{
    int i;
    int all_set;

    i = 0;
    all_set = 0;
    while (!all_set)
    {
	   i++;
	   arr[x][y] = i;
	   // printf("i = %d, x = %d, y = %d, arr[x][y] = %d\n",i,x,y,arr[x][y]);
	   if (!sudoku(arr, x, y))
	   {
		  continue;
	   }
	   if (i == max_value + 1)
	   {
		  arr[x][y] = 0;
		  break;
	   }
	   if (x == max_value && y == max_value)
	   {
		  if (row_left(arr, x, max_value) && row_right(arr, x, max_value)
			 && col_down(arr, y, max_value) && col_up(arr, y, max_value))
		  {
			 all_set = 1;
			 break;
		  }
		  else
		  {
			 continue;
		  }
	   }
	   else if (y == max_value)
	   {
		  if (row_left(arr, x, max_value) && row_right(arr, x, max_value))
		  {
			 all_set = backtrack(arr, x + 1, 1, max_value);
		  }
		  else
		  {
			 continue;
		  }
	   }
	   else if (x == max_value)
	   {
		  if (col_down(arr, y, max_value) && col_up(arr, y, max_value))
		  {
			 all_set = backtrack(arr, x, y + 1, max_value);
		  }
		  else
		  {
			 continue;
		  }
	   }
	   else
	   {
		  all_set = backtrack(arr, x, y + 1, max_value);
	   }
    }
    if (x == 1 && y == 1 && i == 0)
    {
	   //¿¡·¯!
	   write(1, "No Combination", 14);
    }
    return all_set;
}

int	main(int argc, char *argv[])
{

    int	**arr;
    int	max_value;
    /*
	if (argc != 2)
	{
		ft_error();
		return (1);
	}
	max_value = count_digit(argv[1]) / 4;
	if (!param_is_valid(argv[1], max_value))
	{
		ft_error();
		return (1);
	}
	*/
    argv[1] = "2 1 3 3 2 4 1 2 2 1 4 2 3 3 1 2";
    max_value = 4;
    arr = create_table(argv[1], max_value);
    backtrack(arr, 1, 1, max_value);

    print_table(arr, max_value);
    return (0);
}

