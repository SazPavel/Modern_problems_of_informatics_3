#include "spi1.h"

unsigned char table[256];
int position;
unsigned char *b;

void free_list(list_t *list)
{
	list_t  *list_tmp = NULL;
    while (list)
    {
    	list_tmp = list->next;
    	free(list);
    	list = list_tmp;
	}
}

void preparation()
{
	int i;
	for (i = 0; i < 256; i++)
		table[i] = (unsigned char)i;
}

unsigned char mtf_back(int num)
{
	int i;
	unsigned char result, tmp, tmp2;
	result = table[num];
	tmp = table[0];
	table[0] = table[num];
	for (i = 1; i <= num; i++)
	{
		tmp2 = table[i];
		table[i] = tmp;
		tmp = tmp2;
	}
	return (unsigned char)result;
}

list_t * decode_f_0(FILE *fin)
{
	int i, bit = 0, result = 0;
	long long int num;
	list_t *list = NULL, *curr = NULL, *first = NULL;
	
	while (fread (&num, sizeof(long long int), 1, fin) == 1)
	{
#if DEBUG >= 1
		printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 48));
		printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 32));
		printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 16));
		printf(""TWO_BYTE_TO_BINARY_PATTERN" READ\n", TWO_BYTE_TO_BINARY(num));
#endif
		for (i = LL_INT_SIZE; i > 0; i--)
		{
			bit = (num >> (i-1)) & 1;
			if (bit)
			{
				curr = malloc(sizeof(list_t));
				curr->num = result;
				curr->next = NULL;
				curr->prev = NULL;
				if (list == NULL)
				{
					list = curr;
					first = list;
				}
				else
				{
					list->next = curr;
					curr->prev = list;
					list = curr;
				}
				result = 0;
			}
			else
				result ++;
		}
	}
	return first;
}

list_t * decode_f_1(FILE *fin)
{	
	int i, j,  j1, bit = 0, size = 0, result = 0;
	long long int num;
	list_t *list = NULL, *curr = NULL, *first = NULL;
	
	while (fread (&num, sizeof(long long int), 1, fin) == 1)
	{
#if DEBUG >= 1
		printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 48));
		printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 32));
		printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 16));
		printf(""TWO_BYTE_TO_BINARY_PATTERN" READ\n", TWO_BYTE_TO_BINARY(num));
#endif
		for (i = LL_INT_SIZE; i > 0;)
		{
			bit = (num >> (i-1)) & 1;
			if (bit)
			{
				result = 0;
				if (size != 0)
				{
					for (j = 0, j1 = 0; j < size; j++, j1++)
					{
						bit = (num >> (i-1-j1)) & 1;
						result = (result << 1) | bit;
						if (i-1-j1 == 0)
						{
							if (fread (&num, sizeof(long long int), 1, fin) != 1)
							{
								printf("Wrong code");
								return first;
							}
#if DEBUG >= 1
		printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 48));
		printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 32));
		printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 16));
		printf(""TWO_BYTE_TO_BINARY_PATTERN" READ\n", TWO_BYTE_TO_BINARY(num));
#endif
							i = LL_INT_SIZE;
							j1 = -1;
						}
					}
					i -= j1;
				}
				else
				{
					i--;
					i -= size;
				}
				
				curr = malloc(sizeof(list_t));
				curr->num = result;
				curr->next = NULL;
				curr->prev = NULL;
				if (list == NULL)
				{
					list = curr;
					first = list;
				}
				else
				{
					list->next = curr;
					curr->prev = list;
					list = curr;
				}
				
				size = 0;
				result = 0;
			}
			else
			{
				size ++;
				i--;
			}
		}
	}
	return first;
}

list_t * decode_f_2(FILE *fin)
{
	int i, j, j1, bit = 0, size = 0, size_1 = 0, result = 0;
	long long int num;
	list_t *list = NULL, *curr = NULL, *first = NULL;
	
	while (fread (&num, sizeof(long long int), 1, fin) == 1)
	{
#if DEBUG >= 1
		printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 48));
		printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 32));
		printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 16));
		printf(""TWO_BYTE_TO_BINARY_PATTERN" READ\n", TWO_BYTE_TO_BINARY(num));
