#include<iostream>

#define MAX_SIZE 50 + 1
#define NEGATIVE_SIGN 9
#define POSITIVE_SIGN 0

using namespace std;

/// <summary>
/// print one-dimentional array FOR DEBUG
/// </summary>
/// <param name="array"></param>
/// <param name="size"></param>
void print_array(int array[], int size)
{
	printf("\n:");
	for (int i = size - 1; i >= 0; i--)
		//for (int i = 0; i < size; i++)
	{
		printf("%d|", array[i]);
	}
	printf(":\n");
}

/// <summary>
/// count digits in the number only for positive
/// </summary>
/// <param name="array"></param>
/// <param name="size"></param>
/// <returns></returns>
int len(int array[], int size)
{
	int i = size - 1;
	int ZERO_VALUE = array[i];
	// TODO define sign for negative number
	// array[0] != 0  => ZERO_VALUE=9;
	i--;
	// 0 0001
	// 1000 0
	for (; (i >= 0) && (array[i] == ZERO_VALUE); i--)
	{
	}
	return i + 1;
	// 0100 size=4   i=1 res=3
	// revert writen
	// 0010
	// 0123
}
//
//size   = max_size
//size  = current_size

/// <summary>
/// complement encode digits in-place (change sign !!!)
/// </summary>
/// <param name="digits"></param>
/// <param name="size"></param>
void complement(int digits[], int size) //смена знака  --=+
{
	// дополнение до 9
	for (int i = 0; i < size; ++i)
	{
		digits[i] = 9 - digits[i];
	}
	//100 (9910000000)
	//     011
	//101 (0020000000) 
	//+1
	for (int i = 0; i < size; ++i)
		if (digits[i] == 9)
			digits[i] = 0;
		else {
			digits[i]++;
			break;
		}
}

/// <summary>
/// for sub
/// </summary>
/// <param name="digits">digits</param>
/// <param name="size">size</param>
/// <param name="result">complemented digits</param>
void complement(int digits[], int* result, int size) //смена знака  --=+
{
	// дополнение до 9
	for (int i = 0; i < size; ++i)
	{
		result[i] = 9 - digits[i];
	}
	//100 (9910000000)
	//     011
	//101 (0020000000) 
	//+1
	for (int i = 0; i < size; ++i)
		if (result[i] == 9)
			result[i] = 0;
		else
		{
			result[i]++;
			break;
		}
}

/// <summary>
/// Convert to digits.
/// Example:
/// "100"  -> [001000000000000000]  reverse saving 
/// </summary>
/// <param name="number_str"></param>
/// <param name="digits"></param>
/// <param name="size"></param>
void convert_to_digits(const char* number_str, int* digits, int size)
{
	//"100"
	//000000000000000100
	//001000000000000000  reverse saving  !!!
	int sign = 1,
		start_position = 0;
	if (number_str[0] == '-')
	{
		sign = -1;
		start_position = 1;
	}
	int i = strlen(number_str) - 1, j = 0;
	for (; i >= start_position; i--)
	{
		digits[j++] = number_str[i] - '0';
	}
	//DEBUG
	/*print_array(digits, size);*/

	// UNICODE (ASCII)  '0' - AA00, '1' - AA01 ... '9' - AA09
	// символы -> в десятичные эквиваленты
	for (; j < size; ++j)
	{
		digits[j] = 0;//незначащие старшие нули
	}
	//DEBUG print_array(digits, size);
	if (sign == -1)
	{
		complement(digits, size);

		/*digits = complement(digits, size);*/

		//int* temp = complement(digits, size);
		//free digits;
		////digits = null;
		//digits = temp;
	}
	//DEBUG print_array(digits, size);
	cout << endl;
}

/// <summary>
/// convert to string
/// </summary>
/// <param name="digits"></param>
/// <param name="size"></param>
/// <param name="str"></param>
void convert_to_str(int digits[], char* str, int size) {
	int sign = 0;
	if (digits[size - 1] >= NEGATIVE_SIGN)
	{ // признак отрицательного числа
		sign = 1;
		complement(digits, size);
		str[0] = '-';
		//cout << '-';
	}
	//else
	//{
	//	str[0] = '+';
	//}
	int i = size - 1;
	while (i > 0 && digits[i] == 0)//пропустили незначащие нули
	{
		i--;
	}
	int j = sign;
	for (; i >= 0; --i)
	{
		str[j++] = '0' + digits[i];
	}
	str[j] = '\0';
	//cout << a[i];
	/*if (sign == -1) = нак*/
}

