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
    this->rows=0;
    this->game = new Node*[rows];
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

string Board::draw(int n)
{
  const int dimx = n, dimy = n;
  int size = n / this->rows;
  int width = size / 10 ;
  string fileName="picture.ppm";
  ofstream img(fileName, ios::out | ios::binary);
  img << "P6" << endl << dimx <<" " << dimy << endl << 255 << endl;
  RGB image[dimx*dimy];
  for (int j = 0; j < dimy; ++j)  {  // row
    for (int i = 0; i < dimx; ++i) { // column
      image[dimx*j+i].red = (0);
      image[dimx*j+i].green = (0);
      image[dimx*j+i].blue = (0);
    }
  }
  int red,green,blue;  

  for(int i=0; i < this->rows; i++)
      for(int j=0; j< this->rows;j++){
           for (int m = i*size+width; m < i*size+size-width; ++m){
            for (int p = j*size+width; p < j*size+size-width; ++p) {
                image[dimx*m+p].red = (112);
                image[dimx*m+p].green = (214);
                image[dimx*m+p].blue = (136);
            }
        }

          if(this->game[i][j].getNode() == 'X'){
             
          }
         else if (this->game[i][j].getNode() == 'O'){
            float r = this->rows;
            red=green=blue=0;
            float pr = 2; 
            for (int i = -r; i <= r; i++) {
                for (int j = -r; j <= r; j++){
                float d = ((i*pr)/r)*((i*pr)/r) + (j/r)*(j/r);
                    if (d >0.95 && d<1.08) {
                    image[dimx*i+j].red = (red);
                    image[dimx*i+j].green = (green);
                    image[dimx*i+j].blue = (blue);
                }
                    else{
                image[dimx*i+j].red = (112);
                image[dimx*i+j].green = (214);
                image[dimx*i+j].blue = (136);
}
          }
          }
         }

          else{
              red = 255;
              green = 255;
              blue = 255;
          }
           }
 
  img.write(reinterpret_cast<char*>(&image), 3*dimx*dimy);
  img.close();
  return fileName;
}