#endif
		for (i = LL_INT_SIZE; i > 0;)
		{
			bit = (num >> (i-1)) & 1;
			if (bit)
			{
				size_1 = 0;
				if (size != 0)
				{
					result = 1;
					for (j = 0, j1 = 0; j < size; j++, j1++)
					{
						bit = (num >> (i-1-j1)) & 1;
						size_1 = (size_1 << 1) | bit;
						if (i-1-j1 == 0)
						{
							if (fread (&num, sizeof(long long int), 1, fin) != 1)
							{
								printf("Wrong code");
								return first;
							}
#if DEBUG >= 1
		printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 48));
		printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 32));
		printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 16));
		printf(""TWO_BYTE_TO_BINARY_PATTERN" READ\n", TWO_BYTE_TO_BINARY(num));
#endif
							i = LL_INT_SIZE;
							j1 = -1;
						}
					}
					i = i - j1+1;
					for (j = 1, j1 = 1; j < size_1; j++, j1++)
					{
						bit = (num >> (i-1-j1)) & 1;
						result = (result << 1) | bit;
						if (i-1-j1 == 0)
						{
							if (fread (&num, sizeof(long long int), 1, fin) != 1)
							{
								printf("Wrong code");
								return first;
							}
#if DEBUG >= 1
		printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 48));
		printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 32));
		printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(num >> 16));
		printf(""TWO_BYTE_TO_BINARY_PATTERN" READ\n", TWO_BYTE_TO_BINARY(num));
#endif
							i = LL_INT_SIZE;
							j1 = -1;
						}
					}
					i = i - j1;
				}
				else
				{
					result = 0;
					i--;
				}
				curr = malloc(sizeof(list_t));
				curr->num = result;
				curr->prev = NULL;
				curr->next = NULL;
				if (list == NULL)
				{
					list = curr;
					first = list;
				}
				else
				{
					list->next = curr;
					curr->prev = list;
					list = curr;
				}
				result = 0;
				size = 0;
				size_1 = 0;
			}
			else
			{
				size ++;
				i--;
			}
		}
	}
	return first;
}

list_t * bwt_back(list_t *list, int size)
{
	list_t *list_tmp;
	unsigned char *c, *tmp;
	int *ci, *ci_2;
	int i = 0, j;
    c = malloc(sizeof(char)*size);
    tmp = malloc(sizeof(char)*size);
    ci = malloc(sizeof(int)*size);
    ci_2 = malloc(sizeof(int)*size);
    list_tmp = list;
    while (list_tmp)
    {
    	c[i] = list_tmp->c_num;
    	ci[i] = i;
    	i++;
    	list_tmp = list_tmp->next;
	}
	for(i = 1; i < size; i++)
	{
		unsigned char value = c[i];
		int index = i, value_tmp = ci[i];
		while ((index > 0) && (c[index - 1] > value))
		{
			c[index] = c[index-1];
			ci[index] = ci[index-1];
			index--;
		}
		ci[index] = value_tmp;
		c[index] = value;
	}
	for (i = 0; i < size; i++)
	{
		
		tmp[ci[i]] = c[i];
		ci_2[ci[i]] = i;
	}
#if DEBUG >= 1
	for(i = 0; i < size; i++)
	{
		printf("%d %d\n", tmp[i], ci_2[i]);
	}
	printf("\n");
#endif
	
	j = position;
	list_tmp = list;
	do
	{
		list_tmp->c_num = tmp[j];
		j = ci_2[j];
		list_tmp = list_tmp->next;
	}while(j != position);
	return list;
}

