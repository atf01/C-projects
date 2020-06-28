//this project requries you to enter the matrix of the following form

//[1.2 4.3 5.5 ; 7.9 8.8 9 ; 7 2.5 1.4] with semi column separated by space from both sides like:- 4 ; 8

#include<iostream>
#include<vector>
#include<cstdlib>
#include<string>
using namespace std;
class matrix_former
{
    vector<string>elements;
    vector<vector<float> > matrix;

    vector<vector<float> > get_co_matrix(vector<vector<float> >matrix,int r,int c)
    {
        int row=0,col=0;
        vector<vector<float> >co_matrix;
        int SIZE=matrix.size()-1;
        co_matrix.resize(SIZE);
        for(int i=0; i<matrix.size(); i++)
        {
            co_matrix[row].resize(SIZE);
            for(int j=0; j<matrix[i].size(); j++)
            {
                if(i!=r && j!=c)
                {
                    co_matrix[row][col]=matrix[i][j];
                    col++;
                    if(col==SIZE)
                    {
                        col=0;
                        row++;
                    }
                    if(row==SIZE)
                        return co_matrix;
                }

            }

        }
        return co_matrix;
    }
    vector<vector<float> >Inverse_Matrix(vector<vector<float> >matrix)
    {
        vector<vector<float> >result;
        result.resize(matrix.size());
        float denominator=determinant(matrix);

        for(int i=0; i<matrix.size(); i++)
        {
            result[i].resize(matrix.size());
            for(int j=0; j<matrix[i].size(); j++)
            {
                float value=determinant(get_co_matrix(matrix,i,j));
                ((i+j)%2==0)? value*=1: value*=-1;
                result[i][j]=value/denominator;
            }

        }

        return result;
    }
public:
    friend istream & operator >>(istream &o,matrix_former &s);
    friend ostream & operator <<(ostream &o,matrix_former &s);
    friend matrix_former operator + (matrix_former f,matrix_former s);
    friend matrix_former operator - (matrix_former f,matrix_former s);
    friend matrix_former operator * (matrix_former f,matrix_former s);
    friend matrix_former operator / (matrix_former f,matrix_former s);

    void show_elements()
    {
        for(int i=0; i<elements.size(); i++)
            cout<<elements[i]<<"\n";
    }
    bool is_correct_format()
    {
        int var=0;
        for(int i=0; i<elements.size(); i++)
        {
            if(elements[i]==";")
                break;
            else
                var++;
        }
        int counter=0;

        for(int i=0; i<elements.size(); i++)
        {
            if(elements[i]==";")
            {
                if(var!=counter)
                {
                    elements.clear();
                    return false;
                }
                else
                    counter=0;
            }
            else
                counter++;
        }
        if(counter==var)
            return true;
        elements.clear();
        return false;
    }
    int numb_cols()
    {
        matrix[0].size();
    }
    int numb_rows()
    {
        return matrix.size();
    }
    float determinant(vector<vector<float> >matrix)
    {
        int n = matrix.size();

        for(int col = 0; col < n; ++col)
        {
            bool found = false;
            for(int row = col; row < n; ++row)
            {
                if(matrix[row][col]!=0.0)
                {
                    if ( row != col )
                    {
                        swap(matrix[row],matrix[col]);
                    }
                    found = true;
                    break;
                }
            }
            if(!found)
            {
                return 0;
            }

            for(int row = col + 1; row < n; ++row)
            {
                while(true)
                {
                    float del = (float)matrix[row][col] / (float)matrix[col][col];

                    for (int j = col; j < n; ++j)
                    {
                        matrix[row][j] -= del * matrix[col][j];
                    }
                    if (matrix[row][col] == 0.0)
                    {
                        break;
                    }
                    else
                    {
                        matrix[row].swap(matrix[col]);
                    }
                }
            }
        }

        float res = 1.0;

        for(int i = 0; i < n; ++i)
        {
            res *= matrix[i][i];
        }
        return res;
    }
    void set_matrix()
    {
        int rows=0;
        for(int i=0; i<matrix_former::elements.size(); i++)
            if(elements[i]==";")
                rows++;
        rows++;
        matrix.resize(rows);
        int r=0;
        for(int i=0; i<elements.size(); i++)
        {
            if(elements[i]==";")
                r++;
            else
            {
                if(elements[i][0]=='[')
                    matrix[r].push_back(stof(elements[i].substr(1,elements[i].length()-1)));
                else
                    matrix[r].push_back(stof(elements[i]));
            }
        }
    }
    bool is_valid_process(char x,matrix_former mat)
    {
        if(x=='+'||x=='-')
        {
            if(mat.numb_cols()==numb_cols()&&mat.numb_rows()==numb_rows())
                true;
            else
                return false;
        }
        if(x=='*'||x=='/')
        {
            if(x=='/')
                if(mat.numb_rows()!=mat.numb_cols()||mat.determinant(mat.matrix)==0)
                    return false;
            if(numb_cols()==mat.numb_rows())
                return true;
            else
                return false;
        }
        if(x=='^')
        {
            if(numb_cols()==numb_rows())
                return true;
            else
                return false;
        }
    }
    void transpose()
    {
        vector<vector<float> >co_matrix;
        co_matrix.resize(matrix[0].size());
        for(int i=0; i<co_matrix.size(); i++)
        {
            co_matrix[i].resize(matrix.size());
            for(int j=0; j<co_matrix[i].size(); j++)
            {
                co_matrix[i][j]=matrix[j][i];

            }
        }
        matrix=co_matrix;
    }
};
istream & operator >>(istream &o,matrix_former &s)
{
    string input;
    while(input[input.length()-1]!=']')
    {
        o>>input;
        s.elements.push_back(input);
    }
    return o;
}
ostream & operator << (ostream &o,matrix_former &m)
{
    for(int i=0; i<m.numb_rows(); i++)
    {
        if(i==0)
            o<<"[";
        for(int j=0; j<m.numb_cols(); j++)
        {
            if(j==m.numb_cols()-1)
                o<<m.matrix[i][j];
            else
                o<<m.matrix[i][j]<<" ";
        }
        if(i==m.numb_rows()-1)
            o<<"]";
        else
            o<<" ; ";

    }
    return o;
}
matrix_former operator + (matrix_former f,matrix_former s)
{
    matrix_former df;
    df.matrix.resize(f.numb_rows());
    for(int i=0; i<f.numb_rows(); i++)
    {
        df.matrix[i].resize(f.numb_cols());
        for(int j=0; j<f.numb_cols(); j++)
        {
            df.matrix[i][j]=f.matrix[i][j]+s.matrix[i][j];
        }
    }
    return df;
}
matrix_former operator - (matrix_former f,matrix_former s)
{
    matrix_former df;
    df.matrix.resize(f.numb_rows());
    for(int i=0; i<f.numb_rows(); i++)
    {
        df.matrix[i].resize(f.numb_cols());
        for(int j=0; j<f.numb_cols(); j++)
        {
            df.matrix[i][j]=f.matrix[i][j]-s.matrix[i][j];
        }
    }
    return df;
}

