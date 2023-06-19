#ifndef MYPROJECT_Zadaca5
#define MYPROJECT_Zadaca5

class SquareMatrix{
    public:
        /*
        * pokazivač na dimanički alocirano polje duljine M * 
        čiji su elementi* pokazivači na dinamički alocirana polja duljine M (retci u matrici)
        */
        
        double** container;
        unsigned int M;
        
        SquareMatrix()=delete;// inicijaliziraj sve ćelije na 0.0 
        SquareMatrix(unsigned int);
        SquareMatrix(const SquareMatrix&);
        ~SquareMatrix();
        
        const double*operator[](unsigned int) const;
        
        SquareMatrix& operator=(const SquareMatrix&);
        SquareMatrix& operator+=(const SquareMatrix&);
        SquareMatrix& operator-=(const SquareMatrix&);
        SquareMatrix& operator*=(const SquareMatrix&); 

        // postavi sve ćelije na isti skalar
        SquareMatrix& operator=(double);
        //svim ćelijama nadodaj isti skalar
        SquareMatrix& operator+=(double);
        // od svih ćelija oduzmi isti skalar
        SquareMatrix& operator-=(double);
        // svaku ćeliju pomnoži sa skalarom
        SquareMatrix& operator*=(double);
        // svaku ćeliju podijeli sa skalarom
        SquareMatrix& operator/=(double);

        SquareMatrix operator+(const SquareMatrix&) const;
        SquareMatrix operator-(const SquareMatrix&) const;
        SquareMatrix operator*(const SquareMatrix&) const;
        SquareMatrix operator+(double) const;
        SquareMatrix operator-(double) const;
        SquareMatrix operator*(double) const;
        SquareMatrix operator/(double) const;
        bool operator==(const SquareMatrix&) const;
        bool operator!=(const SquareMatrix&) const;
};  

#endif