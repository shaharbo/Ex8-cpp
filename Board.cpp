    #include "Board.h"

Board::Board(int r)
{
    this->rows=r;
    this->game = new Node*[rows];
    for (int i = 0; i < rows; i++) {
        this->game[i] = new Node [rows];
    }
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < rows; j++) {
            game[i][j]= Node{'.'};
        }
    }
}

Board::Board()
{
    this->rows=1;
    this->game = new Node*[rows];
    for (int i = 0; i < rows; i++) {
        this->game[i] = new Node [rows];
    }
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < rows; j++) {
            game[i][j]= Node('.');
        }
    }
}

Board::Board(const Board& other)
{
    this->rows=other.rows;
    this->game = new Node*[rows];
    for (int i = 0; i < rows; i++) {
        this->game[i] = new Node [rows];
    }
    for(int i=0;i<rows;i++){
        for(int j=0;j<rows;j++){
            game[i][j]=other.game[i][j];
        }
    }
}

Board::~Board()
{
    for(int i=0;i<rows;i++){
        delete[] game[i];
    }
    delete[] game;
}

Node& Board::operator[](list<int> list)
{
    int a = list.front(), b=list.back();
    if(a<0 || a>=rows || b<0 || b>=rows)
    {
        IllegalCoordinateException ex;
        ex.setA(a); ex.setB(b);
        throw ex;
    }
    return game[a][b];
}

Board& Board::operator=(const Board &b)
{
    if (this==&b)
        return *this;
    if (b.rows!=this->rows) {
        for (int i = 0; i < rows; i++)
            delete[] game[i];
        delete [] game;

        rows = b.rows;
        game = new Node*[b.rows]; // init
        for (int i = 0; i < rows; i++) {
            game[i] = new Node [rows];
        }
    }

    for (int i=0; i<rows; ++i){
        for(int j=0;j<rows;j++){
            game[i][j]=Node{b.game[i][j].getNode()};
        }
    }
    return *this;
}

Board& Board::operator=(char c)
{
    if (c=='.') {
        for (int j = 0; j < rows; ++j) {
            for (int i = 0; i < rows; ++i) {
                game[i][j] = '.';
            }
        }
    }
    else
    {
        IllegalCharException ex;
        ex.setInput(c);
        throw ex;
    }
    return *this;
}

ostream &operator<<(ostream& out, const Board& b)
{
    for (int i = 0; i < b.rows; i++)
    {
        for (int j = 0; j < b.rows; j++){
            out << b.game[i][j].getNode();
        }
        out << endl;
    }
    return out;
}
string Board::draw(int n)
{
        const int dimX = n, dimY = n;
        int size = n / this->rows;
        int width = size / 8 ;
        string fileName="picture"+to_string(counter)+".ppm";
        counter++;
        ofstream img(fileName, ios::out | ios::binary);
        img << "P6" << endl << dimX <<" " << dimY << endl << 255 << endl;
        RGB image[dimX*dimY];
        for (int j = 0; j < dimY; ++j)  {  // row
            for (int i = 0; i < dimX; ++i) { // column
                image[dimX*j+i].red = (0);
                image[dimX*j+i].green = (0);
                image[dimX*j+i].blue = (0);
            }
        }
        int red,green,blue;

        for(int i=0; i < this->rows; i++)
            for(int j=0; j< this->rows;j++){
                if(this->game[i][j].getNode() == 'X'){
                    red =  249;
                    green = 107;
                    blue = 178;
                }

                else if (this->game[i][j].getNode() == 'O'){
                    red =  65;
                    green = 132;
                    blue = 241;
                }

                else{
                    red = green = blue = 255;
                }
                for (int m = i*size+width; m < i*size+size-width; ++m){
                    for (int p = j*size+width; p < j*size+size-width; ++p) {
                        image[dimX*m+p].red = (red);
                        image[dimX*m+p].green = (green);
                        image[dimX*m+p].blue = (blue);
                    }
                }
            }

        img.write(reinterpret_cast<char*>(&image), 3*dimX*dimY);
        img.close();
        return fileName;
    }

istream &operator>>(istream &in,  Board &b)
{
    string str;
    in>>str;
    int n = str.length();
    Board temp(n);
    b=temp;
    for (int i=0; i<n; i++){
        b[{0,i}] = str[i];   
    }
    int curr = 1;
    while(in>>str){
        for (int i=0; i<n; i++){
            b[{curr, i}] = str[i];    //needs to be checked
        }
        curr++;
    }
    return in;
}