matrix_former operator * (matrix_former f,matrix_former s)
{
    matrix_former fd;
    fd.matrix.resize(f.numb_rows());
    for(int i=0; i<f.numb_rows(); i++)
    {
        fd.matrix[i].resize(s.numb_cols());
        for(int j=0; j<s.numb_cols(); j++)
        {
            fd.matrix[i][j]=0;
        }
    }
    for(int i=0; i<f.numb_rows(); i++)
    {
        for(int j=0; j<s.numb_cols(); j++)
        {
            for(int k=0; k<f.numb_cols(); k++)
            {
                fd.matrix[i][j]+=(f.matrix[i][k])*(s.matrix[k][j]);
            }
        }
    }
    return fd;
}
matrix_former operator / (matrix_former f,matrix_former s)
{
    s.matrix=s.Inverse_Matrix(s.matrix);
    matrix_former result= f*s;

    return result;
}

int main()
{
      string q="don't exit";
      cout<<"Welcome to the matrix solver program! to begin insert the matrix form you want!\n";
      while(q!="exit")
      {
          matrix_former mat_1;
          matrix_former mat_2;
          cin>>mat_1;
          while(true)
          {
              if(mat_1.is_correct_format())
                  break;
              cout<<"Matrix Format is incorrect!\n";
              cin>>mat_1;
          }
          mat_1.set_matrix();
          char x;
          cout<<"Insert the operation you want !\n";
          cin>>x;
          if(x=='+'||x=='-'||x=='*'||x=='/')
          {
           cout<<"Now Enter the next Matrix (Second operand)\n";
              cin>>mat_2;
              while(true)
              {
                  if(mat_2.is_correct_format())
                      break;
                  cout<<"Matrix Format is incorrect!\n";
                  cin>>mat_2;
              }
              mat_2.set_matrix();
              if(!mat_1.is_valid_process(x,mat_2))
                  cout<<"Invalid operation\n";
              else
              {
                  matrix_former mat_3;
                  if(x=='+')
                      mat_3=mat_1+mat_2;
                  if(x=='-')
                      mat_3=mat_1-mat_2;
                  if(x=='*')
                      mat_3=mat_1*mat_2;

                  if(x=='/')mat_3=mat_1/mat_2;
                  cout<<"RESULT IS: \n";
                  cout<<mat_3;
              }
          }
          else
          {
          if(x=='t'||x=='T')
          {
           mat_1.transpose();
           cout<<mat_1;
          }
          if(x=='^')
          {
           if(!mat_1.is_valid_process('*',mat_1))cout<<"ERROR in process! please insert proper types of input!\n";
           else
           {
           int m;
           cin>>m;
           m--;
           mat_2=mat_1;
           while(m--)
           {
            mat_1=mat_1*mat_2;
           }
           cout<<"RESULT IS:\n\n"<<mat_1;
          }
          }
          }

          cout<<"\nwould you like to continue? y for yes and exit to quit\n";
          cin>>q;
      }
    return 0;
}