int decoder()
{
	FILE *fin = NULL, *fout = NULL;
	int size = 0;
	list_t *list = NULL, *list_tmp;
    if ((fin = fopen(fin_name, "rb")) == NULL)
    {
    	printf("Unable to open file %s\n", fin_name);
    	return -1;
	}
    	
	if ((fout = fopen(fout_name, "wb")) == NULL)
    {
    	printf("Unable to open file %s\n", fout_name);
		fclose(fin);
		return -1;
	}
	preparation();
	switch (code_type)
	{
		case 1:
		{
			list = decode_f_0(fin);
			list_tmp = list;
#if DEBUG >= 1
			printf("read code:\n");
#endif
			while (list_tmp)
			{
				size ++;
#if DEBUG >= 1
				printf("%u ", list_tmp->num);
#endif
				list_tmp->c_num = mtf_back(list_tmp->num);
				list_tmp = list_tmp->next;
			}
#if DEBUG >= 1
			printf("\ndecode code:\n");
#endif
			list_tmp = bwt_back(list, size);
			while (list_tmp)
			{
#if DEBUG >= 1
				printf("%u ", list_tmp->c_num);
#endif
				fwrite(&list_tmp->c_num, sizeof(char), 1, fout);
				list_tmp = list_tmp->next;
			}
			break;
		}
		case 2:
		{
			list = decode_f_1(fin);
			list_tmp = list;
#if DEBUG >= 1
			printf("read code:\n");
#endif
			while (list_tmp)
			{
				size ++;
#if DEBUG >= 1
				printf("%u ", list_tmp->num);
#endif
				list_tmp->c_num = mtf_back(list_tmp->num);
				list_tmp = list_tmp->next;
			}
#if DEBUG >= 1
			printf("\ndecode code:\n");
#endif
			list_tmp = bwt_back(list, size);
			while (list_tmp)
			{
#if DEBUG >= 1
				printf("%u ", list_tmp->c_num);
#endif
				fwrite(&list_tmp->c_num, sizeof(char), 1, fout);
				list_tmp = list_tmp->next;
			}
			break;
		}
		case 3:
		{
			list = decode_f_2(fin);
			list_tmp = list;
#if DEBUG >= 1
			printf("read code:\n");
#endif
			while (list_tmp)
			{
				size ++;
#if DEBUG >= 1
				printf("%u ", list_tmp->num);
#endif
				list_tmp->c_num = mtf_back(list_tmp->num);
				list_tmp = list_tmp->next;
			}
#if DEBUG >= 1
			printf("\ndecode code:\n");
#endif
			list_tmp = bwt_back(list, size);
			while (list_tmp)
			{
#if DEBUG >= 1
				printf("%u ", list_tmp->c_num);
#endif
				fwrite(&list_tmp->c_num, sizeof(char), 1, fout);
				list_tmp = list_tmp->next;
			}
			break;
		}
	}
#if DEBUG >= 1
	printf("\n");
#endif
    fclose(fin);
    fclose(fout);
	free_list(list);
	return 1;
}

unsigned char mtf(unsigned char num_read)
{
	int i;
	unsigned char result;
	result = table[(int)num_read];
	if (result == 0)
		return result;
	for (i = 0; i < 256; i++)
	{
		if (table[i] < result)
			table[i] ++;
	}
	table[(int)num_read] = 0;
	return result;
}

long long int code_f_0(int num, int *size)
{
	*size = num + 1;
	return 1;
}

long long int code_f_1(int num, int *size)
{
	int tmp_num = num, i = 1;
	long long int result = num;
	if (num == 0)
	{
		*size = 1;
		return 1;
	}
	for ( ;tmp_num > 1; tmp_num /= 2, i++);
	*size = 2*i;
	return result;
}

long long int code_f_2(int num, int *size)
{
	int size_tmp = 0, tmp_num = num, i = 1;
	long long int tmp;
	if (num == 0)
	{
		*size = 1;
		return 1;
	}
	for ( ;tmp_num > 1; tmp_num /= 2, i++);
	tmp = code_f_1(i, &size_tmp);
	i--;
	num ^= (1 << i);
	tmp = (tmp << i) | num;
	*size = i + size_tmp;
	return tmp;
}

void code1_to_file(int *size, long long int *out, int *out_size, FILE *fout)
{
	if (*out_size + *size < LL_INT_SIZE)
	{
		*out = (*out << *size) | 1;
		*out_size += *size;
		*size = 0;
	}
	else
	{
		int tmp_size = LL_INT_SIZE - *out_size;
		*out = (*out << tmp_size);
		fwrite(out, sizeof(long long int), 1, fout);
#if DEBUG >= 1
		printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(*out >> 48));
		printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(*out >> 32));
		printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(*out >> 16));
		printf(""TWO_BYTE_TO_BINARY_PATTERN" WRITE\n", TWO_BYTE_TO_BINARY(*out));
#endif
		*out = 0;
		*size -= tmp_size;
		*out_size = 0;
	}
}

void code_to_file(long long int result, int *size, long long int *out, int *out_size, FILE *fout)
{
	if (*out_size + *size < LL_INT_SIZE)
	{
		*out = (*out << *size) | result;
		*out_size += *size;
		*size = 0;
	}
	else
	{
		long long int tmp = result;
		int tmp_size = LL_INT_SIZE - *out_size;
		*out = (*out << tmp_size) | (tmp >> (*size - tmp_size));
		fwrite(out, sizeof(long long int), 1, fout);
#if DEBUG >= 1
		printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(*out >> 48));
		printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(*out >> 32));
		printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(*out >> 16));
		printf(""TWO_BYTE_TO_BINARY_PATTERN" WRITE\n", TWO_BYTE_TO_BINARY(*out));
