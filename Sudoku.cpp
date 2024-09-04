#include <iostream>
#include <string>
using namespace std;

class Boarddata{
    public:
		bool column[9][9];
		bool row[9][9];
		bool square[3][3][9];
		int board_main[9][9];
		bool board_input[9][9];
		int singleDimensionBoard[81];
	};


void get_info( Boarddata &board_data );
void calculate_solution( Boarddata &board_data );
void output_board( Boarddata &board_data );
bool cell_value_passes( int cellPosition, int value, Boarddata &board_data );
void initialize_arrays( Boarddata &board_data );
void saveCellValue( int positionInCells, int test_value, Boarddata &board_data );
void resetCellValue( int positionInCells, Boarddata &board_data );
int main()	{
	Boarddata board_data;
	

	//------------
	//start program
	//------------		
	initialize_arrays( board_data );				
	get_info( board_data );
	calculate_solution( board_data );
	output_board( board_data );
	
	//-----------
	//end program
	//-----------
	
	//testing
	return 0;
}


void get_info( Boarddata &board_data )	{
	
	string input_string;
	int x, y, value;
	value = 1;
	
	cout << "Sudoku solver! Enter the coordinates of every number you know of in a 9x9 sudoku board.\n";
	cout << "Input the numbers like this: [number],[y coordinate],[x coordinate]. Type 0 to exit.\n";
	
	//gets all the set values.
	while ( value > 0 )	{
		cout << "Enter: ";
		getline( cin, input_string );
		value = input_string[0]-48;
		x = input_string[4]-48;
		y = input_string[2]-48;
							
		if (!value)
			break;

		//places the values in the board
		cout << value << " (" << y << ", " << x << ")\n";
		board_data.board_main [ y-1 ][ x-1 ] = value;
		
		//-----------
		//creating book-keeping arrays
		//-----------
		board_data.column[x-1][value-1] = true;
		board_data.row[y-1][value-1] = true;
		board_data.square[(y-1)/3][(x-1)/3][value-1] = true;
		board_data.board_input[y-1][x-1] = true;	
	}
	
	for ( int loop1 = 0; loop1<9; loop1++ )	{
		for ( int loop2 = 0; loop2<9; loop2++ )	{
			board_data.singleDimensionBoard[9*loop1 + loop2] = board_data.board_main[loop1][loop2];
		}
	}
}



void calculate_solution( Boarddata &board_data ) {
	int positionInCells = 0;
	bool cellPassed;
	while ( positionInCells <= 80 )	{
				
		cout << "\n" << positionInCells;
		cellPassed = false;
		// Skip if user input cell
		// the value has been input by user and is fixed
		if ( board_data.board_input[positionInCells/9][positionInCells%9] )	{
			positionInCells++;
			continue;
		}
		int currentCellValue = board_data.singleDimensionBoard[positionInCells];
		resetCellValue( positionInCells, board_data );
			
		cout << " - ";
		// Cycle through the different cells until
		for ( int test_value = (currentCellValue + 1); test_value <= 9; test_value++ )	{
			cout << test_value;
			if ( cell_value_passes( positionInCells, test_value, board_data ) )	{
				saveCellValue( positionInCells, test_value, board_data );
				
				cellPassed = true;
				positionInCells++;
				break;
			}
		}
		if ( cellPassed )	
			continue;
		positionInCells--;
		
		while ( board_data.board_input[positionInCells/9][positionInCells%9] ) 
			positionInCells--;
							
		// By the way:
		// y = val/9
		// x = val%9
	}
}



void output_board( Boarddata &board_data ) {
	for ( int cycleThroughRows = 0; cycleThroughRows <= 8; cycleThroughRows++ ) {
		for ( int cycleThroughColumns = 0; cycleThroughColumns <=8; cycleThroughColumns++ ) {
			board_data.board_main[cycleThroughRows][cycleThroughColumns] = board_data.singleDimensionBoard[9*cycleThroughRows+cycleThroughColumns];
		}
	}
	int loop1, loop2;
	for ( loop1 = 0; loop1 < 9; loop1 ++ )	{
		cout << "\n";
		for ( loop2 = 0; loop2 < 9; loop2 ++ )	{
			cout << board_data.board_main[loop1][loop2];
		}
	}
}


// --------
// Checks the value of a cell for conflicts within the board
// Returns 0: fails-conflict
// Returns 1: passes-no conflict
// ---------
bool cell_value_passes ( int cellPosition, int value, Boarddata &board_data ) {
	int y, x;
	y = cellPosition/9;
	x = cellPosition%9;
	
	
	// fail if value is in this column
	if ( board_data.column[x][value-1] == true )
		return 0;
	
	// fail if value is in this row
	if ( board_data.row[y][value-1] == true )
		return 0;
		
	// fail if value in this square
	if ( board_data.square[y/3][x/3][value-1] == true )
		return 0;

	// passes all conditions; current value is good.
	return 1;

}


void initialize_arrays( Boarddata &board_data )	{
	//------------
	//initialize the array
	//------------
	int loop1, loop2, loop3;
	
	
	for ( loop1 = 0; loop1<9; loop1++ )	{
		for ( loop2 = 0; loop2 < 9; loop2++ )	{
			board_data.board_main[loop1][loop2] = 0;
		}
	}	
	
	for ( loop1 = 0; loop1<9; loop1++ )	{
		for ( loop2 = 0; loop2 < 9; loop2++ )	{
			board_data.board_input[loop1][loop2] = false;
		}
	}	
	
	for ( loop1 = 0; loop1<9; loop1++ )	{
		for ( loop2 = 0; loop2 < 9; loop2++ )	{
			board_data.row[loop1][loop2] = false;
		}
	}	
	
	for ( loop1 = 0; loop1<9; loop1++ )	{
		for ( loop2 = 0; loop2 < 9; loop2++ )	{
			board_data.column[loop1][loop2] = false;
		}
	}	
	
	for ( loop1 = 0; loop1<2; loop1++ )	{
		for ( loop2 = 0; loop2 < 2; loop2++ )	{
			for ( loop3 = 0; loop3 < 9; loop3 ++ )	{
				board_data.square[loop1][loop2][loop3] = false;
			}
		}
	}
}	

void saveCellValue( int positionInCells, int temp_value, Boarddata &board_data )	{
	
	board_data.singleDimensionBoard[positionInCells] = temp_value;
	board_data.row[positionInCells/9][temp_value-1] = true;
	board_data.column[positionInCells%9][temp_value-1] = true;
	board_data.square[positionInCells/27][(positionInCells%9)/3][temp_value-1] = true;
	
}

void resetCellValue( int positionInCells, Boarddata &board_data )	{
	if ( !board_data.singleDimensionBoard[positionInCells] )
		return;
	int badCellValue = board_data.singleDimensionBoard[positionInCells];
	board_data.row[positionInCells/9][badCellValue-1] = false;
	board_data.column[positionInCells%9][badCellValue-1] = false;
	board_data.square[positionInCells/27][(positionInCells%9)/3][badCellValue-1] = false;
	
	board_data.singleDimensionBoard[positionInCells] = 0;
	
}