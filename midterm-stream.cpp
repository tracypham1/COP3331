//Matrix constructor reads cstring and constructs 2D matrix
//Matrix(const char*);

class Matrix{
private:
    int nrows;
    int ncols;
    double* mat;
public:
    Matrix(const char*);
};

Matrix::Matrix(const char* str){
    istringstream iss(str);
    vector<double> vec;
    string row;
    nrows = 0;
    ncols = 0;
    
    char c = iss.get(); //get the first char [
    if(c != '['){
        nrows = ncols = 1;
        mat = new double;
        mat[0] = 0.0;
        return;
    }

    while(getline(iss, row, ';')){//store the first row in a string
        nrows++;
        istringstream in(row);//put that string in local iss

        double temp;
        while(in >> temp) //get the first number in the string row
            vec.push_back(temp); //add temp to the vector

        in.clear(); //clear local iss
        in >> c;//the deliminator ; was discarded, this is for ' ' after the ;

        if(ncols == 0) //if this iternation is the first 
            ncols = vec.size(); //the ncols is #elements read for this row
        else if(vec.size() % ncols != 0){//if this row is incorrect ncols
            ncols = nrows = 1;
            mat = new double;
            *mat = 0.0;
            return; //error output
        
        //for last row it adds double values to vector 
        //leaving the ] to be read by in >> c
        }
    }

    //if the is no more the read, the loop breaks with ']' in c
    if(c == ']'){//transfer all values into the mat dat member poitner
        mat = new double[vec.size()];
        for(int i = 0; i < vec.size(); i++)
            mat[i] = vec[i];
    }
    else{
        ncols = nrows = 1;
        mat = new double;
        *mat = 0.0;
        return; //error output
    }
//the matrix is later printed with formatting based on nrows and ncols accessor functions
}