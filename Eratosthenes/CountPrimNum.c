#include<stdio.h> //Ziel Programm zu schreiben, die Prims zwischen 1 und 120 ermittelt
	
int CountPrimNum(int anfang, int ende, char* parr){
	int result = 0;
	
	for (int i = anfang; i <= ende; i++) {
		result += parr[i];
	}
	
	return result;
}
