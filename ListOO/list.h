class rec
{
  friend class list;
  protected:
   char * id;
   char firstname[15];
   char lastname[15];
   int a[10];
   rec* prev;
   rec* next;
  public:
   rec (char* i, char* fn, char* ln, int* a);
   rec (const rec& r);  
   void SetData (char* id_in, char* fn, char* ln, int* ans_in);
   rec();
   ~rec();
   void operator= (const rec& r);
   void Print();
};

class list
{
  private:
    rec* first, *last;
  public:
    int AddItem (rec r);
    int DeleteItem ( char* delid );
    void PrintList ( int order );
    int ReadData ( char* key, char* ans);
    int WriteData (char* key, char* ans);
    list(void);
    void operator= (list& list_in);
};
