#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

#define UNASSIGNED 0

class SudokuSolver{

    private:
        vector<vector<int>> grid;
        vector<vector<int>> possibleValues;
        string fileName;
        // int expandedNodes=0;
        int N=9; //dimention of the gride
        int B=3; // box wdith

        vector<int> getPossibleValues(int row, int col);
        void writeTheGridOnFile(bool isPrint);
        void readGrid();
        void getUnsidedLocation(int& row, int& col);
        vector<vector<int>> getRemaningValues();
        bool isEmptyDomainProduced(int row,int col,int choice);
        bool solveSudoKu();    
    
    public:
        SudokuSolver(string fileN){
            fileName=fileN;
            readGrid();
            N=grid.size();
            B=sqrt(N);
            possibleValues=getRemaningValues();
        }
        void solve(){
		    writeTheGridOnFile(solveSudoKu());
        }
        void printGrid();
       

};

void SudokuSolver::writeTheGridOnFile(bool isPrint)
{
    fstream outputFile;
    outputFile.open(fileName+"_output.txt",fstream::out);

    if(isPrint){
        for (int row = 0; row < N; row++) 
        {
            for (int col = 0; col < N; col++)
                outputFile << grid[row][col] << " ";
            outputFile << endl;
        }
    }else{
         outputFile << "No solution exists";
    }
}

void SudokuSolver::printGrid()
{
	for (int row = 0; row < grid.size(); row++) 
	{
		for (int col = 0; col < grid.size(); col++)
			cout << grid[row][col] << " ";
		cout << endl;
	}
}

void SudokuSolver::readGrid(){
    ifstream readFile(fileName+".txt");
    
    string line;
    int number;
    while (getline (readFile, line)) {
        istringstream stringStream(line);
        vector<int> temp;
        while (stringStream >> number) 
        {
            temp.push_back(number);
        }
        grid.push_back(temp);
    }

}

vector<int> SudokuSolver::getPossibleValues(int row, int col){

     vector<int> vec={1,2,3,4,5,6,7,8,9 };

     if(N!=9)
        vec={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

 
    for (int col1 = 0; col1 < N; col1++)
           vec.erase(remove(vec.begin(), vec.end(), grid[row][col1]), vec.end());
    for (int row1 = 0; row1 < N; row1++)
        vec.erase(remove(vec.begin(), vec.end(), grid[row1][col]), vec.end());

        int boxRow = row - row % B;
        int boxCol = col - col % B;
    for (int row1 = 0; row1 < B; row1++)
		for (int col1 = 0; col1 < B; col1++){
            vec.erase(remove(vec.begin(), vec.end(), grid[boxRow+row1][boxCol+col1]), vec.end());
        }

    return vec;

}

void SudokuSolver::getUnsidedLocation(int& row, int& col){
   
    int minVal=100;
    int minIndex=0;  

    for(int i=0;i<possibleValues.size();i++){
        int tempsize=possibleValues[i].size();
        if(possibleValues[i][0]==-15){
            tempsize=N+1;
        }
        if(minVal>tempsize){
            minVal=tempsize;
            minIndex=i;
        }
    }

    if (minVal==N+1){
        row=-1;
        col=-1;
    }else{
        row=floor(minIndex/N);
        col=minIndex%N;
    }   
}

vector<vector<int>> SudokuSolver::getRemaningValues(){
    vector<vector<int>>  possibleValues;
    for(int row=0;row<N;row++)
        for(int col=0;col<N;col++)
            if(grid[row][col]!=0)
                possibleValues.push_back(vector<int>{-15});
            else
                possibleValues.push_back(getPossibleValues(row,col));
    
    return possibleValues;
}

bool SudokuSolver::isEmptyDomainProduced(int row,int col,int choice){
    vector<int> elemnt = possibleValues[row*N+col];
     possibleValues.erase(possibleValues.begin() + row*N+col);
    if(find(possibleValues.begin(), possibleValues.end(), vector<int>{}) != possibleValues.end()){
        possibleValues.insert(possibleValues.begin() + row*N+col, elemnt);
        return true;
    }else{
        possibleValues.insert(possibleValues.begin() + row*N+col, elemnt);
        return false;
    }

}


bool SudokuSolver::solveSudoKu(){
    int row,col;
    getUnsidedLocation(row,col);
    if(row==-1)
        return true;
    else{
        for(int k=0;k<possibleValues[row*N+col].size();k++){
            grid[row][col]=possibleValues[row*N+col][k];
            vector<vector<int>> cpy(possibleValues.size());
            copy(possibleValues.begin(), possibleValues.end(), cpy.begin());
            possibleValues=getRemaningValues();        
            if(!isEmptyDomainProduced(row,col,possibleValues[row*N+col][k])){
                
                if(solveSudoKu())
                    return true;
            }
            grid[row][col]=0;
            possibleValues=cpy;
        }
        
        
    }
    return false;
    
}

int main(int argc, char** argv)
{
    
    
    if(argc!=2){
        cout<<"Programme is required only one arugemnt which should contains the input file Name"<<endl;
        cout<<"<--Programme ended-->"<<endl;
        return -1;
    }

    
    
   string fileName=argv[1];
   fileName=fileName.substr(0,fileName.find("."));

   auto start = high_resolution_clock::now(); 

   SudokuSolver sudoku(fileName);
   sudoku.solve();    

    auto stop = high_resolution_clock::now(); 


    cout << "Exceution Time | "<<endl;
    auto sec = duration_cast<seconds>(stop - start); 
    cout << "          seconds      : "<<sec.count() << endl; 
    auto millisec = duration_cast<milliseconds>(stop - start); 
    cout << "          milliseconds : "<<millisec.count() << endl; 
    auto microsec = duration_cast<microseconds>(stop - start); 
    cout << "          microseconds : "<<microsec.count() << endl; 

   

	return 0;
}


