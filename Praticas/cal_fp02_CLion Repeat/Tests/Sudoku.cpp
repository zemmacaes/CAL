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
				cellCandidates[i][j][n] = 0;
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

/**
 * Verifica se o Sudoku já está completamente resolvido
 */
bool Sudoku::isComplete()
{
	return countFilled == 9 * 9;
}



/**
 * Resolve o Sudoku.
 * Retorna indicação de sucesso ou insucesso (sudoku impossível).
 */
bool Sudoku::solve() {
    initialize();
    return solver();
}


/**
 * Imprime o Sudoku.
 */
void Sudoku::print()
{
	for (int i = 0; i < 9; i++)
	{
		for (int a = 0; a < 9; a++)
			cout << this->numbers[i][a] << " ";

		cout << endl;
	}
}

bool Sudoku::isCandidate(int num, int x, int y) {
    return !columnHasNumber[x][num] && !lineHasNumber[y][num] && !block3x3HasNumber[x/3][y/3][num];
}

void Sudoku::numCandidatesCell(int x, int y) {
    for (int i = 1; i <= 10; i++) {
        if (isCandidate(i, x, y)) {
            cellCandidates[x][y][i] = i;
            cellCandidates[x][y][0]++;
        }
    }
}

bool Sudoku::solver() {
    if (isComplete()) {
        return true;
    }
    bool impossible = true;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (numbers[i][j] == 0) {
                numCandidatesCell(i, j);
                if (cellCandidates[i][j][0] > 0) impossible = false;
                else if (cellCandidates[i][j][0] == 1) {
                    numbers[i][j] = cellCandidates[i][j][1];
                    lineHasNumber[j][cellCandidates[i][j][1]] = true;
                    columnHasNumber[i][cellCandidates[i][j][1]] = true;
                    block3x3HasNumber[i / 3][j / 3][cellCandidates[i][j][1]] = true;
                    countFilled++;
                    if (solver()) {
                        return true;
                    }
                }
                if (cellCandidates[i][j][0] > 1) {
                    for (int k = 1; k <= cellCandidates[i][j][0]; k++) {
                        numbers[i][j] = cellCandidates[i][j][k];
                        lineHasNumber[j][cellCandidates[i][j][k]] = true;
                        columnHasNumber[i][cellCandidates[i][j][k]] = true;
                        block3x3HasNumber[i / 3][j / 3][cellCandidates[i][j][k]] = true;
                        countFilled++;
                        if (solver()) {
                            return true;
                        }
                        numbers[i][j] = 0;
                        lineHasNumber[j][cellCandidates[i][j][k]] = false;
                        columnHasNumber[i][cellCandidates[i][j][k]] = false;
                        block3x3HasNumber[i / 3][j / 3][cellCandidates[i][j][k]] = false;
                        countFilled--;
                    }
                }
            }
        }
    }

    if (impossible) return false;
}