/// <summary>
/// TODO: docstring and test
/// right_shift for revert written digits
/// check negative
/// </summary>
/// <param name="digits"></param>
/// <param name="length"></param>
/// <param name="size"></param>
void left_shift(int digits[], int length, const int size)
{
	if (len(digits, size) + length >= size)
	{
		cout << "Warning: overflow!" << endl;
		return;
	}
	// TODO:
	// 0     1011 ->  
	// 0 (1) 0110 
	//i |

	// size = 5
	// 4  3210
	// 0  0012 -> 
	//i    |  
	// 0  0112 
	//i      | 
	// 0  0122
	//i       | 
	// 0  0120 
	for (size_t i = size - 2; i > 0; i--)
	{
		digits[i] = digits[i - 1];
	}
	digits[0] = 0;
}

/// <summary>
/// get sub digit from left of the size
/// Examples:
///  00001231236876  length=3 -> result 0000000000123
///  99991231236876  length=3 -> result 9999999999123
/// </summary>
/// <param name="digits"></param>
/// <param name="result"></param>
/// <param name="size"></param>
/// <param name="length"></param>
void sub_digits(int digits[], int result[], int length, const int size)
{
	//  0 1 2 3     size-1
	/// 99991231236876  length=3 -> result 9999999999123
	//                                    
	// i    |                                        |   j
	int i = size - 1, j = size - 1;
	int sign = POSITIVE_SIGN;
	//print_array(digits, size);
	if (digits[i] != POSITIVE_SIGN)
	{
		sign = NEGATIVE_SIGN;
	}
	while (digits[i] == sign)
	{
		i--;
	}
	if (i + length >= size)
	{
		//warning
		return;
	}
	for (j = size - 1; j > length - 1; j--)
	{
		result[j] = sign;
	}
	//print_array(result, size);

	// sub_digit
	while (j >= 0)
	{
		result[j] = digits[i];
		i--;
		j--;
		//result[j + size - size] = digits[i]; i++;
	}
	//print_array(result, size);
}

/// <summary>
/// TODO
/// </summary>
/// <param name="first_operand"></param>
/// <param name="second_operand"></param>
/// <param name="size"></param>
/// <returns></returns>
int compare_digits(const int first_operand[], const int second_operand[], const int size)
{
	int result = 0;
	// different signs
	int i = size - 1;
	if (first_operand[i] != second_operand[i])
	{
		if (first_operand[i] == POSITIVE_SIGN)
		{
			result = 1;
		}
		else
		{
			result = -1;
		}
		return result;
	}
	// same signs
	bool is_positive = true;
	if (first_operand[i] != POSITIVE_SIGN)  //  is_neg(first_operand)
	{
		is_positive = false;
	}
	i--;
	for (; (first_operand[i] == second_operand[i]); i--)
	{
		if (i < 0)
		{
			result = 0;
			return result;
		}
	}
	bool gt = first_operand[i] > second_operand[i];
	if (gt)
	{
		result = 1;
	}
	else
	{
		result = -1;
	}
	//if (is_positive)
	//{
	//	if (first_operand[i] > second_operand[i])   //gt +  is_positive +
	//	{
	//		result = 1;                             //result +
	//	}
	//	else										//gt -  is_positive +
	//	{
	//		result = -1;                            //result -
	//	}
	//}
	//else
	//{
	//	// -12 <> -13    9987  <> 9986
	//	if (first_operand[i] > second_operand[i])    //gt +  is_positive -
	//	{
	//		result = 1;                              //result +
	//	}
	//	else										 //gt -  is_positive -
	//	{
	//		result = -1;                             //result -
	//	}
	//}*/
	return result;
}

/// <summary>
/// left_operand = right_operand
/// </summary>
/// <param name="left_operand"></param>
/// <param name="right_operand"></param>
/// <param name="size"></param>
void copy_digits(int left_operand[], const int right_operand[], int size = MAX_SIZE)
{
	for (int i = 0; i < size; i++)
	{
		left_operand[i] = right_operand[i];
	}
}

bool is_neg(int digits[], int size = MAX_SIZE)
{
	return digits[size - 1] == NEGATIVE_SIGN;
}

/// <summary>
/// adding two complemented numbers
/// </summary>
/// <param name="dest">dest=a+b</param>
/// <param name="first_operand">a</param>
/// <param name="second_operand">b</param>
void add_digits(int dest[], const int first_operand[], const int second_operand[], const int size)
{
	int one_in_memory = 0;
	//print_array(a, MAX_SIZE);//DEBUG
	//print_array(b, MAX_SIZE);//DEBUG
	for (int i = 0; i < size; ++i)
	{
		int rank_sum = first_operand[i] + second_operand[i] + one_in_memory;
		/*dest[i] = rank_sum % 10;
		one_in_memory = rank_sum / 10;*/
		if (rank_sum >= 10)
		{
			dest[i] = rank_sum % 10;
			one_in_memory = 1;
		}
		else
		{
			dest[i] = rank_sum;
			one_in_memory = 0;
		}
		//cout << i << ' ' << rank_sum << ' ' << one_in_memory << endl;//DEBUG
		//print_array(dest, MAX_SIZE);//DEBUG
	}
}

