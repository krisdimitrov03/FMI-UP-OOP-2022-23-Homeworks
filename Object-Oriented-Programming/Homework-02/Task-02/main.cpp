#include <iostream>
#include "StringCreatorPieceByPiece.h"

int main()
{
	StringCreatorPieceByPiece sc(2);

	sc.addPiece("test");
	sc.addPiece();
	sc.addPiece("football");

	sc[1] << " friends ";
	" Hello " >> sc[1];
	10 >> sc[2];

	MyString result1 = sc.getString();
	std::cout << result1 << std::endl;

	sc.swapPieces(1, 2);
	MyString result2 = sc.getString();
	std::cout << result2 << std::endl;

	sc.removePiece(1);
	MyString result3 = sc.getString();
	std::cout << result3 << std::endl;
}