#endif
		*out = 0;
		*size -= tmp_size;
		*out_size = 0;
	}
}

int need_swap(int size, unsigned char *t1, unsigned char *t2)
{
	int i;
	i = size-1;
	if (t1[i] >= t2[i])
	{
		if (t1[i] == t2[i])
		{
			return need_swap(i,t1,t2);
		}
		return 1;
	}
	return 0;
}

void inclusion_sort(bwt_t *first, int size)
{
	int i, tmp_i;
	unsigned char *tmp_p = NULL;
	bwt_t *curr = NULL, *tmp = NULL, *tmp2 = NULL;
	curr = first->next;
	for(i = 1; i < size; i++)
	{
		if (curr == NULL || curr->table == NULL)
			break;
		unsigned char value = curr->table[size-2];
		int index = i;
		tmp = curr->prev;
		tmp2 = curr;
		while ((index > 0) && (tmp->table[size-2] >= value))
		{
			if (tmp->table[size-2] != value || need_swap(size-2, tmp->table, tmp2->table))
			{
				tmp_p = tmp2->table;
				tmp_i = tmp2->flag;
				tmp2->table = tmp->table;
				tmp2->flag = tmp->flag;
				tmp->table = tmp_p;
				tmp->flag = tmp_i;
			}
			index --;
			tmp2 = tmp;
			tmp = tmp->prev;
		}
		curr = curr->next;
	}
}
	
bwt_t *bwt(FILE *fin)
{
	unsigned char num_read;
	long long int i = 0, j, k, l, size = 1024;
  	bwt_t *curr = NULL, *first = NULL, *list = NULL;
    b = malloc(sizeof(char)*size);
	while (fscanf (fin, "%c", &num_read) != EOF)
	{
		b[i] = num_read;
		i++;
		if(i == size)
		{
			size += 1024;
			b = realloc(b, sizeof(char)  * size);
		}
	}
	b = realloc(b, sizeof(char) * i * i);
	if (!b)
	{
		printf("File too large. Size: %I64d bit\n", sizeof(char) * i * (i-1));
		exit(-1);
	}

	for (j = 0; j < i; j++)
	{
		curr = malloc(sizeof(bwt_t));
		curr->table = b+i*j;
		curr->prev = NULL;
		curr->next = NULL;
		curr->size = i;
		if (j == 1)
			curr->flag = 1;
		else
			curr->flag = 0;
		if (list == NULL)
		{
			list = curr;
			first = list;
		}
		else
		{
			list->next = curr;
			curr->prev = list;
			list = curr;
		}
	}
	for(j = l = 1, k = i; k < i*i ; k++)
	{
		b[k] = b[j];
		j++;
		if(j == i)
			j = 0;
		if(j == l)
		{
			l++;
			j++;
		}
	}
	
#if DEBUG >= 1
	printf("%I64d size\n", i);
	curr = first;
	while(curr)
	{
		for(j = 0; j < i; j++)
		{
			printf("%d ", curr->table[j]);
		}
		printf("\n");
		curr = curr->next;
	}
#endif
	inclusion_sort(first, i);
#if DEBUG >= 1
	printf("\n\n");
	curr = first;
	while(curr)
	{
		for(j = 0; j < i; j++)
		{
			printf("%d ", curr->table[j]);
		}
		if (curr->flag)
			printf(" first");
		printf("\n");
		curr = curr->next;
	}
#endif
	return first;
}