/// <summary>
/// submit
/// </summary>
/// <param name="dest"></param>
/// <param name="first_operand"></param>
/// <param name="second_operand"></param>
/// <param name="size"></param>
void sub(int dest[], int first_operand[], int second_operand[], int size) {//dest=a+(-b)
	int* temp = new int[size];
	complement(second_operand, temp, size);
	add_digits(dest, first_operand, temp, size);
	delete[] temp; //free(temp); 
	temp = nullptr;
}

/// <summary>
/// multiply
/// </summary>
/// <param name="dest"></param>
/// <param name="first_operand"></param>
/// <param name="second_operand"></param>
/// <param name="size"></param>
void multiply(int dest[], int first_operand[], int second_operand[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		dest[i] = 0;
	}
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; i + j < size; ++j)
		{
			int t = first_operand[i] * second_operand[j] + dest[i + j];
			dest[i + j] = t % 10;
			if (i + j + 1 < size)
			{
				dest[i + j + 1] += t / 10;
			}
		}
	}
}

void div_digits(int result_quotient[], int result_remainder[], int first_operand[], int second_operand[], int size = MAX_SIZE)
{
	// initialisation with zeros
	for (size_t j = 0; j < size; j++)
	{
		result_quotient[j] = 0;
	}
	for (size_t j = 0; j < size; j++)
	{
		result_remainder[j] = 0;
	}

	int length_1st = len(first_operand, size);
	if (length_1st > size - 1)
	{
		cout << "Warning: first operand grater than size" << endl;
		return;
	}
	int length_2nd = len(second_operand, size);
	if (length_2nd > size - 1)
	{
		cout << "Warning: second operand grater than size" << endl;
		return;
	}
	/// -a b    a -b -> result_sign = -    a b -a -b -> result_sign = +
	// ||a|| / ||b||
	int i = 0/*, j = 0, k = 0*/; // indexes from the end!!!

	// -+ - 0 9   (-1) * 1 
	// +- - 
	// -- + 1
	// ++ +   0   !(a_is_nef XOR b_is_neg)  - XOR -
	int res_sign = POSITIVE_SIGN;
	//bool f_is_neg = is_neg(first_operand);
	if (is_neg(first_operand, size) ^ is_neg(second_operand, size))
	{
		res_sign = NEGATIVE_SIGN;
	}

	int* first = new int[size];
	int* second = new int[size];
	copy_digits(first, first_operand, size);
	copy_digits(second, second_operand, size);

	//abs (complement) with copies of operands
	if (is_neg(first_operand, size))
	{
		complement(first, size);
	}
	if (is_neg(second_operand, size))
	{
		complement(second, size);
	}

	/// special case when first < second 
	if (compare_digits(first, second, size) == -1)
	{
		///result_quotient =0 
		copy_digits(result_remainder, first, size);
		return;
	}

	// only positive numbers
	// first = 000000000123 4 788   | second = 000000223
	int* sub_divident = new int[size];
	sub_digits(first, sub_divident, length_2nd, size); //sub_divident = ...

	// indexes:         654 3 210
	// first = 000000000447 4 788   | second = 000000223
	//                  446         | 000002121234|   0_____       
	//                   14 4
	//                      0
	//                    1 4 7     
	// i                      |
	//  temp = 669 > 447    remainder (1) = 447 - 446
	i = len(first, size) - length_2nd; // indexing from the end !!!
	// a<b ---  cmp(a,b) <0
	int* digit_tmp_previous = new int[size];
	int* digit_tmp = new int[size];
	int n;
	// loop
	while (i >= 0) {

#pragma region next_quotient_digit
		// temp=second, previous_temp=0       n=0       ? temp<sub_divident        
		// previous_temp = temp 
		// temp =previous_temp + second    (n++) n=1    ? temp<sub_divident
		// previous_temp = temp
		// temp =previous_temp + second    (n++) n=2    ? temp<sub_divident
		// previous_temp = temp
		// temp =previous_temp + second        n=3      ? temp<sub_divident  true 
		// 
		//  remainder = sub_divident - previous_temp


		// initialisation digit_tmp_previous
		for (size_t j = 0; j <= size; j++)
		{
			digit_tmp_previous[j] = 0;
		}
		copy_digits(digit_tmp, second, size);
		// 12//4  4+4+4+4 +4
		// accumulation like soft multiple
		for (n = 0; compare_digits(digit_tmp, sub_divident, size) <= 0; n++) //temp<=sub_divident
		{
			copy_digits(digit_tmp_previous, digit_tmp, size);
			add_digits(digit_tmp, digit_tmp_previous, second, size);
		}
		//remainder
		sub(sub_divident, sub_divident, digit_tmp_previous, size);
#pragma endregion
		// 132/4   | n=3
		// 12 
		//  1(2)
		// 9999  |1000 0
		//        n
		// 8888 9 | 9999 0
		// 
	// left shift
	// res[0] = n

		left_shift(result_quotient, 1, size);
		result_quotient[0] = n;
		//  00001  -> 00010  ->  sub_divident[0] = first[i--]  (2)
		if (i == 0)
		{
			break;
		}
		left_shift(sub_divident, 1, size);
		sub_divident[0] = first[--i];
	}
	// TODO: do we need to complement remainder?
	//result_remainder = sub_divident; // copy digits
	copy_digits(result_remainder, sub_divident, size);

	if (res_sign == NEGATIVE_SIGN)
	{
		complement(result_quotient, size);
	}
}

