/*
 * Sudoku.cpp
 *
 */

#include "Sudoku.h"

/** Inicia um Sudoku vazio.
 */
Sudoku::Sudoku()
{
	this->initialize();
}

/**
 * Inicia um Sudoku com um conteúdo inicial.
 * Lança excepção IllegalArgumentException se os valores
 * estiverem fora da gama de 1 a 9 ou se existirem números repetidos
 * por linha, coluna ou bloc 3x3.
 *
 * @param nums matriz com os valores iniciais (0 significa por preencher)
 */
Sudoku::Sudoku(int nums[9][9])
{
	this->initialize();

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (nums[i][j] != 0)
			{
				int n = nums[i][j];
				numbers[i][j] = n;
				lineHasNumber[i][n] = true;
				columnHasNumber[j][n] = true;
				block3x3HasNumber[i / 3][j / 3][n] = true;
				countFilled++;
			}
		}
	}
}

void Sudoku::initialize()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int n = 0; n < 10; n++)
			{
				numbers[i][j] = 0;
				lineHasNumber[i][n] = false;
				columnHasNumber[j][n] = false;
				block3x3HasNumber[i / 3][j / 3][n] = false;
			}
		}
	}

	this->countFilled = 0;
}

/**
 * Obtem o conteúdo actual (só para leitura!).
 */
int** Sudoku::getNumbers()
{
	int** ret = new int*[9];

	for (int i = 0; i < 9; i++)
	{
		ret[i] = new int[9];

		for (int a = 0; a < 9; a++)
			ret[i][a] = numbers[i][a];
	}

	return ret;
}

///**
// * Verifica se o Sudoku já está completamente resolvido
// */
//bool Sudoku::isComplete()
//{
//	return (countFilled == 81);
//}
//
//
//
///**
// * Resolve o Sudoku.
// * Retorna indicação de sucesso ou insucesso (sudoku impossível).
// */
//bool Sudoku::solve()
//{
////    this->print();
//    if (this->isComplete()) return true;
//    int bestI, bestJ;
//
//    if (!findBestCell(bestI, bestJ)) return false;
//
////    cout << endl << rightN << ": " << bestI << ", " << bestJ << endl;
////    this->print();
//
//    for (int n = 1; n <= 9; n++) {
//        if (accept(bestI, bestJ, n)) {
//            place(bestI, bestJ, n);
//            if (solve())
//                return true;
//            else
//                clear(bestI, bestJ);
//        }
//    }
//    return false;
//}
//
//
//
///**
// * Imprime o Sudoku.
// */
//void Sudoku::print()
//{
//	for (int i = 0; i < 9; i++)
//	{
//		for (int a = 0; a < 9; a++)
//			cout << this->numbers[i][a] << " ";
//
//		cout << endl;
//	}
//}
//
//bool Sudoku::findBestCell(int &bestI, int &bestJ) {
//    bestI = -1;
//    bestJ = -1;
//    int bestCellCandidate = 10;
//
//    for (int i = 0; i < 9; i++) {
//        for (int j = 0; j < 9; j++) {
//            if (!numbers[i][j]) {
//                int numCandidates = 0;
//                for (int n = 1; n <= 9; n++)
//                    if (this->accept(i, j, n))
//                        numCandidates++;
//                if (bestCellCandidate > numCandidates) {
//                    bestCellCandidate = numCandidates;
//                    bestI = i;
//                    bestJ = j;
//                    if (numCandidates == 1)
//                        return true;
//                }
//            }
//        }
//    }
//    return bestI >= 0;
//}
//
//bool Sudoku::accept(int i, int j, int n) {
//    return (!columnHasNumber[j][n] && !lineHasNumber[i][n] && !block3x3HasNumber[i/3][j/3][n]);
//}
//
//void Sudoku::place(int i, int j, int n) {
//    numbers[i][j] = n;
//    columnHasNumber[j][n] = true;
//    lineHasNumber[i][n] = true;
//    block3x3HasNumber[i/3][i/3][n] = true;
//    countFilled++;
//}
//
//void Sudoku::clear(int i, int j) {
//    columnHasNumber[j][numbers[i][j]] = false;
//    lineHasNumber[i][numbers[i][j]] = false;
//    block3x3HasNumber[i/3][j/3][numbers[i][j]] = false;
//    numbers[i][j] = 0;
//    countFilled--;
//}
//
//

bool Sudoku::solve(){
    if (isComplete())
        return true; // success, terminate

        // Greedy approach: searches the best cell to fill in
        // (with a minimum number of candidates)
    int i, j;

    if ( ! findBestCell(i, j) )
        return false; // impossible, backtrack

    // Tries all the possible candidates in the chosen cell
    for (int n = 1; n <= 9; n++)
        if (accept(i, j, n)) {
            place(i, j, n);
            if (solve())
                return true; // success, terminate
            clear(i, j);
        }
    return false; // impossible, backtrack
}
/**
 * Searches the best cell to fill in - the cell with
 * a minimum number of candidates.
 * Returns true if found and false otherwise (Sudoku impossible).
 */
bool Sudoku::findBestCell(int & best_i, int & best_j)
{
    best_i = -1, best_j = -1;
    int best_num_choices = 10; // above maximum
    for (int i = 0; i < 9 ; i++)
        for (int j = 0; j < 9; j++)
            if (numbers[i][j] == 0) {
                int num_choices = 0;
                for (int n = 1; n <= 9; n++)
                    if (accept(i, j, n))
                        num_choices++;
                if (num_choices == 0)
                    return false; // impossible
                if (num_choices < best_num_choices) {
                    best_num_choices = num_choices;
                    best_i = i;
                    best_j = j;
                    if (num_choices == 1) // cannot improve
                        return true;
                } }
    return best_i >= 0;
}
/**
 * Checks if the cell at line i, column j accepts number n
 */
bool Sudoku::accept(int i, int j, int n)
{
    return !lineHasNumber[i][n]
           && !columnHasNumber[j][n]
           && !block3x3HasNumber[i / 3][j / 3][n];
}
/**
 * Fills in the cell at line i, column j with number n.
 * Also updates the cell counter.
 */
void Sudoku::place(int i, int j, int n)
{
    numbers[i][j] = n;

    lineHasNumber[i][n] = true;
    columnHasNumber[j][n] = true;
    block3x3HasNumber[i / 3][j / 3][n] = true;
    countFilled++;
}


/**
* Clears the cell at line i, column j.
* Also updates the cell counter.
*/
void Sudoku::clear(int i, int j) {



    lineHasNumber[i][numbers[i][j]] = false;
    columnHasNumber[j][numbers[i][j]] = false;
    block3x3HasNumber[i / 3][j / 3][numbers[i][j]] = false;
    numbers[i][j] = 0;
    countFilled--;
}
/**
* Checks if the Sudoku is completely solved.
*/
bool Sudoku::isComplete()
{
    return countFilled == 9 * 9;
}