int coder()
{
	int num, size = 0, out_size = 0, i = 0, pos = 0;
	long long int result, out = 0;
	unsigned char num_read;
	bwt_t *first, *curr;
	FILE *fin = NULL, *fout = NULL;
    if ((fin = fopen(fin_name, "rb")) == NULL)
    {
    	printf("Unable to open file %s\n", fin_name);
    	return -1;
    }
    	
	if ((fout = fopen(fout_name, "wb")) == NULL)
    {
    	printf("Unable to open file %s\n", fout_name);
		fclose(fin);
		return -1;
	}
	preparation();
	first = bwt(fin);
	curr = first;
	switch (code_type)
	{
		case 1:
		{
			while(curr)
			{
				if (curr->flag)
					pos = i;
				i++;
				num_read = curr->table[curr->size-1];
#if DEBUG >= 1
				printf("%d ", num_read);
#endif
				if (num_read == 0)
					printf("a\n");
				num = (int)mtf(num_read);
				if (num_read == 0)
					printf("mtf result %d\n", num);
#if DEBUG >= 1
				printf("mtf result %d\n", num);
#endif
				result = code_f_0(num, &size);
#if DEBUG == 2
				if (num_read == 0)
				{
					printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(result >> 48));
					printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(result >> 32));
					printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(result >> 16));
					printf(""TWO_BYTE_TO_BINARY_PATTERN"\n size = %d\n", TWO_BYTE_TO_BINARY(result), size);
				}
#endif
				while (size > 0)
					code1_to_file(&size, &out, &out_size, fout);
				curr = curr->next;
			}
			break;
		}
		case 2:
		{
			while(curr)
			{
				if (curr->flag)
					pos = i;
				i++;
				num_read = curr->table[curr->size-1];
#if DEBUG >= 1
				printf("%d ", num_read);
#endif
				num = (int)mtf(num_read);
#if DEBUG >= 1
				printf("mtf result %d\n", num);
#endif
				result = code_f_1(num, &size);
#if DEBUG == 2
				printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(result >> 48));
				printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(result >> 32));
				printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(result >> 16));
				printf(""TWO_BYTE_TO_BINARY_PATTERN"\n size = %d\n", TWO_BYTE_TO_BINARY(result), size);
#endif
				while (size > 0)
					code_to_file(result, &size, &out, &out_size, fout);
				curr = curr->next;
			}
			break;
		}
		case 3:
		{
			while(curr)
			{
				if (curr->flag)
					pos = i;
				i++;
				num_read = curr->table[curr->size-1];
#if DEBUG >= 1
				printf("%d ", num_read);
#endif
				num = (int)mtf(num_read);
#if DEBUG >= 1
				printf("mtf result %d\n", num);
#endif
				result = code_f_2(num, &size);
#if DEBUG == 2
				printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(result >> 48));
				printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(result >> 32));
				printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(result >> 16));
				printf(""TWO_BYTE_TO_BINARY_PATTERN"\n size = %d\n", TWO_BYTE_TO_BINARY(result), size);
			
#endif
				while (size > 0)
					code_to_file(result, &size, &out, &out_size, fout);
				curr = curr->next;
			}
			break;
		}
	}
	if (out != 0)
	{
		out <<= (LL_INT_SIZE - out_size);
#if DEBUG == 2
		printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(out >> 48));
		printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(out >> 32));
		printf(""TWO_BYTE_TO_BINARY_PATTERN, TWO_BYTE_TO_BINARY(out >> 16));
		printf(""TWO_BYTE_TO_BINARY_PATTERN" WRITE\n", TWO_BYTE_TO_BINARY(out));
#endif
		fwrite(&out, sizeof(long long int), 1, fout);
		out = out_size = 0;
	}
	printf("\nPosition: %d\n", pos);
    fclose(fout);
    fclose(fin);
    while (first)
    {
    	curr = first->next;
    	free(first);
    	first = curr;
	}
	free(b);
	return 1;
}

int main()
{
	int command;
	while(1)
	{
    	printf("\nMENU\n"
               "1 - Decode\n"
               "2 - Encode\n"
               "3 - Exit\n\n");
    	if (!scanf("%d", &command))
        	return -1;
    	if (command == 3)
        	break;
            
    	printf("\nMENU\n"
               "1 - First code\n"
               "2 - Second code\n"
               "3 - Third code\n"
               "4 - Return\n\n");
    	if (!scanf("%d", &code_type))
        	return -1;
            
    	if (code_type == 4)
        	continue;
    	printf("\nMENU\n"
           "Enter the file name to input\n\n");
    	if (!scanf("%s", fin_name))
        	return -1;
    	if (command == 1 || command == 2)
        {
        	printf("\nMENU\n"
               "Enter the file name to output\n\n");
        	if (!scanf("%s", fout_name))
            	return -1;
        }
        
    	if (command == 2)
        {
        	coder();
        }
    	else
        {
	    	printf("\nMENU\n"
	           "Enter the position\n\n");
        	if (!scanf("%d", &position))
            	return -1;
        	decoder();
        }
    }
    return 1;
}