int main()
{
	int first_operand[MAX_SIZE];
	int second_operand[MAX_SIZE];
	int result[MAX_SIZE];
	int result2[MAX_SIZE];
	char temp_str[MAX_SIZE + 1];//1 байт на знак и 1 байт на '\0'

	printf("Enter a:");
	scanf_s("%s", temp_str, MAX_SIZE + 1);
	convert_to_digits(temp_str, first_operand, MAX_SIZE);
	//print_array(first_operand, MAX_SIZE ); to show

	//convert_to_str(a, MAX_SIZE , s);

	//cout << "\n" << s  << endl;
	//complement();
	printf("Enter b:");
	scanf_s("%s", temp_str, MAX_SIZE + 1);
	convert_to_digits(temp_str, second_operand, MAX_SIZE);
	//print_array(second_operand, MAX_SIZE);

	//a+b
	add_digits(result, first_operand, second_operand, MAX_SIZE);
	convert_to_str(result, temp_str, MAX_SIZE);
	printf("a+b=%s\n", temp_str);
	//a-b
	sub(result, first_operand, second_operand, MAX_SIZE);
	convert_to_str(result, temp_str, MAX_SIZE);
	printf("a-b=%s\n", temp_str);
	//b-a
	sub(result, second_operand, first_operand, MAX_SIZE);
	convert_to_str(result, temp_str, MAX_SIZE);
	printf("b-a=%s\n", temp_str);
	//a*b
	multiply(result, first_operand, second_operand, MAX_SIZE);
	//print_array(result, MAX_SIZE); DEBUG
	convert_to_str(result, temp_str, MAX_SIZE);
	printf("a*b=%s\n", temp_str);
	//a div b
	div_digits(result, result2, first_operand, second_operand, MAX_SIZE);
	convert_to_str(result, temp_str, MAX_SIZE);
	printf("a div b=%s\n", temp_str);
	//a mod b 
	convert_to_str(result2, temp_str, MAX_SIZE);
	printf("a mod b=%s\n", temp_str);
	//b div a
	div_digits(result, result2, second_operand, first_operand, MAX_SIZE);
	convert_to_str(result, temp_str, MAX_SIZE);
	printf("b div a=%s\n", temp_str);
	//b mod a
	convert_to_str(result2, temp_str, MAX_SIZE);
	printf("b mod a=%s\n", temp_str);


	/// / /// / // // / / /DEBUG
	/*printf("a=");
	scanf_s("%s", temp_str, MAX_SIZE + 1);
	convert_to_digits(temp_str, first_operand, MAX_SIZE);
	//second_operand = sub_str(first_operand, 4)
	print_array(first_operand, MAX_SIZE);
	int temp_int = 4;
	//sub_digits(first_operand, second_operand, temp_int, MAX_SIZE);
	//print_array(second_operand,MAX_SIZE);
	//convert_to_str(second_operand, temp_str, MAX_SIZE);
	//printf("a sub_digits %d =%s\n", temp_int, temp_str);

	printf("b=");
	scanf_s("%s", temp_str, MAX_SIZE + 1);
	convert_to_digits(temp_str, second_operand, MAX_SIZE);
	print_array(second_operand, MAX_SIZE);
	//print_array(second_operand, MAX_SIZE);

	temp_int = compare_digits(first_operand, second_operand, MAX_SIZE);
	printf("%s\n", temp_int > 0 ? "greater than" : (temp_int < 0 ? "less than" : "equals"));*/

}