#include "Jaura.h"
#include "Types.h"
#include "Errors.h"

void memset(void *dest, char chr, UINT count){
	char *pdest = dest;	
	while(count){
		*(char*)pdest = chr;
		pdest++;
		count--;
	}
}

char *strrev(char *str){
      char* strl;
      char* strr = str;
      char tmp;
      //count len
      while(*strr){
         strr++;
      }
      strr--;
      strl = str;
      while(strl < strr){
         tmp = *strr;
         *strr = *strl;
         *strl = tmp;
         strl++;
         strr--;
      }
      return str;
}

char * ultostr(char *str,unsigned long val, int base){
	char *res = str;
	if(base>36){
		*str = 0;
		return str; 
	}
	
	do{
		*str = "0123456789abcdefghijklmnopqrstuvwxyz"[val%base];
		val /= base;
		str++;
	}while(val);
	*str = 0;
	strrev(res);
}

char * ltostr(char *str,signed long val, int base){
	char *res = str;
	signed long num = val;
	val = val < 0 ? -val:val;
	if(base>36){
		*str = 0;
		return str; 
	}
	do{
		*str = "0123456789abcdefghijklmnopqrstuvwxyz"[val%base];
		val /= base;
		str++;
	}while(val);
	if(num < 0){*str = '-'; str++;}
	*str = 0;
	strrev(res);
}


int StrCompare(PCHAR str1, PCHAR str2){
	for(;*str1 == *str2; str1++, str2++){
		if(!(*str1)) return 0;
	}
	if(*str1 < *str2)return -1;
	else return 1;
}

PCHAR StrCopy(PCHAR dest, PCHAR src){
	PCHAR tmp = dest;
	while(*src){
		*dest = *src;
		dest++;
		src++;
	}
	return tmp;
}

void StrJoin(PCHAR dest, PCHAR src){
	while(*dest) dest++;
	while(*src){
		*dest = *src;
		dest++;
		src++;
	}
}

PCHAR StrReverse(PCHAR str){
      PCHAR strl;
      PCHAR strr = str;
      int len;
      char tmp;
      //count len
      while(*strr){
         len++;
         strr++;
      }
      strr--;
      strl = str;
      while(strl < strr){
         tmp = *strr;
         *strr = *strl;
         *strl = tmp;
         strl++;
         strr--;
      }
      return str;
}

PCHAR StrUpper(PCHAR str){
	PCHAR tmp = str;
	while(*str){
		if((*str > 'a') && (*str < 'z')) *str -= 0x20;
		str++;
	}
	return tmp;
}

PCHAR StrLower(PCHAR str){
	PCHAR tmp = str;
	while(*str){
		if((*str > 'A') && (*str < 'Z')) *str += 0x20;
		str++;
	}
	return tmp;
}

UINT StrLength(PCHAR str){
	UINT slen = 0;
	while(*str){
		slen++;
		str++;
	}
	return slen;
}

int MemCompare(void* mem1, void* mem2, UINT size){
	PCHAR ptr1 = (PCHAR)mem1;
	PCHAR ptr2 = (PCHAR)mem2;
	while(size){
		if(*ptr1 != *ptr2){
			if(*ptr1 < *ptr2)return -1;
			else return 1;
		}
		ptr1++;
		ptr2++;
		size--;
	}
	return 0;
}

void MemCopy(void* dest, void *src, UINT count){
char *pdest = dest, *psrc = src;	
	while(count){
		*pdest = *psrc;
		pdest++;
		psrc++;
		count--;
	}
}

void MemFill(PVOID dest, char chr, UINT count){
	char *pdest = dest;	
	while(count){
		*(char*)pdest = chr;
		pdest++;
		count--;
	}
}

int AscToInt(PCHAR str, int base){
	int result = 0;
	char sign = 0;

	if ((base < 2) && (base > 36))
		return 0;
	
	if(*str == '-'){
		sign = 1;
		str++;
	}
	
	while(*str){
		if((*str <= '9') && (*str >= '0')){
			result *= base;
			result += *str - '0';
			str++;
		}
		else if ((*str >= 'a') && (*str <= 'z')){
			result *= base;
			if (*str - 'a' + 10 >= base)
				return 0;
			result += *str - 'a' + 10;
			str++;
		}
		else if ((*str >= 'A') && (*str <= 'Z')){
			result *= base;
			if (*str - 'A' + 10 >= base)
				return 0;
			result += *str - 'A' + 10;
			str++;
		}
		else if ((*str == ' ') || (*str == '\t') || (*str == '\n')){
			str++;
		}
		else return 0; //error
	}
	if(sign)
		return -result;
	else
		return result;
}

int AscToUint(PCHAR str, int base){
	unsigned int result = 0;

	if ((base < 2) && (base > 36))
		return 0;

	while(*str){
		if((*str <= '9') && (*str >= '0')){
			result *= base;
			result += *str - '0';
			str++;
		}
		else if ((*str >= 'a') && (*str <= 'z')){
			result *= base;
			if (*str - 'a' + 10 >= base)
				return 0;
			result += *str - 'a' + 10;
			str++;
		}
		else if ((*str >= 'A') && (*str <= 'Z')){
			result *= base;
			if (*str - 'A' + 10 >= base)
				return 0;
			result += *str - 'A' + 10;
			str++;
		}
		else if ((*str == ' ') || (*str == '\t') || (*str == '\n')){
			str++;
		}
		else return 0; //error
	}
	return result;
}

void UintToAsc(unsigned int number, char *asc, int base)
{
	char *str = asc;
	char num;
	
	if ((base < 2) && (base > 36)){
		*asc = 0;
		return;
	}
	
	do{
		num = (char) (number % base);
		if (num < 10)
			*str = num + '0';
		else
			*str = num - 10 + 'a';
		str++;
		number /= base;
	}while (number != 0);
	*str = 0;
	StrReverse(asc);
}

void IntToAsc(int number, char *asc, int base)
{
	char *str = asc;
	char sign = 0;
	char num;
	
	if ((base < 2) && (base > 36)){
		*asc = 0;
		return;
	}
	
	if (number < 0){
		sign = 1;
		number = -number;
	}
	
	do{
		num = (char) (number % base);
		if (num < 10)
			*str = num + '0';
		else
			*str = num - 10 + 'a';
		str++;
		number /= base;
	}while (number != 0);
	
	if (sign){
		*str = '-';
		str++;
	}
	*str = 0;
	StrReverse(asc);
}

void PortOut8(USHORT port, UCHAR data){
	__asm__("mov dx,%0"::"g"(port));
	__asm__("mov al,%0"::"g"(data));
	__asm__("out dx,al");
}

UCHAR PortIn8(USHORT port){
	__asm__("mov dx,%0"::"g"(port));
	__asm__("in al,dx");
}

void PortOut16(USHORT port, USHORT data){
	__asm__("mov dx,%0"::"g"(port));
	__asm__("mov ax,%0"::"g"(data));
	__asm__("out dx,ax");
}

USHORT PortIn16(USHORT port){
	__asm__("mov dx,%0"::"g"(port));
	__asm__("in ax,dx");
}
